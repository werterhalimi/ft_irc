/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:39:44 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/15 19:36:41 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "Server.hpp"

static bool	validNickName(std::string nick)
{
	size_t		i = 1;
	if (nick.size() > 9) return (false);
	if (isLetter(nick[0]) || isSpecial(nick[0]))
	{
		while (i < nick.size())
		{
			if (!isLetter(nick[i]) && !isSpecial(nick[i]) && !isDigit(nick[i]) && nick[i] != '-')
				return (false);
			i++;
		}
	}
	return (true);
}

std::string	nick(Cmd * cmd, Server & server, User & usr)
{
	std::vector<std::string>	params = cmd->getParams();

	if (!usr.hasPass())
		return (err_passwdmismatch(server, usr));
	if (params.empty())
		return (err_nonicknamegiven(server, usr));
	std::string	nick = params.at(0);
	if (server.hasNick(nick))
		return (err_nicknameinuse(server, usr, nick));
	if (!validNickName(nick))
		return (err_erroneusnickname(server, usr, nick));
	usr.setNickname(nick);
	if (usr.isLog())
		usr.welcome(server);
	return ("");

}
