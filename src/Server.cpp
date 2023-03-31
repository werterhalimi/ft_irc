/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:58:44 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/31 18:05:26 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/* Public */

/* Constructors & Destructor */

Server::Server(int port, std::string const & pass) :
	_port(port),
	_pass(pass),
	_servername("Default"),
	_users(new std::vector<User *>()),
	_operators(new std::vector<Operator *>()),
	_channels(new std::vector<Channel *>()),
	_kq_fd(),
	_running(true)
{
	#if LOG_LEVEL == 10
		std::cout << BOLD_BLUE << "Server port&path constructor @ " << BOLD_MAGENTA << this << RESET_COLOR << std::endl;
	#endif
	time_t	time_now = time(NULL);
	this->_time = gmtime(&time_now);
}

Server::~Server()
{
	#if LOG_LEVEL == 10
		std::cout << BOLD_BLUE << "Server default destructor @ " << BOLD_MAGENTA << this << RESET_COLOR << std::endl;
	#endif
	std::vector<User *>::const_iterator ite = this->_users->end();
	for (std::vector<User *>::const_iterator it = this->_users->begin() + 1; it != ite; ++it)
		(*it)->sendReply(rpl_error(*(*it), ":The server is shutting down"));
	deleteVector(this->_users);
	deleteVector(this->_channels);
	deleteVector(this->_operators);
}

/* Functions */

void	Server::launch()
{
	int					server_fd;
	ssize_t				buff_len;
	int					opt = 1;
    struct sockaddr_in	address = {};
	struct kevent		event[KEVENT_BUFFER_SIZE];
	struct kevent		event_set = {};
	socklen_t			sizeofAddress = sizeof(address);

	try
	{
		serverConfig("config/IRC.conf");
	}
	catch (std::exception &e)
	{
		throw std::exception();
	}
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw std::exception();
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
		throw std::exception();
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(this->_port);

	#if LOG_LEVEL
		std::cout << YELLOW << printCurrentTime() << ": SERVER @ " << &address << std::endl;
		std::cout << "Family : " << (int)address.sin_family << std::endl;
		std::cout << "Port : " << address.sin_port << std::endl;
		std::cout << "Port : " << ntohs(address.sin_port) << std::endl;
		std::cout << "IP : " << inet_ntoa(address.sin_addr) << std::endl;
		std::cout << "Length : " << (int)address.sin_len << std::endl;
		std::cout << "Zeros : " << address.sin_zero << std::endl;
		std::cout << "Sizeof Addr : " << sizeofAddress << std::endl;
		std::cout << "Channels : " << std::endl;
		std::vector<Channel *>::const_iterator itce = this->_channels->end();
		for (std::vector<Channel *>::const_iterator it = this->_channels->begin(); it < itce; ++it)
			std::cout << "\t\"" << (*it)->getName() << "\"" << std::endl;
		std::cout << "Operators : " << std::endl;
		std::vector<Operator *>::const_iterator itoe = this->_operators->end();
		for (std::vector<Operator *>::const_iterator it = this->_operators->begin(); it < itoe; ++it)
			std::cout << "\t\"" << (*it)->getName() << "\"" << std::endl;
		std::cout << RESET_COLOR << std::endl;
	#endif

	if (bind(server_fd, (struct sockaddr *)(&address), sizeofAddress) < 0)
		throw std::exception();

	this->_kq_fd = kqueue();
	if (listen(server_fd, KEVENT_BUFFER_SIZE) < 0)
		throw std::exception();
	User	empty;
	empty.setFd(-2);
	EV_SET(&event_set, server_fd, EVFILT_READ, EV_ADD, 0, 0, &empty);
	if (kevent(this->_kq_fd, &event_set, 1, NULL, 0, NULL) == -1)
		throw std::exception();
	while (this->_running)
	{
		int n = kevent(this->_kq_fd, NULL, 0, event, KEVENT_BUFFER_SIZE, NULL);
		if (n < 0) continue ;
		for (int i = 0; i < n; i++)
		{
			User * user = (User *)event[i].udata;
			if (event[i].flags & EV_EOF)
			{
				#if LOG_LEVEL
					std::cout << YELLOW << "END OF CONNECTION" << RESET_COLOR << std::endl;
				#endif
				try
				{
					this->userLogout(*user);
				}
				catch (std::exception &e)
				{
					throw std::exception();
				}
			}
			else if (event[i].filter == EVFILT_READ)
			{
				if ((user->getFd()) == -2)
				{
					char	buff[513];
					buff_len = read((user->getFd()), buff, 513);
					buff[buff_len] = 0;
					User *usr = new User();
					usr->setFd((int)event[i].ident);
					try
					{
						this->handleLogin(*usr, &event_set);
					}
					catch (std::exception &e)
					{
						throw std::exception();
					}
					if (kevent(this->_kq_fd, &event_set, 1, NULL, 0, NULL) == -1)
						throw std::exception();
				}
				else
				{
					try
					{
						user->handleCmd(*this);
					}
					catch (std::exception &e)
					{
						throw std::exception();
					}
				}
			}
		}
	}
	close(this->_kq_fd);
	std::cout << "Shutting down" << std::endl;
}

void	Server::handleLogout(Cmd const & cmd, User & user, std::string const & params)
{
	std::string reply = rpl_quit(user, params);
	user.sendReply(reply);
	std::vector<Channel *>::const_iterator it = user.getChannels()->begin();
	std::vector<Channel *>::const_iterator ite = user.getChannels()->end();
	while (it != ite)
		(*(it++))->removeUser(user, reply);
	user.sendReply(rpl_error(user, cmd));
	try
	{
		this->userLogout(user);
	}
	catch (std::exception &e)
	{
		throw std::exception();
	}
}

/* Checkers */

bool	Server::hasNick(std::string const & nick) const
{
	std::vector<User *>::const_iterator it = this->_users->begin();
	std::vector<User *>::const_iterator ite = this->_users->end();
	while (it != ite)
	{
		if ((*it)->getNickname() == nick)
			return (true);
		it++;
	}
	return (false);
}

/* Specific setters */

void	Server::registerCustomUser(User & user)
{
	this->_users->push_back(&user);
}

void	Server::createChannel(std::string const & name, int slots)
{
	this->_channels->push_back(new Channel("#" + name, slots));
}

void	Server::removeChannel(Channel const * channel)
{
	this->_channels->erase(std::find(this->_channels->begin(), this->_channels->end(), channel));
	delete channel;
}

void	Server::stop()
{
	this->_running = false;
}

/* Getters */

int	Server::getPort() const
{
	return this->_port;
}

std::string	Server::getPass() const
{
	return this->_pass;
}

std::string	Server::getName() const
{
	return this->_servername;
}

std::string	Server::getHostname() const
{
	return this->_hostname;
}

std::vector<User *> &	Server::getUsers() const
{
	return *(this->_users);
}

std::vector<Operator *> &	Server::getOperators() const
{
	return *(this->_operators);
}

std::vector<Channel *> &	Server::getChannels() const
{
	return *(this->_channels);
}

struct tm *	Server::getTime() const
{
	return (this->_time);
}

/* Specific getters */

User *	Server::getUserByName(std::string const & name) const
{
	std::vector<User *>::const_iterator	ite = this->_users->end();
	for (std::vector<User *>::const_iterator it = this->_users->begin(); it < ite; ++it)
		if ((*it)->getNickname() == name)
			return (*it);
	return (NULL);
}

Channel	* Server::getChannelByName(std::string const & name) const
{
	std::vector<Channel *>::const_iterator	ite = this->_channels->end();
	for (std::vector<Channel *>::const_iterator it = this->_channels->begin(); it < ite; ++it)
		if ((*it)->getName() == name)
			return (*it);
	return (NULL);
}

std::string	Server::getPrefix() const
{
	return (":" + this->getName() + " ");
}

/* Private */

/* Constructors */

Server::Server() :
	_port(),
	_users(new std::vector<User *>()),
	_operators(new std::vector<Operator *>()),
	_channels(new std::vector<Channel *>()),
	_time(),
	_kq_fd(),
	_running()
{
	#if LOG_LEVEL == 10
		std::cout << BOLD_BLUE << "Server default constructor @ " << BOLD_MAGENTA << this << RESET_COLOR << std::endl;
	#endif
}

Server::Server(Server const & src) :
	_port(),
	_users(),
	_operators(),
	_channels(),
	_time(),
	_kq_fd(),
	_running()
{
	#if LOG_LEVEL == 10
		std::cout << BOLD_BLUE << "Server copy constructor @ " << BOLD_MAGENTA << this << RESET_COLOR << std::endl;
	#endif
	*this = src;
}

/* Overload operators */

Server &	Server::operator=(Server const & src)
{
	if (this != &src)
	{
		this->_port = src.getPort();
		this->_pass = src.getPass();
		this->_servername = src.getName();
		this->_hostname = src.getHostname();
		delete this->_users;
		delete this->_channels;
		delete this->_operators;
		this->_users = new std::vector<User *>(src.getUsers().begin(), src.getUsers().end());
		this->_channels = new std::vector<Channel *>(src.getChannels().begin(), src.getChannels().end());
		this->_operators = new std::vector<Operator *>(src.getOperators().begin(), src.getOperators().end());
		this->_time = src.getTime();
		this->_kq_fd = src._kq_fd;
		this->_running = src._running;
	}
	return *this;
}

/* Functions */

void	Server::handleLogin(User & user, struct kevent * event)
{
	int fd = accept(user.getFd(), (struct sockaddr *) user.getAddressPtr(), user.getSocklenPtr());
	if (fd < 0)
		throw std::exception();
	this->_users->push_back(&user);
	user.setFd(fd);
	user.setKEvent(event);
	EV_SET(event,user.getFd(), EVFILT_READ, EV_ADD, 0, 0, &user);
}

void	Server::userLogout(User & user)
{
	this->_users->erase(std::find(this->_users->begin(), this->_users->end(), &user));
	EV_SET(user.getKEvent() ,user.getFd(), EVFILT_READ, EV_DELETE, 0, 0, &user);
	if (kevent(this->_kq_fd, user.getKEvent(), 1, NULL, 0, NULL) < 0)
		throw std::exception();
	close(user.getFd());
	delete &user;
}

void	Server::serverConfig(const char * path)
{
	std::ifstream	configFile;

	configFile.open(path, std::fstream::in);
	if (!configFile || !configFile.is_open())
		throw std::exception();
	std::string	fileStr((std::istreambuf_iterator<char>(configFile)), \
                	std::istreambuf_iterator<char>());
	configFile.close();
	size_t	index;
	std::vector<std::string> lines = split(fileStr, "\n");
	std::string item;
	std::vector<std::string>::const_iterator ite = lines.end();
	for (std::vector<std::string>::const_iterator it = lines.begin(); it < ite; ++it)
	{
		index = it->find("#", 0);
		if (index != std::string::npos)
			item = it->substr(0, index);
		else
			item = *it;
		if (it->find("Channel:", 0) == 0)
		{
			try
			{
				this->_channels->push_back(new Channel(item));
			}
			catch (std::exception &e)
			{
				throw std::exception();
			}
		}
		if (it->find("Operator:", 0) == 0)
		{
			try
			{
				this->_operators->push_back(new Operator(item));
			}
			catch (std::exception &e)
			{
				throw std::exception();
			}
		}
	}
}
