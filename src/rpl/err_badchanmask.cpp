/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_badchanmask.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:50:00 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 18:50:02 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"

std::string	err_badchanmask(User const & user, std::string const & name)
{
	Cmd reply(user);

	reply.setCmd(ERR_BADCHANMASK);
	reply.addParam(user.getNickname());
	reply.addParam(name);
	reply.addParam(":Bad Channel Mask");
	return (reply.toString());
}
