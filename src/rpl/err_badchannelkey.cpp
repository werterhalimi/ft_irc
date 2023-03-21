/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_badchannelkey.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:53:16 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 18:53:19 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"

std::string	err_badchannelkey(User const & user, std::string const & name)
{
	Cmd reply(user);

	reply.setCmd(ERR_BADCHANNELKEY);
	reply.addParam(user.getNickname());
	reply.addParam(name);
	reply.addParam(":Cannot join channel (+k)");
	return (reply.toString());
}
