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
#include "Server.hpp"

std::string quit(Cmd * cmd, Server & server, User & usr)
{
	std::string reason;
	std::vector<std::string> params = cmd->getParams();
	if (!params.empty())
		reason = params[0];
	server.handleLogout(*cmd, usr, reason);
	return (""); // TODO ?
}
