/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 23:04:28 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/30 18:29:55 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include <sstream>

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

void	Bot::reply(User const * user, std::string message) const
{
	user->sendReply(rpl_privmsg(*this, user->getNickname(), message));
}

void	Bot::sendReply(std::string const & reply) const
{
	User *	sender = this->_server->getUserByName(nicknameFromPrefix(reply));
	if (!sender) return ;
	std::vector<std::string>	params = messageToParams(reply);
	if (sender->isOperator())
	{
		if (params.size() == 1 && params[0] == "stop\r\n")
			return this->_server->stop();
		if (params.size() < 2 || (params[0] != "create" && params[0] != "delete"))
		{
			this->reply(sender, std::string("Hello, I'm MAB. I accept the following commands:"));
			this->reply(sender, std::string("<create/delete> <channelName> <slots>"));
			this->reply(sender, std::string("<stop>"));
		}
		Channel *	channel;
		if (params[0] == "create" && params.size() == 3)
		{
			std::string	name = params[1];
			if (this->_server->getChannelByName(name))
				return this->reply(sender, std::string("This channel already exist"));
			this->_server->createChannel(name, stoi(params[2]));
			return this->reply(sender, std::string("The channel was succesfully created"));
		}
		else if (params[0] == "delete")
		{
			std::string	name = params[1].substr(0, params[1].size() - 2);
			channel = this->_server->getChannelByName(name);
			if (!channel)
				return this->reply(sender, std::string("This channel doesn't exist"));
			this->_server->removeChannel(channel);
			return this->reply(sender, std::string("The channel was succesfully deleted"));
		}
		else
			return this->reply(sender, std::string("Hello, I'm MAB. I accept the following commands: <create/delete> <channelName> <slots>"));
	}
	else
	{
		this->reply(sender, std::string("Hello, I'm MAB, the bot of this awsome server."));
		this->reply(sender, std::string("Here is the list of the avalaible channels: "));
		std::vector<Channel *>::const_iterator it = this->_server->getChannels().begin();
		while (it != this->_server->getChannels().end())
		{
			std::string line("Name: ");
			line.append((*it)->getName());
			line.append(" User(s): ");
			line.append(itos((*it)->getUsers().size()));
			line.append("/");
			line.append(itos((*it)->getSlots()));
			line.append("\n");
			this->reply(sender, line);
			it++;
		}
		return ;
	}
}
