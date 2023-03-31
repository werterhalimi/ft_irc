/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_cannotsendtochan.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 19:18:45 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 19:18:51 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"

std::string	err_cannotsendtochan(User const & user, std::string const & name)
{
	Cmd reply(user);

	reply.setCmd(ERR_CANNOTSENDTOCHAN);
	reply.addParam(user.getNickname());
	reply.addParam(name);
	reply.addParam(":Cannot send to channel");
	return (reply.toString());
}
