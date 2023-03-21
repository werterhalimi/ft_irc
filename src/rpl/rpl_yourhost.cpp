/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_yourhost.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:58:50 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 14:58:51 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"

std::string	rpl_yourhost(Server const & server, User const & user)
{
	Cmd reply(server);

	reply.setCmd(RPL_YOURHOST);
	reply.addParam(user.getNickname());
	reply.addParam(":Your host is test.salut.com, running version 0.0.1"); // TODO host name
	return (reply.toString());
}
