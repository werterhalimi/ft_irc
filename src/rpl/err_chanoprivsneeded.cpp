/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_chanoprivsneeded.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:12:39 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/23 14:12:40 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"
# include "Channel.h"

std::string	err_chanoprivsneeded(Channel const & channel, User const & user)
{
	Cmd reply(user);
	reply.setCmd(ERR_CHANOPRIVSNEEDED);
	reply.addParam(user.getNickname());
	reply.addParam(channel.getName());
	reply.addParam(":You're not channel operator");
	return (reply.toString());
}
