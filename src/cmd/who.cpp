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
	std::vector<Channel *>::const_iterator	it;
	if (user.getUsername().find(mask) != std::string::npos)
		return true;
	if (user.getNickname().find(mask) != std::string::npos)
		return true;
	if (user.getHostname().find(mask) != std::string::npos)
		return true;
	if (user.getRealname().find(mask) != std::string::npos)
		return true;
	it = user.getChannels()->begin();
	while (it != user.getChannels()->end())
	{
		if ((*it)->getName().find(mask) != std::string::npos)
			return true;
		it++;
	}
	return false;
}

std::string	who(Cmd * cmd, Server & server, User & usr)
{
	std::vector<std::string>			params = cmd->getParams();
	std::string							query = params.at(0); // TODO !!! WARNING if no params given !!!
	bool								end = false;
	std::vector<User *>::const_iterator	it;
	it = server.getUsers().begin();
	while (it != server.getUsers().end())
	{
		if ((query.empty() || user_match_mask(*(*it), query)))
		{
			usr.sendReply(rpl_whoreply(server, usr, *it));
			end = true;
		}
		it++;
	}
	if (end)
		return (rpl_endofwho(server, usr.getUsername(), query));
	return ("");
}
