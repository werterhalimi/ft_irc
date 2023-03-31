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
#include "Server.hpp"

std::string	topic(Cmd * cmd, Server & server, User & currentUser)
{
	std::vector<std::string> params = cmd->getParams();

	if (params.empty())
		return (err_needmoreparams(currentUser, *cmd));
	std::string	channelName = params[0];
	Channel *	channel = server.getChannelByName(channelName);
	if (!channel)
		return (err_nosuchchannel(currentUser, channelName));
	if (channel->isProtectedTopic() && !currentUser.isGlobalOperator() && !currentUser.isLocalOperator())
		return (err_chanoprivsneeded(*channel, currentUser));
	if (!channel->hasUser(currentUser))
		return (err_notonchannel(currentUser, channelName));
	if (params.size() == 1)
	{
		if (channel->getTopic().empty())
			return (rpl_notopic(server, *channel, currentUser));
		return (rpl_topic(server, *channel, currentUser));
	}
	std::string topic = params[1];
	if (topic[0] != ':')
		return ("");
	if (topic.size() == 1)
		channel->setTopic("");
	else
		channel->setTopic(topic.substr(1, topic.size() - 1));
	std::string reply = rpl_topic(server, *channel, currentUser);
	std::vector<User *>	users = channel->getUsers();
	std::vector<User *>::const_iterator ite = users.end();
	for (std::vector<User *>::const_iterator it = users.begin(); it < ite; ++it)
		(*it)->sendReply(reply);
	return ("");
}
