/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_nosuchnick.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:57:06 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/27 16:45:12 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"

std::string	err_nosuchnick(User const & user, std::string const & name)
{
	Cmd reply(user);

	reply.setCmd(ERR_NOSUCHNICK);
	reply.addParam(user.getNickname());
	reply.addParam(name);
	reply.addParam(":No such nick/channel");
	return (reply.toString());
}
