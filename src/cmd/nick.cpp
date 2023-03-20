/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:39:44 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/15 19:36:41 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"

static bool	validNickName(std::string nick)
{
	size_t		i = 1;
	if (nick.size() > 9) return (false);
	if (isLetter(nick[0]) || isSpecial(nick[0]))
		while (i < nick.size())
		{
			if (!isLetter(nick[i]) && !isSpecial(nick[i]) \
					&& !isDigit(nick[i]) && nick[i] != '-')
				return (false);
			i++;
		}
	return (true);
}

std::string	nick(Cmd * cmd, Server & server, User & usr)
{
	Cmd							reply(usr);
	std::vector<std::string>	params = cmd->getParams();
	std::string					nick = params.at(0);

	if (!usr.hasPass())
	{
		reply.setCmd(ERR_PASSWDMISMATCH);
		reply.addParam(usr.getNickname());
		reply.addParam(":Password incorrect");
		return (reply.toString());
	}
	else if (params.empty())
	{
		reply.setCmd(ERR_NONICKNAMEGIVEN);
		reply.addParam(usr.getNickname());
		reply.addParam(":No nickname given");
		return (reply.toString());
	}
	else if (server.hasNick(nick))
	{
		reply.setCmd(ERR_NICKNAMEINUSE);
		reply.addParam(usr.getNickname());
		reply.addParam(params.at(0));
		reply.addParam(":Nickname is already in use");
		return (reply.toString());
	}
	else if (!validNickName(nick))
	{
		reply.setCmd(ERR_ERRONEUSNICKNAME);
		reply.addParam(usr.getNickname());
		reply.addParam(nick);
		reply.addParam(":Erroneous nickname");
		return (reply.toString());
	}
	usr.setNickname(nick);
	if (usr.isLog())
		usr.welcome();
	return ("");

}
