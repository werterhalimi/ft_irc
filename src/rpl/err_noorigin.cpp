/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_noorigin.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:56:38 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 14:56:39 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"

std::string	err_noorigin(Server const & server, User const & user)
{
	Cmd reply(server);

	reply.setCmd(ERR_NOORIGIN);
	reply.addParam(user.getNickname());
	reply.addParam(":No origin specified");
	return (reply.toString());
}
