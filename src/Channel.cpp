/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:33:59 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/16 18:51:30 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.h"

Channel::Channel(void) : users(new std::vector<User *>())
{
	#if LOG_LEVEL == 10
	std::cout << "Channel default constructor" << std::endl;
	#endif
}

Channel::Channel(std::string name) : name(name), users(new std::vector<User *>())
{
	#if LOG_LEVEL == 10
	std::cout << "Channel name  constructor" << std::endl;
	#endif
}

Channel::Channel(Channel const & src) : name(src.getName()), users(new std::vector<User *>(src.getUsers().begin(), src.getUsers().end()))
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

Channel &	Channel::operator=(Channel const & src)
{
	this->name = src.getName();
	delete this->users;
	this->users = new std::vector<User *>(src.getUsers().begin(), src.getUsers().end());
	return *this;
}

std::string	Channel::getName() const
{
	return this->name;
}

std::vector<User *> &	Channel::getUsers() const
{
	return *(this->users);
}
