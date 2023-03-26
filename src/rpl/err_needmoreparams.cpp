/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_needmoreparams.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:55:40 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 14:55:41 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"

std::string	err_needmoreparams(Server const & server, User const & user, Cmd const & cmd)
{
	Cmd reply(server);

	reply.setCmd(ERR_NEEDMOREPARAMS);
	reply.addParam(user.getNickname());
	reply.addParam(cmd.getCmd());
	reply.addParam(":Not enough parameters");
	return (reply.toString());
}

std::string	err_needmoreparams(User const & user, Cmd const & cmd)
{
	Cmd reply(user);

	reply.setCmd(ERR_NEEDMOREPARAMS);
	reply.addParam(user.getNickname());
	reply.addParam(cmd.getCmd());
	reply.addParam(":Not enough parameters");
	return (reply.toString());
}
