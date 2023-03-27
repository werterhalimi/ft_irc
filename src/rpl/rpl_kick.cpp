/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_kick.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:31:50 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/27 11:31:52 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"
# include "Channel.h"

std::string	rpl_kick(Channel const & channel, User const & user, std::string const & name, std::string const & msg)
{
	Cmd reply(user);

	reply.setCmd("KICK");
	reply.addParam(channel.getName());
	reply.addParam(name);
	reply.addParam(msg);
	return (reply.toString());
}
