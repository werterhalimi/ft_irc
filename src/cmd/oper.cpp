/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:39:55 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/13 13:39:57 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"

std::string	oper(Cmd * cmd, Server & server, User & usr)
{
	Cmd reply(usr);
	std::vector<std::string> params = cmd->getParams();

	if (params.size() < 2)
	{
		reply.setCmd(ERR_NEEDMOREPARAMS);
		reply.addParam(usr.getNickname());
		reply.addParam(cmd->getCmd());
		reply.addParam(":Not enough parameters");
		return (reply.toString());
	}
	std::vector<Operator *>	operators = server.getOperators();
	std::vector<Operator *>::const_iterator ite = operators.end();
	for (std::vector<Operator *>::const_iterator it = operators.begin(); it < ite; ++it)
	{
		if ((*it)->getName() == params[0] && usr.getUsername() == params[0])
		{
			if (!(*it)->isValidHost(usr.getHostname()))
				break;
			if (!usr.loginOperator(*it, params[1]))
			{
				reply.setCmd(ERR_PASSWDMISMATCH);
				reply.addParam(usr.getNickname());
				reply.addParam(":Password incorrect");
				return (reply.toString());
			}
			Cmd replyOK(usr);
			replyOK.setCmd(RPL_YOUREOPER);
			replyOK.addParam(usr.getNickname());
			replyOK.addParam(":You are now an IRC operator");
			usr.sendReply(replyOK.toString());
			usr.setGlobalOperator(true);
			reply.setCmd("MODE");
			reply.addParam(usr.getNickname());
			reply.addParam(":+o");
			return (reply.toString());
		}
	}
	reply.setCmd(ERR_NOOPERHOST);
	reply.addParam(usr.getNickname());
	reply.addParam(":No O-lines for your host");
	return (reply.toString());
}
