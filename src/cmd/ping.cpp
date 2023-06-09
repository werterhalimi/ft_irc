/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:40:24 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/16 17:17:03 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"

std::string	ping(Cmd * cmd, Server & server, User & usr)
{
	Cmd reply(server);

	std::vector<std::string> params = cmd->getParams();
	if (params.empty() || params[0].empty())
		return (err_noorigin(server, usr));
	reply.setCmd("PONG");
	reply.addParam(params[0]);
	return (reply.toString());
}
