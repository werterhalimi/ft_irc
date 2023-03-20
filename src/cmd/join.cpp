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
	Cmd							reply(usr);
	std::vector<std::string>	params = cmd->getParams();
	std::string					*channels = 0;
	std::string					*keys = 0;
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
		keys = split(params.at(1), ",");
	int	i = 0;
	int	no_keys = get_split_size(keys);
	while (!channels[i].empty())
	{
		Cmd	tmp(usr);
		channel = server.getChannelByName(channels[i]);
		if (!channel)
		{
			if (!isNameValid(channels[i]))
			{
				tmp.setCmd(ERR_BADCHANMASK);
				tmp.addParam(channels[i]);
				tmp.addParam(":Bad Channel Mask");
				usr.sendReply(tmp.toString());
			}
			else
			{
				tmp.setCmd(ERR_NOSUCHCHANNEL);
				tmp.addParam(usr.getNickname());
				tmp.addParam(channels[i]);
				tmp.addParam(":No such channel");
				usr.sendReply(tmp.toString());
			}
		}
		// TOOMANYCHANNEL ?
		else if (!channel->getKey().empty())
		{
			if (!channel->getKey().empty() && i < no_keys && channel->getKey() != keys[i])
			{
				tmp.setCmd(ERR_BADCHANNELKEY);
				tmp.addParam(usr.getNickname());
				tmp.addParam(channels[i]);
				tmp.addParam(":Cannot join channel (+k)");
				usr.sendReply(tmp.toString());
			}
		}
		else if (channel->isBanned(usr))
		{
			tmp.setCmd(ERR_BANNEDFROMCHAN);
			tmp.addParam(usr.getNickname());
			tmp.addParam(channels[i]);
			tmp.addParam(":Cannot join channel (+b)");
			usr.sendReply(tmp.toString());
		}
		else if(channel->isFull())
		{
			tmp.setCmd(ERR_BANNEDFROMCHAN);
			tmp.addParam(usr.getNickname());
			tmp.addParam(channels[i]);
			tmp.addParam(":Cannot join channel (+l)");
			usr.sendReply(tmp.toString());
		}
		else if(channel->isInviteOnly())
		{
			tmp.setCmd(ERR_BANNEDFROMCHAN);
			tmp.addParam(usr.getNickname());
			tmp.addParam(channels[i]);
			tmp.addParam(":Cannot join channel (+i)");
			usr.sendReply(tmp.toString());
		}
		else
			channel->addUser(server, usr);
		i++;
	}
	return ("");
}
