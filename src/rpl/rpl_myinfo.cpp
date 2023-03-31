/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_myinfo.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:58:03 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/27 15:15:47 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"
# include "Server.hpp"

std::string	rpl_myinfo(Server const & server, User const & user)
{
	Cmd reply(server);

	reply.setCmd(RPL_MYINFO);
	reply.addParam(user.getNickname());
	reply.addParam(":" + server.getName() + " 2.0 ras"); // TODO host name
	return (reply.toString());
}
