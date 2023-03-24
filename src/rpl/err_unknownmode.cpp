/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_unknownmode.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:32:03 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/23 18:32:05 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"

std::string	err_unknownmode(User const & user, std::string const & mode)
{
	Cmd reply(user);
	reply.setCmd(ERR_UNKNOWNMODE);
	reply.addParam(user.getNickname());
	reply.addParam(mode);
	reply.addParam(":is unknown mode char to me");
	return (reply.toString());
}
