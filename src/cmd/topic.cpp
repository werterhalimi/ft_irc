/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:42:20 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/13 13:42:22 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "Server.h"
#include "Channel.h"

std::string	topic(Cmd * cmd, Server & server, User & usr)
{
	std::vector<std::string> params = cmd->getParams();

	if (params.empty())
		return (err_needmoreparams(usr, *cmd));
	std::string	channelName = params[0];
	Channel *	channel = server.getChannelByName(channelName);
	if (!channel)
		return (err_nosuchchannel(usr, channelName));
	if (channel->isProtectedTopic() && !usr.isGlobalOperator() && !usr.isLocalOperator())
		return (err_chanoprivsneeded(*channel, usr));
	if (!channel->hasUser(usr))
		return (err_notonchannel(usr, channelName));
	if (params.size() == 1)
	{
		if (channel->getTopic().empty())
			return (rpl_notopic(server, *channel, usr));
		return (rpl_topic(server, *channel, usr));
	}
	std::string topic = params[1];
	if (topic[0] != ':')
		return ("");
	if (topic.size() == 1)
		channel->setTopic("");
	else
		channel->setTopic(topic.substr(1, topic.size() - 1));
	std::string reply = rpl_topic(server, *channel, usr);
	std::vector<User *>	users = channel->getUsers();
	std::vector<User *>::const_iterator ite = users.end();
	for (std::vector<User *>::const_iterator it = users.begin(); it < ite; ++it)
		(*it)->sendReply(reply);
//	usr.sendReply(rpl_topicwhotime); // TODO ?
	return ("");
}
