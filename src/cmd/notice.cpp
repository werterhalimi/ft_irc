/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:05:26 by shalimi           #+#    #+#             */
/*   Updated: 2023/04/10 15:22:49 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "Server.hpp"

std::string	notice(Cmd * cmd, Server & server, User & usr)
{
	std::vector<std::string> params = cmd->getParams();
	if (params.empty() || (params.size() == 1 && params[0][0] == ':'))
		return (err_norecipient(usr, *cmd));
	if (params.size() == 1)
		return (err_notexttosend(usr));
	std::vector<std::string>::const_iterator ite = params.end();
	for (std::vector<std::string>::const_iterator it = params.begin(); it < ite - 1; ++it)
	{
		if ((*it)[0] == '#')
		{
			Channel * channel = server.getChannelByName(*it);
			if (!channel)
				return (err_nosuchnick(usr, *it));
			else
			{
				std::vector<User *> userInChannel = channel->getUsers();
				if (std::find(userInChannel.begin(), userInChannel.end(), &usr) == userInChannel.end())
					usr.sendReply(err_cannotsendtochan(usr, channel->getName()));
				else
				{
					std::vector<User *>::const_iterator itue = userInChannel.end();
					for (std::vector<User *>::const_iterator itu = userInChannel.begin(); itu < itue; ++itu)
						if (!(**itu == usr))
							(*itu)->sendReply(rpl_notice(usr, params));
				}
			}
		}
		else if ((*it)[0] != '$')
		{
			User * user = server.getUserByName(*it);
			if (!user)
				return (err_nosuchnick(usr, *it));
			else
				user->sendReply(rpl_notice(usr, params));
		}
	}
	return ("");
}

