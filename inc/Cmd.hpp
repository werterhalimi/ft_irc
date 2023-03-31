/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:12:52 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/27 17:51:29 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_HPP
# define CMD_HPP

# include "User.hpp"
# include "cmd.h"
# include "reply.h"
# include "error.h"

class Server;

class Cmd
{
	/* Attributes */
	private:
		std::string							_prefix;
		std::string							_cmd;
		std::vector<std::string>& 			_params;

	/* Member functions */
	public:
		/* Constructors & Destructor */
		explicit Cmd(std::string const & msg);
		explicit Cmd(User const & user);
		explicit Cmd(Server const & server);
		~Cmd();

		/* Functions */
		std::string 						toString() const;
		void		 						execute(Server &server, User &currentUser);

		/* Setters */
		void								setCmd(std::string const &cmd);
		void								setParams(std::vector<std::string> const &params);

		/* Specific setters */
		void								addParam(std::string const &param);

		/* Getters */
		std::string const &					getCmd() const;
		std::vector<std::string> const &	getParams() const;

		/* Specific getters */
		std::string const &					getOneParam(size_t i) const;

	private:
		/* Constructors */
		Cmd();
		Cmd(Cmd const &cmd);

		/* Overload operators */
		Cmd &								operator=(Cmd const &cmd);

		/* Functions */
		void								parse(std::string const &msg);
};

#endif
