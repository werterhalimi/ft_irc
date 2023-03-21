/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_umodeis.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:58:10 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 14:58:11 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"

std::string	rpl_umodeis(User const & user)
{
	Cmd reply(user);

	reply.setCmd(RPL_UMODEIS);
	reply.addParam(user.getNickname());
	std::ostringstream stream;
	stream << "+";
	if (user.isAway())
		stream << "a";
	if (user.isInvisible())
		stream << "i";
	if (user.isWallops())
		stream << "w";
	if (user.isRestricted())
		stream << "r";
	if (user.isGlobalOperator())
		stream << "o";
	if (user.isLocalOperator())
		stream << "O";
	reply.addParam(stream.str());
	return (reply.toString());
}
