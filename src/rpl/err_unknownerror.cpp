/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_unknownerror.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:59:23 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/31 15:59:25 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"

std::string	err_unknownerror(Server const & server, User const & user, Cmd const & cmd)
{
	Cmd reply(server);

	reply.setCmd(ERR_UNKNOWNERROR);
	reply.addParam(user.getNickname());
	reply.addParam(cmd.getCmd());
	reply.addParam(":error");
	return (reply.toString());
}

