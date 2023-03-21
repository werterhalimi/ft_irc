/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_youreoper.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:58:42 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 14:58:43 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"

std::string	rpl_youreoper(User const & user)
{
	Cmd reply(user);

	reply.setCmd(RPL_YOUREOPER);
	reply.addParam(user.getNickname());
	reply.addParam(":You are now an IRC operator");
	return (reply.toString());
}
