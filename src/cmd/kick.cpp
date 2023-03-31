/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:38:27 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/13 13:38:30 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "Server.hpp"

std::string	kick(Cmd * cmd, Server & server, User & currentUser)
{
	std::vector<std::string> params = cmd->getParams();

	if (params.size() < 2)
		return (err_needmoreparams(currentUser, *cmd));
	std::string	channelName = params[0];
	Channel *	channel = server.getChannelByName(channelName);
	if (!channel)
		return (err_nosuchchannel(currentUser, channelName));
	if (!currentUser.isGlobalOperator() && !currentUser.isLocalOperator())
		return (err_chanoprivsneeded(*channel, currentUser));
	if (!channel->hasUser(currentUser))
		return (err_notonchannel(currentUser, channelName));
	std::string msg = params.back();
	std::vector<std::string>::const_iterator ite = params.end();
	if (msg[0] != ':')
		msg = ":" + currentUser.getNickname();
	else
		ite--;
	User *	userToKick;
	std::vector<User *>	users = channel->getUsers();
	for (std::vector<std::string>::const_iterator it = params.begin() + 1; it < ite; ++it)
	{
		userToKick = channel->getUserByName(*it);
		if (!userToKick)
			currentUser.sendReply(err_usernotinchannel(*channel, currentUser, *it));
		else
			channel->removeUser1Channel(*userToKick, rpl_kick(*channel, currentUser, *it, msg));
	}
	return ("");
}
