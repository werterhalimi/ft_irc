/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:46:44 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/23 18:39:09 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "Server.hpp"

static bool user_match_mask(User & user, std::string const & mask)
{
	if (user.getUsername().find(mask) != std::string::npos)
		return true;
	if (user.getNickname().find(mask) != std::string::npos)
		return true;
	if (user.getHostname().find(mask) != std::string::npos)
		return true;
	if (user.getRealname().find(mask) != std::string::npos)
		return true;
	std::vector<Channel *>::const_iterator	ite = user.getChannels()->end();
	for (std::vector<Channel *>::const_iterator it = user.getChannels()->begin(); it != ite ; ++it)
		if ((*it)->getName().find(mask) != std::string::npos)
			return true;
	return false;
}

std::string	who(Cmd * cmd, Server & server, User & usr)
{
	std::vector<std::string>	params = cmd->getParams();
	bool						end = false;

	if (params.empty())
		return (err_needmoreparams(usr, *cmd));
	std::string	query = params.at(0);
	std::vector<User *>::const_iterator	ite = server.getUsers().end();
	for (std::vector<User *>::const_iterator it = server.getUsers().begin(); it != ite ; ++it)
	{
		if ((query.empty() || user_match_mask(*(*it), query)))
		{
			usr.sendReply(rpl_whoreply(server, usr, *it));
			end = true;
		}
	}
	if (end)
		return (rpl_endofwho(server, usr.getUsername(), query));
	return ("");
}
