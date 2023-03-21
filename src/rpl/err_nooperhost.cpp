/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_nooperhost.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:56:26 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 14:56:27 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"

std::string	err_nooperhost(User const & user)
{
	Cmd reply(user);

	reply.setCmd(ERR_NOOPERHOST);
	reply.addParam(user.getNickname());
	reply.addParam(":No O-lines for your host");
	return (reply.toString());
}
