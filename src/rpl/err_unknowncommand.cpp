/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_unknowncommand.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:57:34 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 14:57:35 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"

std::string	err_unknowncommand(Server const & server, User const & user, Cmd const & cmd)
{
	Cmd reply(server);

	reply.setCmd(ERR_UNKNOWNCOMMAND);
	reply.addParam(user.getNickname());
	reply.addParam(cmd.getCmd());
	reply.addParam(":Unknown command");
	return (reply.toString());
}
