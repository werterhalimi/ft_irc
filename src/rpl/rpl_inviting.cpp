/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_inviting.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:49:55 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/27 17:05:27 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"
# include "Channel.h"

std::string	rpl_inviting(User const & sender, User const & target, std::string chan)
{
	Cmd reply(sender);
	reply.setCmd(RPL_INVITING);
	reply.addParam(target.getUsername());
	reply.addParam(target.getNickname());
	reply.addParam(chan);
	return (reply.toString());
}
