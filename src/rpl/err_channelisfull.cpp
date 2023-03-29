/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_channelisfull.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:50:51 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/29 13:50:54 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"

std::string	err_channelisfull(User const & user, std::string const & name)
{
	Cmd reply(user);

	reply.setCmd(ERR_CHANNELISFULL);
	reply.addParam(user.getNickname());
	reply.addParam(name);
	reply.addParam(":Cannot join channel (+l)");
	return (reply.toString());
}
