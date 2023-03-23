/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_topic.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:21:51 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/23 11:21:52 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"
# include "Channel.h"

std::string	rpl_topic(Server const & server, Channel const & channel, User const & user)
{
	Cmd reply(server);

	reply.setCmd(RPL_TOPIC);
	reply.addParam(user.getNickname());
	reply.addParam(channel.getName());
	reply.addParam(":" + channel.getTopic());
	return (reply.toString());
}
