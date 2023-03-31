/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_nonicknamegiven.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:56:01 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 14:56:03 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"

std::string	err_nonicknamegiven(Server const & server, User const & user)
{
	Cmd reply(server);

	reply.setCmd(ERR_NONICKNAMEGIVEN);
	reply.addParam(user.getNickname());
	reply.addParam(":No nickname given");
	return (reply.toString());
}
