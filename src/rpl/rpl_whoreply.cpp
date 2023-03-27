/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_whoreply.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:22:35 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/27 18:01:03 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"
# include "Server.h"

std::string	rpl_whoreply(Server const & server, User const & user, User const * target)
{
	Cmd	reply(server);
	std::string	flags = "H";
	reply.setCmd(RPL_WHOREPLY);
	reply.addParam(user.getUsername());
	if (target->getChannels()->empty())
		reply.addParam("*");
	else
		reply.addParam(target->getChannels()->at(0)->getName());
	reply.addParam('~' + target->getUsername());
	reply.addParam(target->getHostname());
	reply.addParam(server.getName());
	reply.addParam(target->getNickname());
	if (target->isOperator())
		flags.append("*");
	reply.addParam(flags);

	reply.addParam(":0");
	reply.addParam(target->getRealname());
	return (reply.toString());
}
