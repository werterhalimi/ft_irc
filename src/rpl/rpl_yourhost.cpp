/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_yourhost.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:58:50 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/27 15:03:25 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"
# include "Server.hpp"

std::string	rpl_yourhost(Server const & server, User const & user)
{
	Cmd reply(server);

	reply.setCmd(RPL_YOURHOST);
	reply.addParam(user.getNickname());
	reply.addParam(":Your host is " + server.getName() + ", running version " + SERVER_VERSION);
	return (reply.toString());
}
