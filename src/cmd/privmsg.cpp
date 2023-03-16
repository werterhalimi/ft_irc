/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:40:35 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/13 13:40:36 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"

std::string	privmsg(Cmd * cmd, Server & server, User & usr)
{
	Cmd reply(usr);
	std::vector<std::string> params = cmd->getParams();
	if (params.empty() || (params.size() == 1 && params[1][0] == ':'))
	{
		reply.setCmd(ERR_NORECIPIENT);
		reply.addParams(":No recipient given");
		reply.addParams(cmd->getCmd());
		return (reply.toString());
	}
	if (params.size() == 1)
	{
		reply.setCmd(ERR_NOTEXTTOSEND);
		reply.addParams(":No text to send");
		return (reply.toString());
	}
//	std::string tmp = params.back();
//	if (tmp[0] != ':')
//	{
//		params.pop_back();
//		params.push_back(std::string(":" + tmp));
//	}
	std::vector<std::string>::const_iterator ite = params.end();
	for (std::vector<std::string>::const_iterator it = params.begin(); it < ite; ++it)
	{
		if ((*it)[0] == '#')
		{
			int id = server.getChannelID(*it);
			if (id < 0)
				; // TODO No channel ?
			else
				; // TODO Send all user in channel
		}
		else if ((*it)[0] != '$')
		{
			int id = server.getUserID(*it);
			if (id < 0)
			{
				reply.setCmd(ERR_NOSUCHNICK);
				reply.addParams(*it);
				reply.addParams(":No such nick/channel");
				return (reply.toString());
			}
			else
				; // TODO Send to user
		}
	}

//	server.send(user, reply.)
	return ("");
}

