/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_usersdontmatch.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:57:50 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 14:57:51 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"

std::string	err_usersdontmatch(User const & user, size_t size)
{
	Cmd reply(user);

	reply.setCmd(ERR_USERSDONTMATCH);
	reply.addParam(user.getNickname());
	if (size > 1)
		reply.addParam(":Can't change mode for other users");
	else
		reply.addParam(":Can't view mode for other users");
	return (reply.toString());
}
