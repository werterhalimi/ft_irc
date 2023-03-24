/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:33:59 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/22 18:56:05 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "Channel.h"

Channel::Channel() :
	_users(new std::vector<User *>()),
	_bannedUsers(new std::vector<User *>())
{
	#if LOG_LEVEL
		std::cout << "Channel default constructor @ " << this << std::endl;
	#endif
}

Channel::Channel(std::string const & name, int slots) :
	_name(name),
	_users(new std::vector<User *>()),
	_bannedUsers(new std::vector<User *>()),
	_slots(slots)
{
	#if LOG_LEVEL
		std::cout << "Channel name  constructor @ " << this << std::endl;
	#endif
	this->_topic = "Default _topic";
}

Channel::Channel(Channel const & src) :
	_name(src.getName()),
	_users(new std::vector<User *>(src.getUsers().begin(), src.getUsers().end())),
	_bannedUsers(new std::vector<User *>(src.getBannedUsers().begin(), src.getBannedUsers().end())),
	_slots(src.getSlots())
{
	#if LOG_LEVEL
	std::cout << "Channel copy constructor @ " << this << std::endl;
	#endif
}

Channel::~Channel()
{
	#if LOG_LEVEL
		std::cout << "Channel default destructor @ " << this << std::endl;
	#endif
	delete this->_users;
}

std::string const &	Channel::getTopic() const
{
	return this->_topic;
}

bool	Channel::isInviteOnly() const
{
	return (this->_boolFlags & INVITE_ONLY_FLAG);
}

bool	Channel::isFull() const
{
	return this->_users->size() >= this->_slots;
}

void	Channel::removeUser(Server const & server, User & user, std::string * reason)
{
	(void) server;
	this->_users->erase(std::find(this->_users->begin(), this->_users->end(), &user));
	user.removeChannel(this);
	std::string reply = rpl_part(*this, user, reason);
	user.sendReply(reply);
	for (std::vector<User *>::iterator i = this->_users->begin(); i != this->_users->end(); i++)
		(*i)->sendReply(reply);

}

void	Channel::removeUserQuit(Server const & server, User & user, std::vector<std::string> & reason)
{
	(void) server;
	this->_users->erase(std::find(this->_users->begin(), this->_users->end(), &user));
	user.removeChannel(this);
	std::string reply = rpl_quit(user, reason);
	user.sendReply(reply);
	std::cout << reply << std::endl;
	for (std::vector<User *>::iterator i = this->_users->begin(); i != this->_users->end(); i++)
		(*i)->sendReply(reply);

}

void	Channel::addUser(Server const & server, User & user)
{
	std::string reply = rpl_join(*this, user);

	for(std::vector<User *>::iterator i = this->_users->begin(); i != this->_users->end(); i++)
		(*i)->sendReply(reply);
	user.sendReply(rpl_topic(server, *this, user));
	user.sendReply(rpl_namreply(server, *this, user));
	user.sendReply(rpl_endofnames(server, *this, user));

	this->_users->push_back(&user);
	user.addChannel(this);
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

std::string const &	Channel::getName() const
{
	return this->_name;
}

std::vector<User *> &	Channel::getBannedUsers() const
{
	return *(this->_bannedUsers);
}

std::vector<User *> &	Channel::getUsers() const
{
	return *(this->_users);
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
