/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:41:03 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/16 17:43:34 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.h"
#include "Server.h"

User::User(void)
{
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

void	User::welcome(void) 
{

	std::string hello = ":Default 001 " + this->getNickname() + " :Welcome to the BeyondIRC IRC Network shalimi!shalimi@127.0.0.1\r\n:Default 002 "+ this->getNickname()+" :Your host is test.salut.com, running version 0.0.1\r\n:Default 003 "+ this->getNickname()+" :This server was created 20:12:31 Jan 16 2013\r\n:Default 004 "+ this->getNickname() +" :test.salut.com 2.0 ras\r\n";
	this->sendReply(hello);
}

void	User::sendReply(std::string buff) const
{
	std::cout << buff << " 123" << getUsername() << std::endl;
	send(this->fd, buff.c_str(), strlen(buff.c_str()), 0);
}

std::string	User::prefix() const
{
	std::ostringstream stream;
	stream << ":" << this->nickname << " " ;//<< "@" << this->username << "!" << this->hostname << " ";
	std::string str = stream.str();
	return (str);
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

bool	User::hasUser(void) const
{
	return this->user;
}



bool	User::hasNick(void) const
{
	return this->nick;
}



bool	User::hasPass(void) const
{
	return this->pass;
}

bool	User::isLog() const
{
	return this->pass && this->user && this->nick;
}

void	User::auth(void)
{
	this->pass = true;
}

void	User::setUsername(std::string & username)
{
	this->username = username;
	this->user = true;
}

void	User::setNickname(std::string & nickname)
{
	this->nickname = nickname;
	this->nick = true;
}
