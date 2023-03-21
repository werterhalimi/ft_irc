/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_norecipient.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:56:47 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 14:56:48 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"

std::string	err_norecipient(User const & user, Cmd const & cmd)
{
	Cmd reply(user);

	reply.setCmd(ERR_NORECIPIENT);
	reply.addParam(user.getNickname());
	reply.addParam(":No recipient given");
	reply.addParam(cmd.getCmd());
	return (reply.toString());
}
