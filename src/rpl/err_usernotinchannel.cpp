/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_usernotinchannel.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:46:45 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/27 10:46:47 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"
# include "Channel.hpp"

std::string	err_usernotinchannel(Channel const & channel, User const & user, std::string const & name)
{
	Cmd reply(user);

	reply.setCmd(ERR_USERNOTINCHANNEL);
	reply.addParam(user.getNickname());
	reply.addParam(name);
	reply.addParam(channel.getName());
	reply.addParam(":They aren't on that channel");
	return (reply.toString());
}
