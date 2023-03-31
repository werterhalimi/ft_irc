/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_part.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:58:55 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/23 10:58:57 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"
# include "Channel.hpp"

std::string	rpl_part(Channel const & channel, User const & user, std::string * reason)
{
	Cmd reply(user);

	reply.setCmd("PART");
	reply.addParam(channel.getName());
	if (reason)
		reply.addParam(*reason);
	return (reply.toString());
}
