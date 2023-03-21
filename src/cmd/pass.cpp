/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:40:15 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/16 16:03:32 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"

std::string	pass(Cmd * cmd, Server & server, User & usr)
{
	if (cmd->getParams().empty())
		return (err_needmoreparams(usr, *cmd));
	else if (usr.hasPass())
		return (err_alreadyregistred(usr));
	else if (cmd->getParams().back() != server.getPass())
		return (err_passwdmismatch(server, usr));
	usr.auth();
	return ("");
}
