/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:42:33 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/15 19:33:27 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"

std::string	user(Cmd * cmd, Server & server, User & usr)
{
	std::vector<std::string>	params = cmd->getParams();
	std::string			user = params.at(0);
	if (params.empty())
		return (err_nonicknamegiven(server, usr));
	else if (usr.hasUser())
		return (err_alreadyregistred(usr));
	usr.setUsername(user);
	usr.setHostname();
	if (usr.isLog())
		usr.welcome(server);
	return ("");
}
