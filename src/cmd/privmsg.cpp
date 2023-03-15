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
	(void) server;
	if (cmd->getParams().empty())
	{
		reply.setCmd(ERR_NORECIPIENT);
		reply.addParams(":No recipient given");
		reply.addParams(cmd->getCmd());
	}
	else if (cmd->getParams().back().empty())
	{
		reply.setCmd(ERR_NOTEXTTOSEND);
		reply.addParams(":No text to send");
	}
//	server.send(user, reply.)
	return (reply.toString());
}

