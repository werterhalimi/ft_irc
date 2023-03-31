/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_notexttosend.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:57:15 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 14:57:16 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"

std::string	err_notexttosend(User const & user)
{
	Cmd reply(user);

	reply.setCmd(ERR_NOTEXTTOSEND);
	reply.addParam(user.getNickname());
	reply.addParam(":No text to send");
	return (reply.toString());
}
