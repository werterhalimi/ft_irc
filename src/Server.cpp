/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:58:44 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/21 17:51:03 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.h"
#include "Cmd.hpp"

Server::Server() : _users(new std::vector<User *>()), _operators(new std::vector<Operator *>()), _channels(new std::vector<Channel *>())
{
	#if LOG_LEVEL == 10
	std::cout << "Server default constructor" << std::endl;
	#endif
}

Server::Server(std::string const & name) : _servername(name), _users(new std::vector<User *>()), _operators(new std::vector<Operator *>()), _channels(new std::vector<Channel *>())
{
	#if LOG_LEVEL == 10
	std::cout << "Server name constructor" << std::endl;
	#endif
}

Server::Server(int port, std::string const & pass) : _port(port), _pass(pass), _servername("Default"), \
	_users(new std::vector<User *>()), _operators(new std::vector<Operator *>()), _channels(new std::vector<Channel *>())
{
	this->_channels->push_back(new Channel("#Default", 20));
	#if LOG_LEVEL == 10
	std::cout << "Server name constructor" << std::endl;
	#endif
	time_t	time_now = time(NULL);
	this->_time = gmtime(&time_now);
}

Server::Server(Server const & src) 
{
	this->_port = src.getPort();
	this->_pass = src.getPass();
	this->_servername = src.getName();
	this->_hostname = src.getHostname();
	this->_users = new std::vector<User *>(src.getUsers().begin(), src.getUsers().end());
	this->_channels = new std::vector<Channel *>(src.getChannels().begin(), src.getChannels().end());
	this->_operators = new std::vector<Operator *>(src.getOperators().begin(), src.getOperators().end());
	#if LOG_LEVEL == 10
	std::cout << "Server copy constructor" << std::endl;
	#endif
}

Server::~Server()
{
	delete this->_users;
	delete this->_channels;
	delete this->_operators;
	#if LOG_LEVEL == 10
	std::cout << "Server default deconstructor" << std::endl;
	#endif

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
	int					buff_len;
	int					opt;
    struct sockaddr_in	address;
	struct kevent		event;
	socklen_t			sizeofAddress = sizeof(address);
	int					kq;

	opt = 1;
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

	std::cout << YELLOW << &address << std::endl;
	std::cout << "Family : " << (int)address.sin_family << std::endl;
	std::cout << "Port : " << address.sin_port << std::endl;
	std::cout << "Port : " << ntohs(address.sin_port) << std::endl;
	std::cout << "IP : " << inet_ntoa(address.sin_addr) << std::endl;
	std::cout << "Length : " << (int)address.sin_len << std::endl;
	std::cout << "Zeros : " << address.sin_zero << std::endl;
	std::cout << "Sizeof Addr : " << sizeofAddress << std::endl;
	std::cout << RESET_COLOR << std::endl;

	if (bind(server_fd, (struct sockaddr *)(&address), sizeofAddress) < 0)
		throw std::exception();

	Operator *	admin = new Operator("ncotte", "127.0.0.1", "Born2beroot");
	this->_operators->push_back(admin);

	kq = kqueue();
	// 1024 is out buffersize
	if (listen(server_fd, 1024) < 0)
		throw std::exception();
	User	empty;
	empty.setFd(-2);
	EV_SET(&event, server_fd, EVFILT_READ, EV_ADD | EV_CLEAR, 0, 0, &empty);
//	int	no_cmd = 1;
	while (1)
	{
		int n = kevent(kq, &event, 1, &event, 1, 0);
		if (n < 0) continue ;
		for(int i = 0; i < n; i++)
		{
			if (event.filter == EVFILT_READ)
			{
				User * user = (User *)event.udata;
				if ((user->getFd()) == -2)
				{ 
					char	buff[513];
					buff_len = read((user->getFd()), buff, 513);

					buff[buff_len] = 0;
					User *usr = new User();
					usr->setFd(server_fd);
					handleLogin(*usr, &event);
				}
				else
				{
					char buff[513];
					buff_len = read((user->getFd()), buff, 513);
					buff[buff_len] = 0;
//					std::cout << no_cmd++ << " " << buff << std::endl;
					std::string		*sp = split(buff, "\r\n");
					int	iter = 0;
					while (!sp[iter].empty())
					{
//						Cmd cmd(sp[iter++], this);
						Cmd cmd(sp[iter++]);
						cmd.execute(*this, *user);
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
	EV_SET(event,user.getFd(), EVFILT_READ, EV_ADD | EV_CLEAR, 0, 0, &user);
}

void	Server::handleLogout(User & user)
{
	std::remove(this->_users->begin(), this->_users->end(), &user);
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

Channel	* Server::getChannelByName(std::string const & name)
{
	std::vector<Channel *>::const_iterator	it = this->_channels->begin();
	std::vector<Channel *>::const_iterator	ite = this->_channels->end();
	while (it != ite)
	{
		if ((*it)->getName() == name)
			return (*it);
		it++;
	}
	return (0);
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
	return (-1);
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
	return (-1);
}

struct tm *	Server::getTime() const
{
	return (this->_time);
}
