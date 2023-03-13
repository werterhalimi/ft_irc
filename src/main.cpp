/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:45:34 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/13 16:41:59 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"
#include "Server.h"

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cout << RED << "Invalid number of arguments.";
		std::cout << " Usage: ./ircserv <port> <password>" << RESET_COLOR << std::endl;
		return (EXIT_ERROR);
	}
	std::cout << GREEN << "Starting IRC server on port ";
	std::cout << argv[1] << RESET_COLOR << std::endl;
	Server server;
	server.launch();
	return (EXIT_SUCCESS);
}
