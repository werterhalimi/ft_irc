/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_alreadyregistred.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:51:55 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/23 17:48:08 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"

std::string	err_alreadyregistred(Server const & server, User const & user)
{
	Cmd reply(server);

	reply.setCmd(ERR_ALREADYREGISTRED);
	reply.addParam(user.getNickname());
	reply.addParam(":Unauthorized command (already registered");
	return (reply.toString());
}

std::string	err_alreadyregistred(User const & user)
{
	Cmd reply(user);

	reply.setCmd(ERR_ALREADYREGISTRED);
	reply.addParam(user.getNickname());
	reply.addParam(":Unauthorized command (already registered");
	return (reply.toString());
}
