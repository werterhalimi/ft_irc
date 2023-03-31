/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_kill.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:54:22 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/29 18:54:23 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"

std::string	rpl_kill(User const & userOp, User const & userKill, std::string const & reasons)
{
	Cmd reply(userOp);

	reply.setCmd("KILL");
	reply.addParam(userKill.getNickname());
	reply.addParam(reasons);
	return (reply.toString());
}
