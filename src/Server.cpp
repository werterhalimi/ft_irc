/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:58:44 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/22 18:59:26 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.h"
#include "Cmd.hpp"

Server::Server() :
	_users(new std::vector<User *>()),
	_operators(new std::vector<Operator *>()),
	_channels(new std::vector<Channel *>())
{
	#if LOG_LEVEL
		std::cout << "Server default constructor @ " << this << std::endl;
	#endif
}

Server::Server(std::string const & name) :
	_servername(name),
	_users(new std::vector<User *>()),
	_operators(new std::vector<Operator *>()),
	_channels(new std::vector<Channel *>())
{
	#if LOG_LEVEL
		std::cout << "Server name constructor @ " << this << std::endl;
	#endif
}

Server::Server(int port, std::string const & pass) :
	_port(port),
	_pass(pass),
	_servername("Default"),
	_users(new std::vector<User *>()),
	_operators(new std::vector<Operator *>()),
	_channels(new std::vector<Channel *>())
{
	#if LOG_LEVEL
		std::cout << "Server port&path constructor @ " << this << std::endl;
	#endif
//	Channel * channel = new Channel("#Default", 20);
//	this->_channels->push_back(channel);
	time_t	time_now = time(NULL);
	this->_time = gmtime(&time_now);
}

Server::Server(Server const & src) 
{
	#if LOG_LEVEL
		std::cout << "Server copy constructor @ " << this << std::endl;
	#endif
	this->_port = src.getPort();
	this->_pass = src.getPass();
	this->_servername = src.getName();
	this->_hostname = src.getHostname();
	this->_users = new std::vector<User *>(src.getUsers().begin(), src.getUsers().end());
	this->_channels = new std::vector<Channel *>(src.getChannels().begin(), src.getChannels().end());
	this->_operators = new std::vector<Operator *>(src.getOperators().begin(), src.getOperators().end());
}

Server::~Server()
{
	#if LOG_LEVEL
		std::cout << "Server default destructor @ " << this << std::endl;
	#endif
	delete this->_users;
	delete this->_channels;
	delete this->_operators;
}

Server &	Server::operator=(Server const & src)
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
	return *this;
}

void	Server::launch()
{
	int					server_fd;
	int 				buff_len;
	int					opt = 1;
    struct sockaddr_in	address = {};
	struct kevent		event[1024];
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
	// AF_INET == ipv4
	// SOCK_STREAM == tcp
	// 0 is the default protocol
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw std::exception();
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
		throw std::exception();
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(this->_port);

	#if LOG_LEVEL
		std::cout << YELLOW << &address << std::endl;
		std::cout << "Family : " << (int)address.sin_family << std::endl;
		std::cout << "Port : " << address.sin_port << std::endl;
		std::cout << "Port : " << ntohs(address.sin_port) << std::endl;
		std::cout << "IP : " << inet_ntoa(address.sin_addr) << std::endl;
		std::cout << "Length : " << (int)address.sin_len << std::endl;
		std::cout << "Zeros : " << address.sin_zero << std::endl;
		std::cout << "Sizeof Addr : " << sizeofAddress << std::endl;
		std::cout << "Channels : " << std::endl;
		std::vector<Channel *>::const_iterator ite = this->_channels->end();
		for (std::vector<Channel *>::const_iterator it = this->_channels->begin(); it < ite; ++it)
		{
			std::cout << "\t\"" << (*it)->getName() << "\"" << std::endl;
		}
		std::cout << RESET_COLOR << std::endl;
	#endif

	if (bind(server_fd, (struct sockaddr *)(&address), sizeofAddress) < 0)
		throw std::exception();

	this->_kq_fd = kqueue();
	// 1024 is out buffersize
	if (listen(server_fd, 1024) < 0)
		throw std::exception();
	User	empty;
	empty.setFd(-2);
	EV_SET(&event_set, server_fd, EVFILT_READ, EV_ADD, 0, 0, &empty);
	if (kevent(this->_kq_fd, &event_set, 1, NULL, 0, NULL) == -1)
		throw std::exception();
//	int	no_cmd = 1;
	while (true)
	{
		int n = kevent(this->_kq_fd, NULL, 0, event, 1024, NULL);
		if (n < 0) continue ;
		for(int i = 0; i < n; i++)
		{
			User * user = (User *)event[i].udata;
			if(event[i].flags & EV_EOF)
			{
				EV_SET(&event_set, (int) event[i].ident, EVFILT_READ, EV_DELETE, 0, 0, NULL);
                if (kevent(this->_kq_fd, &event_set, 1, NULL, 0, NULL) == -1)
                    throw std::exception();
				close(user->getFd());
			}
			else if (event[i].filter == EVFILT_READ)
			{
				if ((user->getFd()) == -2)
				{
					char	buff[513];
					buff_len = read((user->getFd()), buff, 513); // TODO size_t < 0 ?
					buff[buff_len] = 0;
					User *usr = new User();
					usr->setFd((int)event[i].ident);
					handleLogin(*usr, &event_set);
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
					//delete sp;
				}
			}
		}
	}
}

void	Server::handleLogin(User & user, struct kevent * event)
{
	this->_users->push_back(&user);

	int fd = accept(user.getFd(), (struct sockaddr *) user.getAddressPtr(), user.getSocklenPtr());
	if (fd < 0)
		return ;
	user.setFd(fd);
	user.setKEvent(event);
	EV_SET(event,user.getFd(), EVFILT_READ, EV_ADD, 0, 0, &user);
}

void	Server::handleLogout(User & user, std::vector<std::string> params)
{
	this->_users->erase(std::find(this->_users->begin(), this->_users->end(), &user));

	std::vector<Channel *>::const_iterator it = user.getChannels()->begin();
	std::vector<Channel *>::const_iterator ite = user.getChannels()->end();
	while (it != ite)
		(*(it++))->removeUserQuit(user, params);
	EV_SET(user.getKEvent() ,user.getFd(), EVFILT_READ, EV_DELETE, 0, 0, &user);
	int	ret = kevent(this->_kq_fd, user.getKEvent(), 1, NULL, 0, NULL);
	if (ret == -1)
		return ; // ERROR
	close(user.getFd());
}

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

Channel	* Server::getChannelByName(std::string const & name) const
{
	std::vector<Channel *>::const_iterator	it = this->_channels->begin();
	std::vector<Channel *>::const_iterator	ite = this->_channels->end();
	while (it != ite)
	{
		if ((*it)->getName() == name)
			return (*it);
		it++;
	}
	return (NULL);
}

std::string	Server::prefix() const
{
	return (":" + this->getName() + " ");
}

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

int	Server::getChannelID(std::string const & name) const
{
	int	id = 0;
	std::vector<Channel *>::const_iterator ite = this->_channels->end();
	for (std::vector<Channel *>::const_iterator it = this->_channels->begin(); it < ite; ++it)
	{
		if ((*it)->getName() == name)
			return (id);
		id++;
	}
	return (EXIT_ERROR_NEG);
}

int	Server::getUserID(std::string const & nickname) const
{
	int	id = 0;

	std::vector<User *>::const_iterator ite = this->_users->end();
	for (std::vector<User *>::const_iterator it = this->_users->begin(); it < ite; ++it)
	{
		if ((*it)->getNickname() == nickname)
			return (id);
		id++;
	}
	return (EXIT_ERROR_NEG);
}

struct tm *	Server::getTime() const
{
	return (this->_time);
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
