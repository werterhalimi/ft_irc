/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_join.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:17:51 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/23 11:17:54 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"
# include "Channel.h"

std::string	rpl_join(Channel const & channel, User const & user)
{
	Cmd reply(user);
	// TODO user name ?
	reply.setCmd("JOIN");
	reply.addParam(":" + channel.getName()); // TODO : ?
	return (reply.toString());
}
