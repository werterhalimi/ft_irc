/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:12:29 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/16 17:28:33 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "cmd.h"

Cmd::Cmd(std::string const &msg, Server * server) :_params(*(new std::vector<std::string>())), _server(server)
{
	this->parse(msg);
}

Cmd::Cmd(User const &user) : _prefix(user.prefix()), _params(*(new std::vector<std::string>()))
{

}

Cmd::Cmd(Server const &server) : _prefix(server.prefix()), _params(*(new std::vector<std::string>()))
{

}


Cmd::~Cmd()
{
	delete &(this->_params);
}

Cmd::Cmd()  :  _params(*(new std::vector<std::string>()))
{}

Cmd::Cmd(Cmd const &cmd) : _params(*(new std::vector<std::string>()))
{
	*this = cmd;
}

Cmd	&Cmd::operator=(Cmd const &cmd)
{
	if (this != &cmd)
	{
		this->_cmd = cmd.getCmd();
		for (size_t i = 0; i < NB_PARAMS; ++i)
			this->_params.push_back(cmd.getOneParam(i));
	}
	return (*this);
}

std::string 	Cmd::toString() const
{
	std::ostringstream stream;
	stream << this->_prefix << this->_cmd;
	std::vector<std::string>::const_iterator ite = this->_params.end();
	for (std::vector<std::string>::const_iterator it = this->_params.begin(); it < ite; ++it)
		stream << " " << *it;
	stream << "\r\n";
	std::string str = stream.str();
	std::cout << "ToString" << str << std::endl;
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
	end = msg.size();
	if (msg.empty())
		return;
	if (msg[index] == ':')
	{
		index = msg.find(' ', 0);
		this->_prefix = msg.substr(0, index);
	}
	length = findLength(msg, index, end);
	this->_cmd = msg.substr(index, length);
	index += length;
	for (i = 0; i < NB_PARAMS - 1; ++i)
	{
		if (msg[index + 1] == ':' || msg[index] == '\0')
			break;
		length = findLength(msg, index, end);
		this->_params.push_back(msg.substr(index + 1, length - 1));
		index += length;
	}
	if (msg[index] == '\0')
		return;
	this->_params.push_back( msg.substr(index, end - index));
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
		&pass,		&nick,		&user,	&privmsg,	&ping,	&pong
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
		{
			if ((i != 0 && !currentUser.hasPass()) || (i > 2 && !currentUser.isLog()))
			{
				Cmd reply(*(this->_server));
				reply.setCmd(ERR_PASSWDMISMATCH);
				reply.addParam(":Password incorrect");
				currentUser.sendReply(reply.toString());
				continue ;
			}
			currentUser.sendReply(executeFct[i](this, server, currentUser));

		}
	}
	return ("");
	//throw std::exception();
}

std::string const	&Cmd::getCmdNames(size_t i) const
{
	static std::string	cmdNames[NB_CMD] = {
		"PASS",	"NICK",	"USER", "PRIVMSG", "PING", "PONG"
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

void	Cmd::addParam(std::string const &param)
{
	this->_params.push_back(param);
}

void	Cmd::addParams(std::vector<std::string> const &params)
{
	this->_params = params;
}
