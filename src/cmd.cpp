/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:12:29 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/13 16:07:18 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"
#include "cmd.h"

Cmd::Cmd(std::string const &msg)
{
	this->parse(msg);
}

Cmd::Cmd(User const &user) : _prefix(user.prefix())
{

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
			this->_params[i] = cmd.getOneParam(i);
	}
	return (*this);
}

std::string 	Cmd::toString() const
{
	std::ostringstream stream;
	stream << this->_prefix << this->_cmd << " ";
	std::vector<std::string>::const_iterator it = this->_params.begin();
	std::vector<std::string>::const_iterator ite = this->_params.end();
	while (it != ite)
	{
		stream << *it << " ";
		it++;
	}
	stream << "\r\n";
	std::string str = stream.str();
	return (str);
}

static size_t	findLength(std::string const &msg, size_t index, size_t end)
{
	size_t	length;

	length = msg.find(' ', index + 1);
	if (length == std::string::npos)
		return (end - index);
	return (length - index);
}

void	Cmd::parse(std::string const &msg)
{
	size_t	index;
	size_t	length;
	size_t	end;
	size_t	i;

	index = 0;
	end = msg.find('\0', 0);
	if (end == std::string::npos)
		return;
	if (msg[index] == ':')
	{
		index = msg.find(' ', 0);
		_prefix = msg.substr(0, index);
	}
	length = findLength(msg, index, end);
	_cmd = msg.substr(index, length);
	index += length;
	for (i = 0; i < NB_PARAMS - 1; ++i)
	{
		if (msg[index + 1] == ':' || msg[index] == '\0')
			break;
		length = findLength(msg, index, end);
		_params[i] = msg.substr(index, length);
		index += length;
	}
	if (msg[index] == '\0')
		return;
	_params[i] = msg.substr(index, end - index);
}
/*
std::string	reply(User &user, std::string const & cmd, std::string const & msg)
{
	std::string	toSend;

	toSend.append(":");
	toSend.append(user.getNickname());
	toSend.append("@");
	toSend.append(user.getUsername());
	toSend.append("!");
	toSend.append(user.getHostname());
	toSend.append(" ");
	toSend.append(cmd);
	toSend.append(msg);
	toSend.append("\r\n");
	return (toSend);
}
*/
std::string	Cmd::execute(Server &server, User &currentUser)
{
	static std::string	(*executeFct[NB_CMD])(Cmd *cmd, Server &servr, User &currentUsr) = {
		&pass,		&nick,		&user
	};
	/*
	 * ,		&oper,
		&mode,		&service,	&quit,		&squit,
		&join,		&part,		&topic,	&names,
		&list,		&invite,	&kick,		&privmsg,
		&notice,	&motd,		&luser,	&version,
		&stats,	&links,	&time,		&connect,
		&trace,	&admin,	&info,		&servlist,
		&squery,	&who,		&whois,	&whowas,
		&kill,		&ping,	&pong,	&error,
		&away,	&rehash,	&die,		&restart,
		&summon,	&users,	&wallops,	&usehost,
		&ison
	};*/

	for (size_t i = 0; i < NB_CMD; ++i)
	{
		if (_cmd == this->getCmdNames(i))
			return (executeFct[i](this, server, currentUser));
	}
	return ("");
	//throw std::exception();
}

std::string const	&Cmd::getCmdNames(size_t i) const
{
	static std::string	cmdNames[NB_CMD] = {
		"PASS",	"NICK",		"USER"
	};
	/*
	"OPER",
		"MODE",	"SERVICE",	"QUIT",	"SQUIT",
		"JOIN",	"PART",	"TOPIC",	"NAMES",
		"LIST",	"INVITE",	"KICK",	"PRIVMSG",
		"NOTICE",	"MOTD",	"LUSERS",	"VERSION",
		"STATS",	"LINKS",	"TIME",	"CONNECT",
		"TRACE",	"ADMIN",	"INFO",	"SERVLIST",
		"SQUERY",	"WHO",		"WHOIS",	"WHOWAS",
		"KILL",	"PING",	"PONG",	"ERROR",
		"AWAY",	"REHASH",	"DIE",	"RESTART",
		"SUMMON",	"USERS",	"WALLOPS",	"USERHOST",
		"ISON"
	};*/

	return (cmdNames[i]);
}

std::string const	&Cmd::getCmd() const
{
	return (this->_cmd);
}

std::vector<std::string> const	&Cmd::getParams() const
{
	return (this->_params);
}

std::string const	&Cmd::getOneParam(size_t i) const
{
	return (this->_params[i]);
}

void	Cmd::setCmd(std::string const &cmd)
{
	this->_cmd = cmd;
}

void	Cmd::addParams(std::string const &param)
{
	this->_params.push_back(param);
}

