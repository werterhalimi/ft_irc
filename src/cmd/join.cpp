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
#include "Server.hpp"

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
	std::vector<std::string>	channels;
	std::vector<std::string>	keys;
	Channel 					*channel;

	if (params.empty())
		return (err_needmoreparams(usr, *cmd));
	channels = split(params.at(0), ",");
	if (params.size() >= 2)
		keys = split(params.at(1), ",");
	size_t i = 0;
	size_t	no_keys = keys.size();
	std::vector<std::string>::const_iterator ite = channels.end();
	for (std::vector<std::string>::const_iterator it = channels.begin(); it < ite; ++it)
	{
		channel = server.getChannelByName(*it);
		if (!channel)
		{
			if (!isNameValid(*it))
				usr.sendReply(err_badchanmask(usr, *it));
			else
				usr.sendReply(err_nosuchchannel(usr, *it));
		}
		// TODO TOOMANYCHANNEL ?
		else if (!channel->getKey().empty())
		{
			if (!channel->getKey().empty() && i < no_keys && channel->getKey() != keys[i])
				usr.sendReply(err_badchannelkey(usr, *it));
		}
		else if (channel->isBanChannel() && channel->isBanned(usr))
			usr.sendReply(err_bannedfromchan(usr, *it));
		else if (channel->isFull())
			usr.sendReply(err_channelisfull(usr, *it));
		else if (channel->isInviteOnly() && !channel->isInvited(usr))
			usr.sendReply(err_inviteonlychan(usr, *it));
		else
			channel->addUser(server, usr);
		i++;
	}
	return ("");
}
