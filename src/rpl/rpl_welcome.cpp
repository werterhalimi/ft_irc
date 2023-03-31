/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_welcome.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:58:28 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 14:58:31 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"

std::string	rpl_welcome(Server const & server, User const & user)
{
	Cmd reply(server);

	reply.setCmd(RPL_WELCOME);
	reply.addParam(user.getNickname());
	reply.addParam(":Welcome to the BeyondIRC IRC Network " + user.getNickname() + "!" + user.getUsername() + "@" + user.getHostname());
	return (reply.toString());
}

