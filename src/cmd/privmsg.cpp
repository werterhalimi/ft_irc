/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:40:35 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/13 13:40:36 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"

void	privmsg(Cmd * cmd, Server & server, User & usr)
{
	if (cmd->getParams(0).empty())
	{
		reply(usr, ERR_NORECIPIENT, std::string(":No recipient given ").append(cmd->getCmd()));
		return;
	}
}

