/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:12:29 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/12 14:12:31 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"

Cmd::Cmd(std::string const &msg)
{
	this->parse(msg);
	this->execute();
}

Cmd::~Cmd()
{}

Cmd::Cmd()
{}

Cmd::Cmd(Cmd const &cmd)
{
	*this = cmd;
}

Cmd	&Cmd::operator=(Cmd const &cmd)
{
	if (this != &cmd)
	{
		this->_cmd = cmd.getCmd();
		for (size_t i = 0; i < NB_PARAMS; ++i)
			this->_params[i] = cmd.getParams(i);
	}
	return (*this);
}

void	Cmd::parse(std::string const &msg)
{
	size_t	index;
	size_t	length;

	index = 0;
	if (msg[index] == ':')
	{
		index = msg.find(' ', 0);
	}
	length = msg.find(' ', index);
	_cmd = msg.substr(index, length);
	index = length;

}

std::string	Cmd::reply(User &user)
{
	std::string	toSend;

	toSend.append(":");
	toSend.append(user.getNickname());
	toSend.append("@");
	toSend.append(user.getUsername());
	toSend.append("!");
	toSend.append(user.getHostname());
	toSend.append(" ");
	toSend.append(this->_cmd);
	for (size_t i = 0; i < NB_PARAMS; ++i)
	{
		toSend.append(" ");
		toSend.append(this->_params[i]);
	}
	toSend.append("\r\n");
	return (toSend);
}


void	Cmd::execute()
{
	static void	(*executeFct[NB_CMD])(Cmd *cmd) = {
//		&Cmd::pass,
//		...
	};

	for (size_t i = 0; i < NB_CMD; ++i)
	{
		if (_cmd == this->getCmdNames(i))
		{
			executeFct[i](this);
			break;
		}
	}
	throw std::exception();
}

std::string const	&Cmd::getCmdNames(size_t i) const
{
	static std::string	cmdNames[NB_CMD] = {
		"PASS",		"NICK",		"USER",		"OPER",
		"MODE",		"SERVICE",	"QUIT",	"SQUIT",
		"JOIN",		"PART",	"MODE",	"TOPIC",
		"NAMES",		"LIST",	"INVITE",	"KICK",
		"PRIVMSG",		"NOTICE",	"MOTD",	"LUSERS",
		"VERSION",		"STATS",	"LINKS",	"TIME",
		"CONNECT",		"TRACE",	"ADMIN",	"INFO",
		"SERVLIST",	"SQUERY",	"WHO",	"WHOIS",
		"WHOWAS",		"KILL",	"PING",	"PONG",
		"ERROR",		"AWAY",	"REHASH",	"DIE",
		"RESTART",	"SUMMON",	"USERS",	"WALLOPS",
		"USERHOST",	"ISON"
	};

	return (cmdNames[i]);
}

std::string const	&Cmd::getCmd() const
{
	return (this->_cmd);
}

std::string const	&Cmd::getParams(size_t i) const
{
	return (this->_params[i]);
}
