/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_nicknameinuse.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:55:52 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 14:55:54 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"

std::string	err_nicknameinuse(Server const & server, User const & user, std::string const & name)
{
	Cmd reply(server);

	reply.setCmd(ERR_NICKNAMEINUSE);
	reply.addParam(user.getNickname().empty() ? name : user.getNickname());
	reply.addParam(name);
	reply.addParam(":Nickname is already in use");
	return (reply.toString());
}
