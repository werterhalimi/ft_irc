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

std::string part(Cmd * cmd, Server & server, User & usr)
{
	Cmd							reply(usr);
	std::vector<std::string>	params = cmd->getParams();
	std::string					*channels = 0;
	std::string					*reasons = 0;
	Channel 					*channel;
	if (params.size() < 1)
	{
		reply.setCmd(ERR_NEEDMOREPARAMS);
		reply.addParam(cmd->getCmd());
		reply.addParam(":Not enough parameters");
		return (reply.toString());
	}
	channels = split(params.at(0), ",");
	if (params.size() >= 2)
		reasons = split(params.at(1), ",");
	int	i = 0;
	int	no_keys = get_split_size(reasons);
	while (!channels[i].empty())
	{
		Cmd	tmp(usr);
		channel = server.getChannelByName(channels[i]);
		if (!channel)
		{
			tmp.setCmd(ERR_NOSUCHCHANNEL);
			tmp.addParam(usr.getNickname());
			tmp.addParam(channels[i]);
			tmp.addParam(":No such channel");
			usr.sendReply(tmp.toString());
		}
		else if (!channel->hasUser(usr))
		{
			tmp.setCmd(ERR_NOTONCHANNEL);
			tmp.addParam(usr.getNickname());
			tmp.addParam(channels[i]);
			tmp.addParam(":You're not on that channel");
		}
		else
		{
			if (i < no_keys)
				channel->removeUser(server, usr, &reasons[i]);
			else
				channel->removeUser(server, usr, 0);
		}
		i++;
	}
	return ("");
}
