/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_channelmodeis.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:28:45 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/23 13:28:48 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"
# include "Channel.h"

std::string	rpl_channelmodeis(Channel const & channel, User const & user)
{
	Cmd reply(user);
	reply.setCmd(RPL_CHANNELMODEIS);
	reply.addParam(user.getNickname());
	reply.addParam(channel.getName());
	std::ostringstream stream;
	stream << "+";
//	if (channel.is...)
//		stream << "a";
	reply.addParam(stream.str());
	return (reply.toString());
}
