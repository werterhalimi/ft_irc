/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_notopic.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:13:55 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/27 15:13:56 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"
# include "Channel.h"

std::string	rpl_notopic(Server const & server, Channel const & channel, User const & user)
{
	Cmd reply(server);

	reply.setCmd(RPL_NOTOPIC);
	reply.addParam(user.getNickname());
	reply.addParam(channel.getName());
	reply.addParam(":No topic is set");
	return (reply.toString());
}
