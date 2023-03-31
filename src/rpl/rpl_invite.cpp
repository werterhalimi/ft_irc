/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_invite.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:04:54 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/29 14:04:55 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"

std::string	rpl_invite(User const & sender, User const & target, std::string const & chan)
{
	Cmd reply(sender);

	reply.setCmd("INVITE");
	reply.addParam(target.getUsername());
	reply.addParam(target.getNickname());
	reply.addParam(chan);
	return (reply.toString());
}
