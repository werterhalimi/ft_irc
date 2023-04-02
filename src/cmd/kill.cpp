/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:38:34 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/13 13:38:36 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "Server.hpp"

std::string	kill(Cmd * cmd, Server & server, User & currentUser)
{
	std::vector<std::string> params = cmd->getParams();

	if (params.size() < 2)
		return (err_needmoreparams(currentUser, *cmd));
	std::string	userName = params[0];
	User *	userKill = server.getUserByName(userName);
	if (!currentUser.isGlobalOperator() && !currentUser.isLocalOperator())
		return (err_noprivileges(currentUser));
	if (!userKill)
		return (err_nosuchnick(currentUser, userName)); // TODO ?
	userKill->sendReply(rpl_kill(currentUser, *userKill, params[1]));
	try
	{
		server.userLogout(*cmd, *userKill, params[1]);
	}
	catch (std::exception &e)
	{
		std::cerr << BOLD_RED << "\t in kill command" << RESET_COLOR << std::endl;
		throw std::exception();
	}
	return ("");
}

