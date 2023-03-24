/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:39:22 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/13 13:39:24 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "Server.h"

static void	updateUserFlag(int *flagToAdd, int *flagToRemove, char c, User & usr, bool removeMode)
{
	switch (c)
	{
//		case 'a':
//			*flagToAdd |= AWAY_FLAG;
//			*flagToRemove &= ~AWAY_FLAG;
//			break;
		case 'i':
			*flagToAdd |= INVISIBLE_FLAG;
			*flagToRemove &= ~INVISIBLE_FLAG;
			break;
		case 'w':
			*flagToAdd |= WALLOPS_FLAG;
			*flagToRemove &= ~WALLOPS_FLAG;
			break;
		case 'r':
			*flagToAdd |= RESTRICTED_FLAG;
			*flagToRemove &= ~RESTRICTED_FLAG;
			break;
		case 'o':
			if (removeMode || usr.isOperator())
				*flagToAdd |= GLOBAL_OPERATOR_FLAG;
			*flagToRemove &= ~GLOBAL_OPERATOR_FLAG;
			break;
		case 'O':
			if (removeMode || usr.isOperator())
				*flagToAdd |= LOCAL_OPERATOR_FLAG;
			*flagToRemove &= ~LOCAL_OPERATOR_FLAG;
			break;
		default:
			break;
	}
}

static void	updateChannelFlag(int *flagToAdd, int *flagToRemove, char c, Channel & channel, bool removeMode)
{
	switch (c)
	{
		case 'i':
			*flagToAdd |= INVITE_ONLY_FLAG;
			*flagToRemove &= ~INVITE_ONLY_FLAG;
			break;
		default:
			break;
	}
}

std::string	mode(Cmd * cmd, Server & server, User & usr)
{
	bool	plusSign = true;
	int		modeToAdd = 0;
	int		modeToRemove = 0;
	std::vector<std::string> params = cmd->getParams();

	if (params.empty())
		return (err_needmoreparams(usr, *cmd));
	if (params[0][0] == '#')
	{
		int id = server.getChannelID(params[0]);
		if (id < 0)
			return (err_nosuchchannel(usr, params[0]));
		Channel channel = *server.getChannels()[id];
		if (params.size() == 1)
			return (rpl_channelmodeis(channel, usr));
		if (!usr.isGlobalOperator()) // TODO which one ?
			return (err_chanoprivsneeded(channel, usr));
		std::string validFlags = std::string(CHANNEL_MODE_FLAG_LETTERS);
		std::vector<std::string>::const_iterator ite = params.end();
		for (std::vector<std::string>::const_iterator it = params.begin() + 1; it < ite; ++it)
		{
			for (size_t i = 0; i < (*it).size(); ++i)
			{
				if ((*it)[i] == '+')
					plusSign = true;
				else if ((*it)[i] == '-')
					plusSign = false;
				else if (validFlags.find((*it)[i]) == std::string::npos)
					usr.sendReply(err_unknownmode(usr, std::string(1, (*it)[i])));
				else if (plusSign)
					updateChannelFlag(&modeToAdd, &modeToRemove, (*it)[i], channel, false);
				else
					updateChannelFlag(&modeToRemove, &modeToAdd, (*it)[i], channel, true);
			}
		}
		if (!modeToAdd && !modeToRemove)
			return ("");
		std::string reply = rpl_channelmode(server, channel, modeToAdd, modeToRemove);
		std::vector<User *>::const_iterator iteu = channel.getUsers().end();
		for (std::vector<User *>::const_iterator it = channel.getUsers().begin() + 1; it < iteu; ++it)
			(*it)->sendReply(reply);
		return ("");
	}
	else
	{
		int id = server.getUserID(params[0]);
		if (id < 0)
			return (err_nosuchnick(usr, params[0]));
		else if (server.getUsers()[id]->getNickname() != usr.getNickname())
			return (err_usersdontmatch(usr, params.size()));
		else if (params.size() == 1)
			return (rpl_umodeis(usr));
		std::string errorReply = err_umodeunknownflag(usr);
		std::string validFlags = std::string(USER_MODE_FLAG_LETTERS);
		std::vector<std::string>::const_iterator ite = params.end();
		for (std::vector<std::string>::const_iterator it = params.begin() + 1; it < ite; ++it)
		{
			for (size_t i = 0; i < (*it).size(); ++i)
			{
				if ((*it)[i] == '+')
					plusSign = true;
				else if ((*it)[i] == '-')
					plusSign = false;
				else if (validFlags.find((*it)[i]) == std::string::npos)
					usr.sendReply(errorReply);
				else if (plusSign)
					updateUserFlag(&modeToAdd, &modeToRemove, (*it)[i], usr, false);
				else
					updateUserFlag(&modeToRemove, &modeToAdd, (*it)[i], usr, true);
			}
		}
		if (!modeToAdd && !modeToRemove)
			return ("");
		return (rpl_usermode(usr, modeToAdd, modeToRemove));
	}
}
