/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:40:15 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/16 16:03:32 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"

std::string	pass(Cmd * cmd, Server & server, User & usr)
{
	Cmd reply(usr);
	if (cmd->getParams().empty())
	{
		reply.setCmd(ERR_NEEDMOREPARAMS);
		reply.addParams(cmd->getCmd());
		reply.addParams(":Not enough parameters");
		return (reply.toString());
	}
	else if (usr.hasPass())
	{
		reply.setCmd(ERR_ALREADYREGISTRED);
		reply.addParams(":Unauthorized command (already registered");
		return (reply.toString());
	}
	else if (cmd->getParams().back() != server.getPass())
	{
		reply.setCmd(ERR_PASSWDMISMATCH);
		reply.addParams(":Password incorrect");
		return (reply.toString());
	}
	usr.auth();
	return ("");
}
