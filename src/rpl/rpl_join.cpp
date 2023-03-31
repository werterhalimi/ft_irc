/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_join.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:17:51 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/23 11:17:54 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"
# include "Channel.hpp"

std::string	rpl_join(Channel const & channel, User const & user)
{
	Cmd reply(user);

	reply.setCmd("JOIN");
	reply.addParam(":" + channel.getName());
	return (reply.toString());
}
