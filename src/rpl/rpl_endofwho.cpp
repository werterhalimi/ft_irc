/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_endofwho.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:00:52 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/27 15:16:07 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"

std::string rpl_endofwho(Server const & server, std::string const & client, std::string const & mask)
{
	Cmd	reply(server);
	reply.setCmd(RPL_ENDOFWHO);
	reply.addParam(client);
	reply.addParam(mask);
	reply.addParam(":End of WHO list.");
	return (reply.toString());
}
