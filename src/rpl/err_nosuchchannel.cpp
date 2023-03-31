/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_nosuchchannel.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:56:57 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 14:56:58 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"

std::string	err_nosuchchannel(User const & user, std::string const & name)
{
	Cmd reply(user);

	reply.setCmd(ERR_NOSUCHCHANNEL);
	reply.addParam(user.getNickname());
	reply.addParam(name);
	reply.addParam(":No such channel");
	return (reply.toString());
}
