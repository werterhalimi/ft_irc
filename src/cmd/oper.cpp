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
#include "Server.h"

std::string	oper(Cmd * cmd, Server & server, User & usr)
{
	Cmd reply(usr);
	std::vector<std::string> params = cmd->getParams();

	if (params.size() < 2)
		return (err_needmoreparams(usr, *cmd));
	std::vector<Operator *>	operators = server.getOperators();
	std::vector<Operator *>::const_iterator ite = operators.end();
	for (std::vector<Operator *>::const_iterator it = operators.begin(); it < ite; ++it)
	{
		if ((*it)->getName() == params[0] && usr.getUsername() == params[0])
		{
			if (!(*it)->isValidHost(usr.getHostname()))
				break;
			if (!usr.loginOperator(*it, params[1]))
				return (err_passwdmismatch(server, usr));
			usr.sendReply(rpl_youreoper(usr));
			return (rpl_mode(usr, LOCAL_OPERATOR_FLAG, 0));
		}
	}
	return (err_nooperhost(usr));
}
