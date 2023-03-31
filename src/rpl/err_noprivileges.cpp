/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_noprivileges.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:44:02 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/29 15:44:04 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"

std::string	err_noprivileges(User const & user)
{
	Cmd reply(user);

	reply.setCmd(ERR_NOPRIVILEGES);
	reply.addParam(user.getNickname());
	reply.addParam(":Permission Denied- You're not an IRC operator");
	return (reply.toString());
}
