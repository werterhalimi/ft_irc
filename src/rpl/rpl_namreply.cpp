/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_namreply.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:33:29 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/27 18:19:21 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"
# include "Channel.hpp"

std::string	rpl_namreply(Server const & server, Channel const & channel, User const & user)
{
	Cmd reply(server);

	reply.setCmd(RPL_NAMREPLY);
	reply.addParam(user.getNickname());
	reply.addParam("=");
	reply.addParam(channel.getName());

	std::vector<User *> users = channel.getUsers();
	if(!users.empty())
	{
		reply.addParam(":");
		std::vector<User *>::iterator ite = users.end();
		for(std::vector<User *>::iterator it = users.begin(); it != ite; it++)
		{
			if ((*it)->isOperator())
				reply.addParam("@" + (*it)->getNickname());
			else
				reply.addParam((*it)->getNickname());
		}
	}
	return (reply.toString());
}
