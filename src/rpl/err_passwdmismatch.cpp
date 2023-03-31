/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_passwdmismatch.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:57:24 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 14:57:25 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"

std::string	err_passwdmismatch(Server const & server, User const & user)
{
	Cmd reply(server);

	reply.setCmd(ERR_PASSWDMISMATCH);
	reply.addParam(user.getNickname());
	reply.addParam(":Password incorrect");
	return (reply.toString());
}
