/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:38:18 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/20 20:26:20 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "Channel.h"
#include "Server.h"

static bool	isNameValid(std::string const & name)
{
	if (name.find(0x20) != std::string::npos)
		return false;
	if (name.find(0x07) != std::string::npos)
		return false;
	if (name.find(0x2C) != std::string::npos)
		return false;
	return (true);
}

std::string	join(Cmd * cmd, Server & server, User & usr)
{
	std::vector<std::string>	params = cmd->getParams();
	std::string					*channels = NULL;
	std::string					*keys = NULL;
	Channel 					*channel;

	if (params.empty())
		return (err_needmoreparams(usr, *cmd));
	channels = split(params.at(0), ",");
	if (params.size() >= 2)
		keys = split(params.at(1), ",");
	int	i = 0;
	int	no_keys = get_split_size(keys);
	while (!channels[i].empty())
	{
		channel = server.getChannelByName(channels[i]);
		if (!channel)
		{
			if (!isNameValid(channels[i]))
				usr.sendReply(err_badchanmask(usr, channels[i]));
			else
				usr.sendReply(err_nosuchchannel(usr, channels[i]));
		}
		// TOOMANYCHANNEL ?
		else if (!channel->getKey().empty())
		{
			if (!channel->getKey().empty() && i < no_keys && channel->getKey() != keys[i])
				usr.sendReply(err_badchannelkey(usr, channels[i]));
		}
		else if (channel->isBanned(usr))
			usr.sendReply(err_bannedfromchan(usr, channels[i], "b"));
		else if(channel->isFull())
			usr.sendReply(err_bannedfromchan(usr, channels[i], "l"));
		else if(channel->isInviteOnly())
			usr.sendReply(err_bannedfromchan(usr, channels[i], "i"));
		else
			channel->addUser(server, usr);
		i++;
	}
	return ("");
}
