/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:45:34 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/16 16:07:00 by shalimi          ###   ########.fr       */
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
	Server server(std::atoi(argv[1]), std::string(argv[2]));
	server.launch();
	return (EXIT_SUCCESS);
}
