/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:38:00 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/27 17:00:32 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "Server.hpp"

std::string	invite(Cmd * cmd, Server & server, User & usr)
{
	std::vector<std::string>	params = cmd->getParams();
	if (params.size() != 2)
		return (err_needmoreparams(usr, *cmd));
	Channel	*channel = server.getChannelByName(params.at(1));
	User	*user = server.getUserByName(params.at(0));
	if (!channel)
		return (err_nosuchchannel(usr, params.at(1)));
	if (!channel->hasUser(usr))
		return (err_notonchannel(usr, channel->getName()));
	if (!user)
		return (err_nosuchnick(usr, params.at(0)));
	if (channel->hasUser(*user))
		return (err_useronchannel(*user, channel->getName()));
	if (!usr.isGlobalOperator() && !usr.isLocalOperator())
		return (err_chanoprivsneeded(*channel, usr));
	channel->addInvitedUser(user);
	usr.sendReply(rpl_inviting(usr, *user, channel->getName()));
	user->sendReply(rpl_invite(usr, *user, channel->getName()));
	return ("");
}
