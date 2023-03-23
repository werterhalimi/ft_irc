/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_error.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:46:51 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/23 10:46:55 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"

std::string	rpl_error(User const & user, Cmd const & cmd)
{
	Cmd reply(user);

	reply.setCmd("ERROR");
//	reply.addParam(user.getNickname()); TODO ?
	reply.addParams(cmd.getParams());
	return (reply.toString());
}
