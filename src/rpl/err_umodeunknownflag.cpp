/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_umodeunknownflag.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:57:41 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 14:57:42 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"

std::string	err_umodeunknownflag(User const & user)
{
	Cmd reply(user);

	reply.setCmd(ERR_UMODEUNKNOWNFLAG);
	reply.addParam(user.getNickname());
	reply.addParam(":Unknown MODE flag");
	return (reply.toString());
}
