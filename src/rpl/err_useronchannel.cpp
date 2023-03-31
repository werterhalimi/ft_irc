/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_useronchannel.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:37:56 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/27 17:04:19 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"
# include "Channel.hpp"

std::string	err_useronchannel(User const & user, std::string const & channel)
{
	Cmd	cmd(user);
	cmd.setCmd(ERR_USERONCHANNEL);
	cmd.addParam(user.getUsername());
	cmd.addParam(channel);
	cmd.addParam(": is already on channel");
	return (cmd.toString());
}
