/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:33:59 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/21 16:16:16 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "Channel.h"

Channel::Channel(void) :
	users(new std::vector<User *>()),
	bannedUsers(new std::vector<User *>())
{
	#if LOG_LEVEL == 10
	std::cout << "Channel default constructor" << std::endl;
	#endif
}

Channel::Channel(std::string name, int slots) : 
	name(name),
	users(new std::vector<User *>()),
	bannedUsers(new std::vector<User *>()),
	slots(slots)
{
	this->topic = "Default topic";
	#if LOG_LEVEL == 10
	std::cout << "Channel name  constructor" << std::endl;
	#endif
}

Channel::Channel(Channel const & src) : 
	name(src.getName()),
	users(new std::vector<User *>(src.getUsers().begin(), src.getUsers().end())),
	bannedUsers(new std::vector<User *>(src.getBannedUsers().begin(),src.getBannedUsers().end())),
	slots(src.getSlots())
{
	#if LOG_LEVEL == 10
	std::cout << "Channel copy constructor" << std::endl;
	#endif
}

Channel::~Channel(void)
{
	delete this->users;
	#if LOG_LEVEL == 10
	std::cout << "Channel default deconstructor" << std::endl;
	#endif

}

std::string 	Channel::getTopic(void) const
{
	return this->topic;
}

//TODO
bool	Channel::isInviteOnly(void) const
{
	return false;
}

bool	Channel::isFull(void) const
{
	return this->users->size() >= this->slots; 
}

void	Channel::addUser(Server const & server, User & user)
{
	this->users->push_back(&user);
	Cmd join(user);
	Cmd topic(server);
	Cmd names(server);
	Cmd eof(server);

	join.addParam("JOIN");
	join.addParam(":" + this->getName());
	
	topic.setCmd(RPL_TOPIC);
	topic.addParam(user.getNickname());
	topic.addParam(this->getName());
	topic.addParam(":" + this->getTopic());


	names.setCmd(RPL_NAMREPLY);
	names.addParam(user.getNickname());
	names.addParam("="); //TODO all mode
	names.addParam(this->getName());
	for(std::vector<User *>::iterator i = this->users->begin(); i != this->users->end(); i++)
		names.addParam((*i)->getNickname());

	eof.setCmd(RPL_ENDOFNAMES);
	eof.addParam(user.getNickname());
	eof.addParam(this->getName());
	eof.addParam(":End of Names list");

	for(std::vector<User *>::iterator i = this->users->begin(); i != this->users->end(); i++)
		(*i)->sendReply(join.toString());
	user.sendReply(topic.toString());
	user.sendReply(names.toString());
	user.sendReply(eof.toString());
}

Channel &	Channel::operator=(Channel const & src)
{
	this->name = src.getName();
	delete this->users;
	this->users = new std::vector<User *>(src.getUsers().begin(), src.getUsers().end());
	this->bannedUsers = new std::vector<User *>(src.getBannedUsers().begin(), src.getBannedUsers().end());
	this->slots = src.getSlots();
	this->key = src.getKey();
	return *this;
}

bool	Channel::isBanned(User const & user) const
{
	std::vector<User *>::const_iterator it = find (this->bannedUsers->begin(), this->bannedUsers->end(), &user);
	return (it != this->bannedUsers->end());
}

std::string	Channel::getName() const
{
	return this->name;
}

std::vector<User *> &	Channel::getBannedUsers() const
{
	return *(this->bannedUsers);
}

std::vector<User *> &	Channel::getUsers() const
{
	return *(this->users);
}

size_t	Channel::getSlots() const
{
	return (this->slots);
}

std::string 	Channel::getKey(void) const
{
	return this->key;
}
