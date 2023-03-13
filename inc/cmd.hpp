/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:12:52 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/12 14:12:53 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_HPP
# define CMD_HPP

# include "constants.h"
# include "cmd.h"
# include <iostream>
//# include <cstdio>

# define NB_PARAMS	15
# define NB_CMD		45

// TODO
class User;

class Server;

class Cmd
{
	private:
		std::string			_cmd;
		std::string			_params[NB_PARAMS];

	public:
		Cmd(std::string const &msg, Server &server, User &user);

		~Cmd();

		std::string			reply(User &user);

		std::string const	&getCmdNames(size_t i) const;

		std::string const	&getCmd() const;

		std::string const	&getParams(size_t i) const;

	private:
		Cmd();

		Cmd(Cmd const &cmd);

		Cmd		&operator=(Cmd const &cmd);

		void	parse(std::string const &msg);

		void	execute(Server &server, User &currentUser);
};

#endif
