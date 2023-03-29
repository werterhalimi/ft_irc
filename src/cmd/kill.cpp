/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:38:34 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/13 13:38:36 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "Server.h"

std::string	kill(Cmd * cmd, Server & server, User & usr)
{
	std::vector<std::string> params = cmd->getParams();

	if (params.size() < 2)
		return (err_needmoreparams(usr, *cmd));
	std::string	userName = params[0];
	User *	userKill = server.getUserByName(userName);
	if (!usr.isGlobalOperator() && !usr.isLocalOperator())
		return (err_noprivileges(usr));
	if (!userKill)
		return (err_nosuchnick(usr, userName)); // TODO ?
//	std::string quitMsg = rpl_kill(usr, *userKill, params[1]);
	userKill->sendReply(rpl_kill(usr, *userKill, params[1]));
	server.handleLogout(*cmd, *userKill, params[1]);

/*	Channel *	channel = server.getChannelByName(channelName);
	if (!channel)
		return (err_nosuchchannel(usr, channelName));
	if (!usr.isGlobalOperator() && !usr.isLocalOperator())
		return (err_chanoprivsneeded(*channel, usr));
	if (!channel->hasUser(usr))
		return (err_notonchannel(usr, channelName));
	std::string msg = params.back();
	std::vector<std::string>::const_iterator ite = params.end();
	if (msg[0] != ':')
		msg = ":" + usr.getNickname();
	else
		ite--;
	User *	userToKick;
	std::vector<User *>	users = channel->getUsers();
	for (std::vector<std::string>::const_iterator it = params.begin() + 1; it < ite; ++it)
	{
		userToKick = channel->getUserByName(*it);
		if (!userToKick)
			usr.sendReply(err_usernotinchannel(*channel, usr, *it));
		else
			channel->removeUser(*userToKick, rpl_kick(*channel, usr, *it, msg));
	}
*/	return ("");
}

