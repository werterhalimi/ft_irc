/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_notice.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:21:51 by shalimi           #+#    #+#             */
/*   Updated: 2023/04/10 15:22:31 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "Cmd.hpp"

std::string	rpl_notice(User const & user, std::string target, std::string const &param)
{
	Cmd reply(user);

	reply.setCmd("NOTICE");
	reply.addParam(target);
	reply.addParam(":" + param);
	return (reply.toString());
}

std::string	rpl_notice(User const & user, std::vector<std::string> const &params)
{
	Cmd reply(user);

	reply.setCmd("NOTICE");
	reply.setParams(params);
	return (reply.toString());
}
