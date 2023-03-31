/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_inviteonlychan.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:51:06 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/29 13:51:08 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"

std::string	err_inviteonlychan(User const & user, std::string const & name)
{
	Cmd reply(user);

	reply.setCmd(ERR_INVITEONLYCHAN);
	reply.addParam(user.getNickname());
	reply.addParam(name);
	reply.addParam(":Cannot join channel (+i)");
	return (reply.toString());
}
