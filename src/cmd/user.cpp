/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:42:33 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/15 19:33:27 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"

std::string	user(Cmd * cmd, Server & server, User & usr)
{
	(void) server;
	Cmd					reply(usr);
	std::vector<std::string>	params = cmd->getParams();
	std::string			user = params.at(0);
	if (params.empty())
	{
		reply.setCmd(ERR_NONICKNAMEGIVEN);
		reply.addParam(":No username given");
		return (reply.toString());
	}
	else if (usr.hasUser())
	{
		reply.setCmd(ERR_ALREADYREGISTRED);
		reply.addParam(":Unauthorized command (already registered");
		return (reply.toString());
	}
	usr.setUsername(user);
	if (usr.isLog())
		usr.welcome();
	return ("");
}
