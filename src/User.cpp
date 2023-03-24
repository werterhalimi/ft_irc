/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:41:03 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/23 18:46:29 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.h"
#include "Server.h"
#include "reply.h"

User::User() :
	_boolFlags(0),
	_len(sizeof(struct sockaddr_in)),
	_channels(new std::vector<Channel *>())
{
	#if LOG_LEVEL
		std::cout << "User default constructor @ " << this << std::endl;
	#endif
}

User::User(std::string const &username, std::string const &nickname, std::string const &hostname) :
	_boolFlags(0),
	_username(username),
	_nickname(nickname),
	_hostname(hostname),
	_channels(new std::vector<Channel *>())
{
	#if LOG_LEVEL
		std::cout << "User username, nickname & hostname constructor @ " << this << std::endl;
	#endif
}

User::User(User const & src) :
	_boolFlags(0),
	_username(src.getUsername()),
	_nickname(src.getNickname()),
	_hostname(src.getHostname()),
	_channels((src.getChannels()))
{
	#if LOG_LEVEL
		std::cout << "User copy constructor @ " << this << std::endl;
	#endif
}

User::~User()
{
	#if LOG_LEVEL
		std::cout << "User default destructor @ " << this << std::endl;
	#endif
	delete this->_channels;
}

void	User::setKEvent(struct kevent * event)
{
	this->_event = event;
}

struct kevent *	User::getKEvent() const
{
	return this->_event;
}

void	User::welcome(Server const & server) const
{
	this->sendReply(rpl_welcome(server, *this));
	this->sendReply(rpl_yourhost(server, *this));
	this->sendReply(rpl_created(server, *this));
	this->sendReply(rpl_myinfo(server, *this));
}

void	User::sendReply(std::string const &buff) const
{
	if (!buff.empty())
	{
		send(this->_fd, buff.c_str(), strlen(buff.c_str()), 0);
		std::cout << RED << buff << RESET_COLOR << std::endl;
	}
}

std::string	User::prefix() const
{
	std::ostringstream stream;
	stream << ":" << this->_nickname << "!" << this->_username << "@" << this->_hostname << " ";
	std::string str = stream.str();
	return (str);
}

User &	User::operator=(User const & src)
{
	this->_username = src.getUsername();
	this->_nickname = src.getNickname();
	this->_hostname = src.getHostname();
	this->_channels = src.getChannels();
	return *this;
}

bool User::operator==(User const & src)
{
	return this->_hostname == src.getHostname();
}


std::string User::getRealname() const
{
	return this->_realname;
}


std::string User::getUsername() const
{
	return this->_username;
}

std::string User::getNickname() const
{
	return this->_nickname;
}

std::string User::getHostname() const
{
	return this->_hostname;
}

struct sockaddr_in *	User::getAddressPtr()
{
	return &(this->_addr);
}

socklen_t 	*User::getSocklenPtr()
{
	return &(this->_len);
}

int &	User::getFd()
{
	return (this->_fd);
}

void	User::setFd(int i)
{
	this->_fd = i;
}

bool	User::hasUser() const
{
	return (this->_boolFlags & USER_FLAG);
}

bool	User::hasNick() const
{
	return (this->_boolFlags & NICK_FLAG);
}

bool	User::hasPass() const
{
	return (this->_boolFlags & PASS_FLAG);
}

bool	User::isLog() const
{
	return ((this->_boolFlags & PASS_FLAG) && (this->_boolFlags & NICK_FLAG) && (this->_boolFlags & USER_FLAG));
}

bool	User::isAway() const
{
	return (this->_boolFlags & AWAY_FLAG);
}

bool	User::isInvisible() const
{
	return (this->_boolFlags & INVISIBLE_FLAG);
}

bool	User::isWallops() const
{
	return (this->_boolFlags & WALLOPS_FLAG);
}

bool	User::isRestricted() const
{
	return (this->_boolFlags & RESTRICTED_FLAG);
}

bool	User::isGlobalOperator() const
{
	return (this->_boolFlags & GLOBAL_OPERATOR_FLAG);
}

bool	User::isLocalOperator() const
{
	return (this->_boolFlags & LOCAL_OPERATOR_FLAG);
}

bool	User::isOperator() const
{
	return (this->_boolFlags & OPERATOR_FLAG);
}

void	User::setAway(bool flag)
{
	if (flag)
		this->_boolFlags |= AWAY_FLAG;
	else
		this->_boolFlags &= ~AWAY_FLAG;
}

void	User::setInvisible(bool flag)
{
	if (flag)
		this->_boolFlags |= INVISIBLE_FLAG;
	else
		this->_boolFlags &= ~INVISIBLE_FLAG;
}

void	User::setWallops(bool flag)
{
	if (flag)
		this->_boolFlags |= WALLOPS_FLAG;
	else
		this->_boolFlags &= ~WALLOPS_FLAG;
}

void	User::setRestricted(bool flag)
{
	if (flag)
		this->_boolFlags |= RESTRICTED_FLAG;
	else
		this->_boolFlags &= ~RESTRICTED_FLAG;
}

void	User::setGlobalOperator(bool flag)
{
	if (flag)
		this->_boolFlags |= GLOBAL_OPERATOR_FLAG;
	else
		this->_boolFlags &= ~GLOBAL_OPERATOR_FLAG;
}

void	User::setLocalOperator(bool flag)
{
	if (flag)
		this->_boolFlags |= LOCAL_OPERATOR_FLAG;
	else
		this->_boolFlags &= ~LOCAL_OPERATOR_FLAG;
}

void	User::auth()
{
	this->_boolFlags |= PASS_FLAG;
}

void	User::setUsername(std::string const & username)
{
	this->_username = username;
	this->_boolFlags |= USER_FLAG;
}

void	User::setNickname(std::string const & nickname)
{
	this->_nickname = nickname;
	this->_boolFlags |= NICK_FLAG;
}


void	User::setRealname(std::string const & name)
{
	this->_realname = name.substr(2, name.size() - 1);
}


void	User::setHostname()
{
	this->_hostname = inet_ntoa(this->_addr.sin_addr);
}

bool	User::loginOperator(Operator const * op, std::string const &password)
{
	if (op->isValidPassword(password))
		this->_boolFlags |= OPERATOR_FLAG;
	return (this->isOperator());
}

std::vector<Channel *>* User::getChannels() const
{
	return this->_channels;
}

void	User::addChannel(Channel * chan)
{
	this->_channels->push_back(chan);
}

void	User::removeChannel(Channel * chan)
{
	this->_channels->erase(std::find(this->_channels->begin(), this->_channels->end(), chan));
}
