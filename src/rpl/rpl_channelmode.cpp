/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_channelmode.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:56:13 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/29 11:56:14 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"
# include "Channel.hpp"

static std::string	updateChannelMode(int flags, Channel & channel, bool value)
{
	std::ostringstream stream;

	if (flags && value)
		stream << "+";
	else if (flags)
		stream << "-";
	if (flags & INVITE_ONLY_FLAG)
	{
		channel.setInviteOnly(value);
		stream << "i";
	}
	if (flags & PROTECTED_TOPIC_FLAG)
	{
		channel.setProtectedTopic(value);
		stream << "t";
	}
	if (flags & CLIENT_LIMIT_FLAG)
	{
		channel.setClientLimit(value);
		stream << "l";
	}
	if (flags & BAN_CHANNEL_FLAG)
	{
		channel.setBanChannel(value);
		stream << "b";
	}
	return (stream.str());
}

std::string	rpl_channelmode(Channel & channel, User & user, int modeToAdd, int modeToRemove)
{
	Cmd reply(user);

	reply.setCmd("MODE");
	reply.addParam(channel.getName());
	std::ostringstream stream;
	stream << updateChannelMode(modeToAdd, channel, true);
	stream << updateChannelMode(modeToRemove, channel, false);
	reply.addParam(stream.str());
	return (reply.toString());
}
