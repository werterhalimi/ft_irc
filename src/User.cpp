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

User::User()
{
	#if LOG_LEVEL == 10
	std::cout << "User default constructor" << std::endl;
	#endif
}

User::User(std::string const &username, std::string const &nickname, std::string const &hostname) : boolFlags(0), username(username), nickname(nickname), hostname(hostname)
{
	#if LOG_LEVEL == 10
	std::cout << "User params constructor" << std::endl;
	#endif
}

User::User(User const & src) : boolFlags(0), username(src.getUsername()), nickname(src.getNickname()), hostname(src.getHostname())
{
	#if LOG_LEVEL == 10
	std::cout << "User copy constructor" << std::endl;
	#endif
}

User::~User()
{
	#if LOG_LEVEL == 10
	std::cout << "User default deconstructor" << std::endl;
	#endif
}

void	User::welcome()
{
	std::string hello = ":Default 001 " + this->getNickname() + " :Welcome to the BeyondIRC IRC Network " \
		+ this->getNickname() + "!" + this->getUsername() + "@" + this->getHostname() + "\r\n:Default 002 " \
		+ this->getNickname() + " :Your host is test.salut.com, running version 0.0.1\r\n:Default 003 " \
		+ this->getNickname() + " :This server was created 20:12:31 Jan 16 2013\r\n:Default 004 " \
		+ this->getNickname() + " :test.salut.com 2.0 ras\r\n";
	this->sendReply(hello);
}

void	User::sendReply(std::string const &buff) const
{
	if (!buff.empty())
	{
		std::cout << buff << " 123" << getUsername() << std::endl;
		send(this->fd, buff.c_str(), strlen(buff.c_str()), 0);
	}
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

std::string User::getUsername() const
{
	return this->username;
}

std::string User::getNickname() const
{
	return this->nickname;
}

std::string User::getHostname() const
{
	return this->hostname;
}

struct sockaddr_in *	User::getAddress()
{
	return &(this->addr);
}

socklen_t 	*User::getSocklen()
{
	return &(this->len);
}

int &	User::getFd()
{
	return (this->fd);
}

void	User::setFd(int i)
{
	this->fd = i;
}

bool	User::hasUser() const
{
	return (this->boolFlags & USER_FLAG);
}

bool	User::hasNick() const
{
	return (this->boolFlags & NICK_FLAG);
}

bool	User::hasPass() const
{
	return (this->boolFlags & PASS_FLAG);
}

bool	User::isLog() const
{
	return ((this->boolFlags & PASS_FLAG) && (this->boolFlags & NICK_FLAG) && (this->boolFlags & USER_FLAG));
}

bool	User::isAway() const
{
	return (this->boolFlags & AWAY_FLAG);
}

bool	User::isInvisible() const
{
	return (this->boolFlags & INVISIBLE_FLAG);
}

bool	User::isWallops() const
{
	return (this->boolFlags & WALLOPS_FLAG);
}

bool	User::isRestricted() const
{
	return (this->boolFlags & RESTRICTED_FLAG);
}

bool	User::isGlobalOperator() const
{
	return (this->boolFlags & GLOBAL_OPERATOR_FLAG);
}

bool	User::isLocalOperator() const
{
	return (this->boolFlags & LOCAL_OPERATOR_FLAG);
}

bool	User::isOperator() const
{
	return (this->boolFlags & OPERATOR_FLAG);
}

void	User::setAway(bool flag)
{
	if (flag)
		this->boolFlags |= AWAY_FLAG;
	else
		this->boolFlags &= ~AWAY_FLAG;
}

void	User::setInvisible(bool flag)
{
	if (flag)
		this->boolFlags |= INVISIBLE_FLAG;
	else
		this->boolFlags &= ~INVISIBLE_FLAG;
}

void	User::setWallops(bool flag)
{
	if (flag)
		this->boolFlags |= WALLOPS_FLAG;
	else
		this->boolFlags &= ~WALLOPS_FLAG;
}

void	User::setRestricted(bool flag)
{
	if (flag)
		this->boolFlags |= RESTRICTED_FLAG;
	else
		this->boolFlags &= ~RESTRICTED_FLAG;
}

void	User::setGlobalOperator(bool flag)
{
	if (flag)
		this->boolFlags |= GLOBAL_OPERATOR_FLAG;
	else
		this->boolFlags &= ~GLOBAL_OPERATOR_FLAG;
}

void	User::setLocalOperator(bool flag)
{
	if (flag)
		this->boolFlags |= LOCAL_OPERATOR_FLAG;
	else
		this->boolFlags &= ~LOCAL_OPERATOR_FLAG;
}

void	User::auth()
{
	this->boolFlags |= PASS_FLAG;
}

void	User::setUsername(std::string const & username)
{
	this->username = username;
	this->boolFlags |= USER_FLAG;
}

void	User::setNickname(std::string const & nickname)
{
	this->nickname = nickname;
	this->boolFlags |= NICK_FLAG;
}

void	User::setHostname()
{
	std::cout << CYAN << "Hostname" << RESET_COLOR << std::endl;
//	if (&(this->addr))
//		std::cout << MAGENTA << inet_ntoa(this->addr->sin_addr) << RESET_COLOR << std::endl;
//	else
//		std::cout << MAGENTA << "NOPE" << RESET_COLOR << std::endl;
	this->hostname = inet_ntoa(this->addr.sin_addr);
	std::cout << RED <<hostname << RESET_COLOR << std::endl;
}

bool	User::loginOperator(Operator const * op, std::string const &password)
{
	if (op->isValidPassword(password))
		this->boolFlags |= OPERATOR_FLAG;
	return (this->isOperator());
}
