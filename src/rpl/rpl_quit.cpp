/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_quit.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:09:02 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/23 11:09:04 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "reply.h"
# include "Cmd.hpp"

std::string	rpl_quit(User const & user, std::vector<std::string> const & reasons)
{
	Cmd reply(user);

	reply.setCmd("QUIT");
	reply.addParam(":Quit:"); // TODO :Quit ?
	reply.addParams(reasons);
	return (reply.toString());
}
