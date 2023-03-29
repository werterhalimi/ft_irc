/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:40:03 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 16:51:42 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "Channel.h"
#include "Server.h"

std::string part(Cmd * cmd, Server & server, User & usr)
{
	std::vector<std::string>	params = cmd->getParams();
	std::vector<std::string>	channels;
	std::vector<std::string>	reasons;
	Channel 					*channel;

	if (params.empty())
		return (err_needmoreparams(usr, *cmd));
	channels = split(params.at(0), ",");
	if (params.size() >= 2)
		reasons = split(params.at(1), ",");
	size_t i = 0;
	size_t	no_keys = reasons.size();
	std::vector<std::string>::const_iterator ite = channels.end();
	for (std::vector<std::string>::const_iterator it = channels.begin(); it < ite; ++it)
	{
		channel = server.getChannelByName(*it);
		if (!channel)
			usr.sendReply(err_nosuchchannel(usr, *it));
		else if (!channel->hasUser(usr))
		{
			usr.sendReply(err_notonchannel(usr, *it));
		}
		else
		{
			std::string *	reason = NULL;
			if (i < no_keys)
				reason = &reasons[i];
			channel->removeUser1Channel(usr, rpl_part(*channel, usr, reason));
		}
		i++;
	}
	return ("");
}
