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

std::string	mode(Cmd * cmd, Server & server, User & usr)
{
	Cmd reply(usr);
	std::vector<std::string> params = cmd->getParams();

	if (params.empty())
	{
		reply.setCmd(ERR_NEEDMOREPARAMS);
		reply.addParam(cmd->getCmd());
		reply.addParam(":Not enough parameters");
		return (reply.toString());
	}
	if (params[0][0] == '#')
	{
		int id = server.getChannelID(params[0]);
		if (id < 0)
		{
			reply.setCmd(ERR_NOSUCHCHANNEL);
			reply.addParam(params[0]);
			reply.addParam(":No such channel");
			return (reply.toString());
		}
		else
		{
			// TODO
		}
	}
	else
	{
		int id = server.getUserID(params[0]);
		if (id < 0)
		{
			reply.setCmd(ERR_NOSUCHNICK);
			reply.addParam(params[0]);
			reply.addParam(":No such nick");
			return (reply.toString());
		}
		else if (server.getUsers()[id]->getNickname() != usr.getNickname())
		{
			reply.setCmd(ERR_USERSDONTMATCH);
			if (params.size() > 1)
				reply.addParam(":Can't change mode for other users");
			else
				reply.addParam(":Can't view mode for other users");
			return (reply.toString());
		}
		else if (params.size() == 1)
		{
			reply.setCmd(RPL_UMODEIS);
			reply.addParam(usr.getNickname());
			std::ostringstream stream;
			stream << "+";
			if (usr.isAway())
				stream << "a";
			if (usr.isInvisible())
				stream << "i";
			if (usr.isWallops())
				stream << "w";
			if (usr.isRestricted())
				stream << "r";
			if (usr.isGlobalOperator())
				stream << "o";
			if (usr.isLocalOperator())
				stream << "O";
			reply.addParam(stream.str());
			return (reply.toString());
		}
		bool plusSign = true;
		int modeToAdd = 0;
		int modeToRemove = 0;
		Cmd errorReply(usr);
		errorReply.setCmd(ERR_UMODEUNKNOWNFLAG);
		errorReply.addParam(usr.getNickname());
		errorReply.addParam(":Unknown MODE flag");
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
					usr.sendReply(errorReply.toString());
				else if (plusSign)
					updateUserFlag(&modeToAdd, &modeToRemove, (*it)[i], usr, false);
				else
					updateUserFlag(&modeToRemove, &modeToAdd, (*it)[i], usr, true);
			}
		}
		if (!modeToAdd && !modeToRemove)
			return ("");
		reply.setCmd("MODE");
		reply.addParam(usr.getNickname());
		std::ostringstream stream;
		stream << ":";
		stream << updateUserMode(modeToAdd, usr, true);
		stream << updateUserMode(modeToRemove, usr, false);
		reply.addParam(stream.str());
	}
	return (reply.toString());
}
