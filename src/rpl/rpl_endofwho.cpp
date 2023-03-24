/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_endofwho.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:00:52 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/23 18:02:46 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reply.h"
#include "Server.h"

std::string rpl_endofwho(Server const & server, std::string client, std::string mask)
{
	Cmd	reply(server);
	reply.setCmd(RPL_ENDOFWHO);
	reply.addParam(client);
	reply.addParam(mask);
	reply.addParam(":End of WHO list");
	return (reply.toString());
}
