/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:41:03 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/13 16:00:18 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.h"
#include "Server.h"

User::User(void)
{
	this->logged = false;
	#if LOG_LEVEL == 10
	std::cout << "User default constructor" << std::endl;
	#endif
}

User::User(std::string username, std::string nickname, std::string hostname) : username(username), nickname(nickname), hostname(hostname)
{
	#if LOG_LEVEL == 10
	std::cout << "User params constructor" << std::endl;
	#endif
}

User::User(User const & src) : username(src.getUsername()), nickname(src.getNickname()), hostname(src.getHostname())
{
	#if LOG_LEVEL == 10
	std::cout << "User copy constructor" << std::endl;
	#endif
}

User::~User(void)
{
	#if LOG_LEVEL == 10
	std::cout << "User default deconstructor" << std::endl;
	#endif
}

void	User::log(char *buff)
{
	(void) buff;
	this->logged = true;
//	std::cout << buff << std::endl;
	std::string hello = ":servername 001 shalimi :Welcome to the BeyondIRC IRC Network shalimi!shalimi@127.0.0.1\r\n:servername 002 shalimi :Your host is test.salut.com, running version 0.0.1\r\n:servername 003 shalimi :This server was created 20:12:31 Jan 16 2013\r\n:servername 004 shalimi :test.salut.com 2.0 ras\r\n";
	send(this->fd, hello.c_str(), strlen(hello.c_str()), 0);
}

User &	User::operator=(User const & src)
{
	this->username = src.getUsername();
	this->nickname = src.getNickname();
	this->hostname = src.getHostname();
	return *this;
}

bool User::operator==(User const & src)
{
	return this->hostname == src.getHostname();
}

std::string User::getUsername(void) const
{
	return this->username;
}

std::string User::getNickname(void) const
{
	return this->nickname;
}

std::string User::getHostname(void) const
{
	return this->hostname;
}

struct sockaddr_in &	User::getAddress()
{
	return *(this->addr);
}

socklen_t &	User::getSocklen()
{
	return *(this->len);
}
int &	User::getFd()
{
	return (this->fd);
}

void	User::setFd(int i)
{
	this->fd = i;
}

bool	User::isLog()
{
	return this->logged;
}
