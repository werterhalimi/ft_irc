/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_bannedfromchan.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:56:30 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 18:56:32 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"

std::string	err_bannedfromchan(User const & user, std::string const & name)
{
	Cmd reply(user);

	reply.setCmd(ERR_BANNEDFROMCHAN);
	reply.addParam(user.getNickname());
	reply.addParam(name);
	reply.addParam(":Cannot join channel (+b)");
	return (reply.toString());
}
