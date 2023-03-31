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
#include "Server.hpp"

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
	(void) channel;
	(void) removeMode;
	switch (c)
	{
		case 'i':
			*flagToAdd |= INVITE_ONLY_FLAG;
			*flagToRemove &= ~INVITE_ONLY_FLAG;
			break;
		case 't':
			*flagToAdd |= PROTECTED_TOPIC_FLAG;
			*flagToRemove &= ~PROTECTED_TOPIC_FLAG;
			break;
		case 'l':
			*flagToAdd |= CLIENT_LIMIT_FLAG;
			*flagToRemove &= ~CLIENT_LIMIT_FLAG;
			break;
		case 'b':
			*flagToAdd |= BAN_CHANNEL_FLAG;
			*flagToRemove &= ~BAN_CHANNEL_FLAG;
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
		Channel * channel = server.getChannelByName(params[0]);
		if (!channel)
			return (err_nosuchchannel(usr, params[0]));
		if (params.size() == 1)
			return (rpl_channelmodeis(*channel, usr));
		if (!usr.isGlobalOperator() && !usr.isLocalOperator()) // TODO which one ?
			return (err_chanoprivsneeded(*channel, usr));
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
					updateChannelFlag(&modeToAdd, &modeToRemove, (*it)[i], *channel, false);
				else
					updateChannelFlag(&modeToRemove, &modeToAdd, (*it)[i], *channel, true);
			}
		}
		if (!modeToAdd && !modeToRemove)
			return ("");
		std::string reply = rpl_channelmode(*channel, usr, modeToAdd, modeToRemove);
		std::vector<User *>::const_iterator itue = channel->getUsers().end();
		for (std::vector<User *>::const_iterator itu = channel->getUsers().begin(); itu < itue; ++itu)
			if (!(**itu == usr))
				(*itu)->sendReply(reply);
		usr.sendReply(reply);
		return ("");
	}
	else
	{
		User * target = server.getUserByName(params[0]);
		if (!target)
			return (err_nosuchnick(usr, params[0]));
		else if (!(*target == usr))
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
