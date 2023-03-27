/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_usermode.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:12:54 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 17:12:55 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"
# include "Channel.h"

static std::string	updateUserMode(int flags, User & usr, bool value)
{
	std::ostringstream stream;

	if (flags && value)
		stream << "+";
	else if (flags)
		stream << "-";
//	if (flags & AWAY_FLAG)
//	{
//		usr.setAway(value);
//		stream << "a";
//	}
	if (flags & INVISIBLE_FLAG)
	{
		usr.setInvisible(value);
		stream << "i";
	}
	if (flags & WALLOPS_FLAG)
	{
		usr.setWallops(value);
		stream << "w";
	}
	if (flags & RESTRICTED_FLAG)
	{
		usr.setRestricted(value);
		stream << "r";
	}
	if (flags & GLOBAL_OPERATOR_FLAG)
	{
		usr.setGlobalOperator(value);
		stream << "o";
	}
	if (flags & LOCAL_OPERATOR_FLAG)
	{
		usr.setLocalOperator(value);
		stream << "O";
	}
	return (stream.str());
}

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
	return (stream.str());
}

std::string	rpl_usermode(User & user, int modeToAdd, int modeToRemove)
{
	Cmd reply(user);

	reply.setCmd("MODE");
	reply.addParam(user.getNickname());
	std::ostringstream stream;
	stream << ":"; // TODO needed ?
	stream << updateUserMode(modeToAdd, user, true);
	stream << updateUserMode(modeToRemove, user, false);
	reply.addParam(stream.str());
	return (reply.toString());
}

std::string	rpl_channelmode(Server const & server, Channel & channel, int modeToAdd, int modeToRemove)
{
	Cmd reply(server);

	reply.setCmd("MODE");
	reply.addParam(channel.getName());
	std::ostringstream stream;
//	stream << ":"; // TODO needed ?
	stream << updateChannelMode(modeToAdd, channel, true);
	stream << updateChannelMode(modeToRemove, channel, false);
	reply.addParam(stream.str());
	return (reply.toString());
}
