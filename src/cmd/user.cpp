/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:42:33 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/23 17:01:44 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"

std::string	user(Cmd * cmd, Server & server, User & usr)
{
	std::vector<std::string>	params = cmd->getParams();

	if (params.size() < 4)
//		return (err_nonicknamegiven(server, usr));
		return (err_needmoreparams(server, usr, *cmd));
	else if (usr.hasUser())
		return (err_alreadyregistred(server, usr));
//	std::string	user = params.at(0);
	usr.setUsername(params.at(0));
	usr.setRealname(params.at(3));
	usr.setHostname();
	if (usr.isLog())
		usr.welcome(server);
	return ("");
}
