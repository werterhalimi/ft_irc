/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:33:59 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/30 00:23:52 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "Channel.h"

Channel::Channel() :
	_users(new std::vector<User *>()),
	_bannedUsers(new std::vector<User *>()),
	_invitedUsers(new std::vector<User *>())
{
	#if LOG_LEVEL == 10
		std::cout << BOLD_BLUE << "Channel default constructor @ " << BOLD_MAGENTA << this << RESET_COLOR << std::endl;
	#endif
}

Channel::Channel(std::string const & name, int slots) :
	_name(name),
	_users(new std::vector<User *>()),
	_bannedUsers(new std::vector<User *>()),
	_invitedUsers(new std::vector<User *>()),
	_slots(slots)
{
	#if LOG_LEVEL == 10
		std::cout << BOLD_BLUE << "Channel name constructor @ " << BOLD_MAGENTA << this << RESET_COLOR << std::endl;
	#endif
	this->_topic = "Default topic";
}

Channel::Channel(std::string const & config) :
	_users(new std::vector<User *>()),
	_bannedUsers(new std::vector<User *>()),
	_invitedUsers(new std::vector<User *>())
{
	#if LOG_LEVEL == 10
		std::cout << BOLD_BLUE << "Channel config constructor @ " << BOLD_MAGENTA << this << RESET_COLOR << std::endl;
	#endif
	try
	{
		this->_name = "#" + parsing(config, "name", true);
		std::istringstream(parsing(config, "slots", false)) >> this->_slots;
		this->_topic = parsing(config, "topic", false);
		this->_boolFlags = parsingFlags(config);
	}
	catch (std::exception &e)
	{
		throw std::exception();
	}
}

Channel::Channel(Channel const & src) :
	_name(src.getName()),
	_users(new std::vector<User *>(src.getUsers().begin(), src.getUsers().end())),
	_bannedUsers(new std::vector<User *>(src.getBannedUsers().begin(), src.getBannedUsers().end())),
	_invitedUsers(new std::vector<User *>(src.getInvitedUsers().begin(), src.getInvitedUsers().end())),
	_slots(src.getSlots())
{
	#if LOG_LEVEL == 10
	std::cout << BOLD_BLUE << "Channel copy constructor @ " << BOLD_MAGENTA << this << RESET_COLOR << std::endl;
	#endif
}

Channel::~Channel()
{
	#if LOG_LEVEL == 10
		std::cout << BOLD_BLUE << "Channel default destructor @ " << BOLD_MAGENTA << this << RESET_COLOR << std::endl;
	#endif
	delete this->_users;
}

std::string const &	Channel::getTopic() const
{
	return this->_topic;
}

void	Channel::setTopic(std::string const & topic)
{
	this->_topic = topic;
}

bool	Channel::isInviteOnly() const
{
	return (this->_boolFlags & INVITE_ONLY_FLAG);
}

bool	Channel::isProtectedTopic() const
{
	return (this->_boolFlags & PROTECTED_TOPIC_FLAG);
}

bool	Channel::isClientLimit() const
{
	return (this->_boolFlags & CLIENT_LIMIT_FLAG);
}

bool	Channel::isBanChannel() const
{
	return (this->_boolFlags & BAN_CHANNEL_FLAG);
}

bool	Channel::isFull() const
{
	return (this->isClientLimit() && this->_users->size() >= this->_slots);
}

void	Channel::removeUser(User & user, std::string const & reply)
{
	this->_users->erase(std::find(this->_users->begin(), this->_users->end(), &user));
	user.removeChannel(this);
	std::vector<User *>::iterator ite = this->_users->end();
	for (std::vector<User *>::const_iterator it = this->_users->begin(); it < ite; ++it)
		(*it)->sendReply(reply);
}

void	Channel::removeUser1Channel(User & user, std::string const & reply)
{
	user.sendReply(reply);
	this->removeUser(user, reply);
}

void	Channel::addUser(Server const & server, User & user)
{
	this->_users->push_back(&user);
	user.addChannel(this);
	std::string reply = rpl_join(*this, user);

	for(std::vector<User *>::iterator i = this->_users->begin(); i != this->_users->end(); i++)
		(*i)->sendReply(reply);
	user.sendReply(rpl_topic(server, *this, user));
	user.sendReply(rpl_namreply(server, *this, user));
	user.sendReply(rpl_endofnames(server, *this, user));
}

void	Channel::addInvitedUser(User * user)
{
	this->_invitedUsers->push_back(user);
}

bool	Channel::hasUser(User & user) const
{
	std::vector<User *>::const_iterator it = find (this->_users->begin(), this->_users->end(), &user);
	return (it != this->_users->end());
}

Channel &	Channel::operator=(Channel const & src)
{
	this->_name = src.getName();
	delete this->_users;
	this->_users = new std::vector<User *>(src.getUsers().begin(), src.getUsers().end());
	this->_bannedUsers = new std::vector<User *>(src.getBannedUsers().begin(), src.getBannedUsers().end());
	this->_slots = src.getSlots();
	this->_key = src.getKey();
	return *this;
}

bool	Channel::isBanned(User const & user) const
{
	std::vector<User *>::const_iterator it = find (this->_bannedUsers->begin(), this->_bannedUsers->end(), &user);
	return (it != this->_bannedUsers->end());
}

bool	Channel::isInvited(User const & user) const
{
	if (user.isGlobalOperator() || user.isLocalOperator())
		return (true);
	std::vector<User *>::const_iterator it = find (this->_invitedUsers->begin(), this->_invitedUsers->end(), &user);
	return (it != this->_invitedUsers->end());
}

std::string const &	Channel::getName() const
{
	return this->_name;
}

std::vector<User *> &	Channel::getBannedUsers() const
{
	return *(this->_bannedUsers);
}

std::vector<User *> &	Channel::getInvitedUsers() const
{
	return *(this->_invitedUsers);
}

std::vector<User *> &	Channel::getUsers() const
{
	return *(this->_users);
}

User	* Channel::getUserByName(std::string const & name) const
{
	std::vector<User *>::const_iterator	it = this->_users->begin();
	std::vector<User *>::const_iterator	ite = this->_users->end();
	while (it != ite)
	{
		if ((*it)->getNickname() == name)
			return (*it);
		it++;
	}
	return (NULL);
}

size_t	Channel::getSlots() const
{
	return (this->_slots);
}

std::string const &	Channel::getKey() const
{
	return this->_key;
}

void	Channel::setInviteOnly(bool flag)
{
	if (flag)
		this->_boolFlags |= INVITE_ONLY_FLAG;
	else
		this->_boolFlags &= ~INVITE_ONLY_FLAG;
}

void	Channel::setProtectedTopic(bool flag)
{
	if (flag)
		this->_boolFlags |= PROTECTED_TOPIC_FLAG;
	else
		this->_boolFlags &= ~PROTECTED_TOPIC_FLAG;
}

void	Channel::setClientLimit(bool flag)
{
	if (flag)
		this->_boolFlags |= CLIENT_LIMIT_FLAG;
	else
		this->_boolFlags &= ~CLIENT_LIMIT_FLAG;
}

void	Channel::setBanChannel(bool flag)
{
	if (flag)
		this->_boolFlags |= BAN_CHANNEL_FLAG;
	else
		this->_boolFlags &= ~BAN_CHANNEL_FLAG;
}
