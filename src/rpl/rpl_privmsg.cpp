/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_privmsg.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 19:25:07 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/29 20:07:13 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"


std::string	rpl_privmsg(User const & user, std::string target, std::string const &param)
{
	Cmd reply(user);

	reply.setCmd("PRIVMSG");
	reply.addParam(target);
	reply.addParam(":" + param);
	return (reply.toString());
}

std::string	rpl_privmsg(User const & user, std::vector<std::string> const &params)
{
	Cmd reply(user);

	reply.setCmd("PRIVMSG");
	reply.addParams(params);
	return (reply.toString());
}
