/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_namreply.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:33:29 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/23 11:33:31 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"
# include "Channel.h"

std::string	rpl_namreply(Server const & server, Channel const & channel, User const & user)
{
	Cmd reply(server);

	reply.setCmd(RPL_NAMREPLY);
	reply.addParam(user.getNickname());
	reply.addParam("="); //TODO all mode
	reply.addParam(channel.getName());

	std::vector<User *> users = channel.getUsers();
	if(!users.empty())
	{
		reply.addParam(":" + users.at(0)->getNickname());
		std::vector<User *>::iterator ite = users.end();
		for(std::vector<User *>::iterator it = users.begin() + 1; it != ite; it++)
			reply.addParam((*it)->getNickname());
	}
	// TODO break into multiples rpl
//	reply.addParam(":End of Names list");
	return (reply.toString());
}
