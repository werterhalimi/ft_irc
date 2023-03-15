/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:40:15 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/13 15:59:02 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"

std::string	pass(Cmd * cmd, Server & server, User & usr)
{
	std::cout << cmd->getOneParam(0) << std::endl;
	(void) cmd;
	(void) server;
	(void) usr;
	return ("");
}
