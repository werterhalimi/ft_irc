/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_notonchannel.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 19:03:12 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 19:03:14 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"

std::string	err_notonchannel(User const & user, std::string const & name)
{
	Cmd reply(user);

	reply.setCmd(ERR_NOTONCHANNEL);
	reply.addParam(user.getNickname());
	reply.addParam(name);
	reply.addParam(":You're not on that channel");
	return (reply.toString());
}
