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
	(void) server;
	if (params.empty())
	{
		reply.setCmd(ERR_NORECIPIENT);
		reply.addParams(":No recipient given");
		reply.addParams(cmd->getCmd());
		return (reply.toString());
	}
	if (params.back().empty())
	{
		reply.setCmd(ERR_NOTEXTTOSEND);
		reply.addParams(":No text to send");
		return (reply.toString());
	}
	std::vector<std::string>::const_iterator ite = params.end();
	for (std::vector<std::string>::const_iterator it = params.begin(); it < ite; ++it)
	{

	}

//	server.send(user, reply.)
	return ("");
}

