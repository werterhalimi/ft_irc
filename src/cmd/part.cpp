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
	std::string					*channels = NULL;
	std::string					*reasons = NULL;
	Channel 					*channel;

	if (params.empty())
		return (err_needmoreparams(usr, *cmd));
	channels = split(params.at(0), ",");
	if (params.size() >= 2)
		reasons = split(params.at(1), ",");
	int	i = 0;
	int	no_keys = get_split_size(reasons);
	while (!channels[i].empty())
	{
		channel = server.getChannelByName(channels[i]);
		if (!channel)
			usr.sendReply(err_nosuchchannel(usr, channels[i]));
		else if (!channel->hasUser(usr))
		{
			usr.sendReply(err_notonchannel(usr, channels[i]));
		}
		else
		{
			if (i < no_keys)
				channel->removeUser(server, usr, &reasons[i]);
			else
				channel->removeUser(server, usr, NULL);
		}
		i++;
	}
	return ("");
}
