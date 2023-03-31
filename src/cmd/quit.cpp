/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:40:42 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/31 18:07:16 by shalimi          ###   ########.fr       */
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
	try
	{
		server.handleLogout(*cmd, usr, reason);
	}
	catch (std::exception &e)
	{
		throw std::exception();
	}
	return (""); 
}
