/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_whoreply.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:22:35 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/27 15:00:43 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"
# include "Server.h"

std::string	rpl_whoreply(Server const & server, User const & user, User const * target)
{
	Cmd	reply(server);
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
	reply.addParam("H");
	reply.addParam(":0");
	reply.addParam(target->getRealname());
	return (reply.toString());
}
