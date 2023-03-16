/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:40:24 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/13 13:40:25 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"

std::string	ping(Cmd * cmd, Server & server, User & usr)
{
	Cmd reply(usr);
	(void) server;
	std::vector<std::string> params = cmd->getParams();
	if (params.empty() || params[0].empty())
	{
		reply.setCmd(ERR_NOORIGIN);
		reply.addParams(":No origin specified");
		return (reply.toString());
	}
	reply.setCmd("PONG");
	reply.addParams(params[0]);
	return (reply.toString());
}
