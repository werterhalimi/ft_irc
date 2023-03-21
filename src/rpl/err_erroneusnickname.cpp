/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_erroneusnickname.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:55:29 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 14:55:31 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"

std::string	err_erroneusnickname(User const & user, std::string const & name)
{
	Cmd reply(user);

	reply.setCmd(ERR_ERRONEUSNICKNAME);
	reply.addParam(user.getNickname());
	reply.addParam(name);
	reply.addParam(":Erroneous nickname");
	return (reply.toString());
}
