/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:40:42 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/22 18:30:08 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"

std::string quit(Cmd * cmd, Server & server, User & usr)
{
	(void) cmd;
	Cmd reply(server);
	reply.setCmd("ERROR");
	reply.addParams(cmd->getParams());
	usr.sendReply(reply.toString());
	server.handleLogout(usr, cmd->getParams());
	return ("");
}
