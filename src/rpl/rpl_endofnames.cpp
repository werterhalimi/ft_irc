/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_endofnames.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:25:50 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/23 11:25:52 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"
# include "Channel.hpp"

std::string	rpl_endofnames(Server const & server, Channel const & channel, User const & user)
{
	Cmd reply(server);

	reply.setCmd(RPL_ENDOFNAMES);
	reply.addParam(user.getNickname());
	reply.addParam(channel.getName());
	reply.addParam(":End of Names list");
	return (reply.toString());
}
