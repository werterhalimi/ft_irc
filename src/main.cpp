/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:45:34 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/29 00:23:05 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"
#include "Server.h"
#include "Bot.hpp"

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
	int port;
	std::istringstream(argv[1]) >> port;
	Server server(port, std::string(argv[2]));

	Bot bot("MAB", server);
	server.registerCustomUser(bot);

	try
	{
		server.launch();
	}
	catch (std::exception &e)
	{
		std::cerr << RED << "Fatal error" << RESET_COLOR << std::endl;
		return (EXIT_ERROR);
	}
	return (EXIT_SUCCESS);
}
