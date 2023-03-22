/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_created.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:57:57 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 14:57:58 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"
# include "Server.h"

std::string	rpl_created(Server const & server, User const & user)
{
	Cmd reply(server);

	reply.setCmd(RPL_CREATED);
	reply.addParam(user.getNickname());
	reply.addParam(":This server was created " + printTime(server.getTime()));
	return (reply.toString());
}
