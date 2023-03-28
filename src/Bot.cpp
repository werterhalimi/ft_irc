/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 23:04:28 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/29 00:28:27 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

Bot::Bot(void) : User(){}
Bot::Bot(std::string name, Server & server) : User(name, name, "BotLand"), _server(&server) {}
Bot::~Bot(void){}
Bot::Bot(Bot const & src) : User(){ (void) src; }
Bot &	Bot::operator=(Bot const & src)
{
	(void) src;
	return *this;
}


static std::string	nicknameFromPrefix(std::string const & prefix)
{
	std::string ret;
	if (prefix.empty() || prefix[0] != ':') return ret;
	size_t	index = prefix.find("!");
	if (index == std::string::npos) return ret;
	ret = prefix.substr(1, index - 1);
	return ret;
}

static std::vector<std::string>	messageToParams(std::string const & prefix)
{
	std::vector<std::string>	tmp = split(prefix, ":");
	return (split(tmp.back(), " "));
}



void	Bot::sendReply(std::string const & reply) const
{
	User *	sender = this->_server->getUserByName(nicknameFromPrefix(reply));
	if (!sender) return ;
	std::vector<std::string>	params = messageToParams(reply);	
	(void) sender;
	(void) params;
}
