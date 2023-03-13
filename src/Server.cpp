/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:58:44 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/11 20:43:13 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.h"

Server::Server(void) : users(new std::vector<User *>()), channels(new std::vector<Channel *>())
{
	#if LOG_LEVEL == 10
	std::cout << "Server default constructor" << std::endl;
	#endif
}

Server::Server(std::string	name) : servername(name), users(new std::vector<User *>()), channels(new std::vector<Channel *>())
{
	#if LOG_LEVEL == 10
	std::cout << "Server name constructor" << std::endl;
	#endif
}

Server::Server(Server const & src) 
{
	this->port = src.getPort();
	this->pass = src.getPass();
	this->servername = src.getName();
	this->hostname = src.getHostname();
	this->users = new std::vector<User *>(src.getUsers().begin(), src.getUsers().end());
	this->channels = new std::vector<Channel *>(src.getChannels().begin(), src.getChannels().end());
	#if LOG_LEVEL == 10
	std::cout << "Server copy constructor" << std::endl;
	#endif
}

Server::~Server(void)
{
	delete this->users;
	delete this->channels;
	#if LOG_LEVEL == 10
	std::cout << "Server default deconstructor" << std::endl;
	#endif

}

Server &	Server::operator=(Server const & src)
{
	this->port = src.getPort();
	this->pass = src.getPass();
	this->servername = src.getName();
	this->hostname = src.getHostname();
	delete this->users;
	delete this->channels;
	this->users = new std::vector<User *>(src.getUsers().begin(), src.getUsers().end());
	this->channels = new std::vector<Channel *>(src.getChannels().begin(), src.getChannels().end());
	return *this;
}



void	Server::launch(void)
{
	int					server_fd;
	int					buff_len;
	int					opt;
    struct sockaddr_in	address;
	struct kevent		event;
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
	address.sin_port = htons(6667);
	if (bind(server_fd, (struct sockaddr *)(&address), sizeof(address)) < 0)
		throw std::exception();
	
	kq = kqueue();
	// 1024 is out buffersize
	listen(server_fd, 1024);
	User	empty;
	empty.setFd(-2);
	EV_SET(&event, server_fd, EVFILT_READ, EV_ADD | EV_CLEAR, 0, 0, &empty);
	while(1)
	{
		struct timespec timeout = {3, 0};
		int n = kevent(kq, &event, 1, &event, 1, &timeout);
		if (n < 0) continue ;
		for(int i = 0; i < n; i++)
		{
			if (event.filter == EVFILT_READ)
			{
				User * user = (User *)event.udata;
				if ((user->getFd()) == -2)
				{ 
					User *usr = new User();
					usr->setFd(server_fd);
					handleLogin(*usr, &event);
				}
				else
				{
					char buff[513];
					buff_len = read((user->getFd()), buff, 513);
					buff[buff_len] = 0;
					if (!user->isLog())
						user->log(buff);
				}
			}
		}
	}
}

void	Server::handleLogin(User & user, struct kevent * event)
{
	this->users->push_back(&user);
	user.setFd(accept(user.getFd(), (struct sockaddr*)&(user.getAddress()) , &(user.getSocklen())));
	EV_SET(event,user.getFd(), EVFILT_READ, EV_ADD | EV_CLEAR, 0, 0, &user);

}

void	Server::handleLogout(User & user)
{
	std::remove(this->users->begin(), this->users->end(), &user);
}

std::string	Server::getPort() const
{
	return this->port;
}

std::string	Server::getPass() const
{
	return this->pass;
}

std::string	Server::getName() const
{
	return this->servername;
}

std::string	Server::getHostname() const
{
	return this->hostname;
}

std::vector<User *> &	Server::getUsers() const
{
	return *(this->users);
}

std::vector<Channel *> &	Server::getChannels() const
{
	return *(this->channels);
}
