/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 23:04:28 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/31 16:44:15 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

/* Static functions */
static void	stop(Bot const * bot, User const * sender, std::vector<std::string> const & params);
static void	create(Bot const * bot, User const * sender, std::vector<std::string> const & params);
static void	del(Bot const * bot, User const * sender, std::vector<std::string> const & params);
static std::string	nicknameFromPrefix(std::string const & prefix);
static std::vector<std::string>	messageToParams(std::string const & prefix);

/* Public */

/* Constructors & Destructor */

Bot::Bot(std::string const & name, Server & server) :
	User(name, name, "BotLand"),
	_server(&server)
{}

Bot::~Bot(){}

/* Getter */

Server &	Bot::getServer() const
{
	return *(this->_server);
}

/* Functions */

void	Bot::reply(User const * user, std::string const & message) const
{
	user->sendReply(rpl_privmsg(*this, user->getNickname(), message));
}

void	Bot::sendReply(std::string const & reply) const
{
	static void	(*executeFct[NB_BOT_CMD])(Bot const * bot, User const * usr, std::vector<std::string> const & params)  = {
		&stop, &create, &del
	};
	static std::string	cmdNames[NB_BOT_CMD] = {
		"stop", "create", "delete"
	};

	User *	sender = this->_server->getUserByName(nicknameFromPrefix(reply));
	if (!sender) return ;
	std::vector<std::string>	params = messageToParams(reply);

	if (sender->isOperator() && !params.empty())
	{
		for (int i = 0; i < NB_BOT_CMD; i++)
		{
			if (params[0] == cmdNames[i])
				return executeFct[i](this, sender, params);
		}
		this->reply(sender, std::string("Hello, I'm MAB. I accept the following commands:"));
		this->reply(sender, std::string("<create/delete> <channelName> <slots>"));
		this->reply(sender, std::string("<stop>"));
		return ;
	}
	this->reply(sender, std::string("Hello, I'm MAB, the bot of this awsome server."));
	this->reply(sender, std::string("Here is the list of the avalaible channels: "));
	std::vector<Channel *>::const_iterator ite = this->_server->getChannels().end();
	for (std::vector<Channel *>::const_iterator it = this->_server->getChannels().begin(); it != ite; it++)
	{
		std::string line("Name: ");
		line.append((*it)->getName());
		line.append(" User(s): ");
		line.append(itos((int)(*it)->getUsers().size()));
		line.append("/");
		line.append(itos((int)(*it)->getSlots()));
		line.append("\n");
		this->reply(sender, line);
	}
}

/* Private */

/* Constructors */

Bot::Bot() : User(), _server() {}

Bot::Bot(Bot const & src) :
	User(src), _server()
{
	*this = src;
}

/* Overload operators */

Bot &	Bot::operator=(Bot const & src)
{
	if (this != & src)
	{
		User::operator=(src);
		this->_server = src._server;
	}
	return *this;
}

/* Commands */

static void	stop(Bot const * bot, User const * sender, std::vector<std::string> const & params)
{
	(void) sender;
	(void) params;
	return bot->getServer().stop();
}

static void	create(Bot const * bot, User const * sender, std::vector<std::string> const & params)
{
	if (params.size() != 3)
		return bot->reply(sender, std::string("Wrong input, try: create <NAME> <SLOTS>"));
	const std::string &	name = params[1];
	if (bot->getServer().getChannelByName(name))
		return bot->reply(sender, std::string("This channel already exist"));
	bot->getServer().createChannel(name, stoi(params[2]));
	return bot->reply(sender, std::string("The channel was succesfully created"));

}

static void	del(Bot const * bot, User const * sender, std::vector<std::string> const & params)
{
	Channel *	channel;
	if(params.size() != 2)	
		return bot->reply(sender, std::string("Wrong input, try: delete <NAME>"));
	const std::string &	name = params[1];
	channel = bot->getServer().getChannelByName(name);
	if (!channel)
		return bot->reply(sender, std::string("This channel doesn't exist"));
	bot->getServer().removeChannel(channel);
	return bot->reply(sender, std::string("The channel was succesfully deleted"));

}

/* Static function */

static std::string	nicknameFromPrefix(std::string const & prefix)
{
	std::string ret;
	if (prefix.empty() || prefix[0] != ':') return ret;
	size_t	index = prefix.find('!');
	if (index == std::string::npos) return ret;
	ret = prefix.substr(1, index - 1);
	return ret;
}

static std::vector<std::string>	messageToParams(std::string const & prefix)
{
	std::vector<std::string>	tmp = split(prefix, ":");
	std::vector<std::string>	ret = split(tmp.back(), " ");
	size_t						i = ret.back().find("\r\n");
	if (i != std::string::npos)
		ret[ret.size() - 1] = ret[ret.size() - 1].substr(0, i);
	return ret;
}
