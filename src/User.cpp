/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:41:03 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/31 16:26:35 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include "Server.hpp"

/* Public */

/* Constructors & Destructor */

User::User() :
	_boolFlags(0),
	_addr(),
	_len(sizeof(struct sockaddr_in)),
	_fd(),
	_event(),
	_channels(new std::vector<Channel *>()),
	_buffer(),
	_bufferLength(0)
{
	#if LOG_LEVEL == 10
		std::cout << BOLD_BLUE << "User default constructor @ " << BOLD_MAGENTA << this << RESET_COLOR << std::endl;
	#endif
	this->initBuffer();
}

User::User(std::string const &username, std::string const &nickname, std::string const &hostname) :
	_boolFlags(0),
	_addr(),
	_len(sizeof(struct sockaddr_in)),
	_fd(),
	_username(username),
	_nickname(nickname),
	_hostname(hostname),
	_event(),
	_channels(new std::vector<Channel *>()),
	_buffer(),
	_bufferLength(0)
{
	#if LOG_LEVEL == 10
		std::cout << BOLD_BLUE << "User username, nickname & hostname constructor @ " << BOLD_MAGENTA << this << RESET_COLOR << std::endl;
	#endif
	this->initBuffer();
}

User::~User()
{
	#if LOG_LEVEL == 1
		std::cout << BOLD_BLUE << "User default destructor @ " << BOLD_MAGENTA << this << RESET_COLOR << std::endl;
	#endif
	delete this->_channels;
}

/* Overload operators */

bool User::operator==(User const & src) const
{
	return (this->_hostname == src.getHostname() && this->_username == src.getUsername());
}

/* Functions */

void	User::sendReply(std::string const &buff) const
{
	if (!buff.empty())
	{
		send(this->_fd, buff.c_str(), strlen(buff.c_str()), 0);
		#if LOG_LEVEL
				std::vector<std::string> sp = split(buff, " ");
					if (sp.size() > 1 && !sp[1].empty())
					{
						std::cout << GREEN;
						if (sp[1][0] == '4' || sp[1][0] == '5')
							std::cout << RED;
					}
					std::cout << buff << RESET_COLOR << std::endl;
		#endif
	}
}

void	User::welcome(Server const & server) const
{
	this->sendReply(rpl_welcome(server, *this));
	this->sendReply(rpl_yourhost(server, *this));
	this->sendReply(rpl_created(server, *this));
	this->sendReply(rpl_myinfo(server, *this));
}

void	User::handleCmd(Server & server)
{
	ssize_t read_return;

	read_return = read(this->_fd, this->_buffer + this->_bufferLength, 513);
	if (read_return < 0)
		throw std::exception();
	this->_bufferLength += (int)read_return;
	this->_buffer[this->_bufferLength] = 0;
	if (this->_bufferLength < 2 || this->_buffer[this->_bufferLength - 1] != '\n' || this->_buffer[this->_bufferLength - 2] != '\r')
		return;
	std::vector<std::string> sp = split(this->_buffer, "\r\n");
	std::vector<std::string>::const_iterator ite = sp.end();
	for (std::vector<std::string>::const_iterator it = sp.begin(); it < ite; ++it)
	{
		#if LOG_LEVEL
				std::cout << CYAN << printCurrentTime() << "- " << this->_fd << " ( " << this->prefix() << ") - \"" << *it << "\"" << RESET_COLOR << std::endl;
		#endif
		Cmd cmd(*it);
		cmd.execute(server, *this);
	}
	this->initBuffer();
	this->_bufferLength = 0;
}

/* Checkers */

bool	User::isLog() const
{
	return ((this->_boolFlags & PASS_FLAG) && (this->_boolFlags & NICK_FLAG) && (this->_boolFlags & USER_FLAG));
}

bool	User::loginOperator(Operator const * op, std::string const &password)
{
	if (op->isValidPassword(password))
		this->_boolFlags |= OPERATOR_FLAG;
	return (this->isOperator());
}

/* Setters */

void	User::setKEvent(struct kevent * event)
{
	this->_event = event;
}

void	User::setFd(int i)
{
	this->_fd = i;
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
	this->_realname = name.substr(1, name.size() - 1);
}

void	User::setHostname()
{
	this->_hostname = inet_ntoa(this->_addr.sin_addr);
}

/* Specific setters */

void	User::auth()
{
	this->_boolFlags |= PASS_FLAG;
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

void	User::addChannel(Channel * chan)
{
	this->_channels->push_back(chan);
}

void	User::removeChannel(Channel * chan)
{
	this->_channels->erase(std::find(this->_channels->begin(), this->_channels->end(), chan));
}

/* Getters */

struct kevent *	User::getKEvent() const
{
	return this->_event;
}

int 	User::getFd() const
{
	return (this->_fd);
}

socklen_t 	*User::getSocklenPtr()
{
	return &(this->_len);
}

struct sockaddr_in *	User::getAddressPtr()
{
	return &(this->_addr);
}

std::vector<Channel *>* User::getChannels() const
{
	return this->_channels;
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

std::string	User::prefix() const
{
	std::ostringstream stream;
	stream << ":" << this->_nickname << "!" << this->_username << "@" << this->_hostname << " ";
	std::string str = stream.str();
	return (str);
}

/* Specific getters */

bool	User::hasPass() const
{
	return (this->_boolFlags & PASS_FLAG);
}

bool	User::hasNick() const
{
	return (this->_boolFlags & NICK_FLAG);
}

bool	User::hasUser() const
{
	return (this->_boolFlags & USER_FLAG);
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

/* Private */

/* Constructors */

User::User(User const & src) :
	_boolFlags(),
	_addr(),
	_len(),
	_fd(),
	_username(),
	_nickname(),
	_hostname(),
	_event(),
	_channels(),
	_buffer(),
	_bufferLength()
{
	#if LOG_LEVEL == 10
		std::cout << BOLD_BLUE << "User copy constructor @ " << BOLD_MAGENTA << this << RESET_COLOR << std::endl;
	#endif
	*this = src;
}

/* Overload operators */

User &	User::operator=(User const & src)
{
	if (this != &src)
	{
		this->_boolFlags = src._boolFlags;
		this->_addr = src._addr;
		this->_len = src._len;
		this->_fd = src.getFd();
		this->_username = src.getUsername();
		this->_nickname = src.getNickname();
		this->_hostname = src.getHostname();
		this->_realname = src._realname;
		this->_event = src._event;
		this->_channels = src.getChannels();
		this->_bufferLength = src._bufferLength;
		for (int i = 0; i < READ_BUFFER_SIZE; ++i)
			this->_buffer[i] = src._buffer[i];
	}
	return *this;
}

/* Specific setters */

void	User::initBuffer()
{
	for (int i = 0; i < READ_BUFFER_SIZE; ++i)
		this->_buffer[i] = 0;
}
