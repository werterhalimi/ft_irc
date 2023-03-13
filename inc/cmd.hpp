/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:12:52 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/13 15:51:48 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_HPP
# define CMD_HPP

# include "constants.h"
# include "User.h"
# include "Server.h"
//# include "cmd.h"
# include <iostream>
//# include <cstdio>

# define NB_PARAMS	15
# define NB_CMD		3


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


void	pass(Cmd *cmd, Server &server, User &currentUser);

void	nick(Cmd *cmd, Server &server, User &currentUser);

void	user(Cmd *cmd, Server &server, User &currentUser);

/*
void	admin(Cmd *cmd, Server &server, User &currentUser);

void	away(Cmd *cmd, Server &server, User &currentUser);

void	connect(Cmd *cmd, Server &server, User &currentUser);

void	die(Cmd *cmd, Server &server, User &currentUser);

void	error(Cmd *cmd, Server &server, User &currentUser);

void	info(Cmd *cmd, Server &server, User &currentUser);

void	invite(Cmd *cmd, Server &server, User &currentUser);

void	ison(Cmd *cmd, Server &server, User &currentUser);

void	join(Cmd *cmd, Server &server, User &currentUser);

void	kick(Cmd *cmd, Server &server, User &currentUser);

void	kill(Cmd *cmd, Server &server, User &currentUser);

void	links(Cmd *cmd, Server &server, User &currentUser);

void	list(Cmd *cmd, Server &server, User &currentUser);

void	luser(Cmd *cmd, Server &server, User &currentUser);

void	mode(Cmd *cmd, Server &server, User &currentUser);

void	motd(Cmd *cmd, Server &server, User &currentUser);

void	names(Cmd *cmd, Server &server, User &currentUser);

void	nick(Cmd *cmd, Server &server, User &currentUser);

void	notice(Cmd *cmd, Server &server, User &currentUser);

void	oper(Cmd *cmd, Server &server, User &currentUser);

void	part(Cmd *cmd, Server &server, User &currentUser);

void	pass(Cmd *cmd, Server &server, User &currentUser);

void	ping(Cmd *cmd, Server &server, User &currentUser);

void	pong(Cmd *cmd, Server &server, User &currentUser);

void	privmsg(Cmd *cmd, Server &server, User &currentUser);

void	quit(Cmd *cmd, Server &server, User &currentUser);

void	rehash(Cmd *cmd, Server &server, User &currentUser);

void	restart(Cmd *cmd, Server &server, User &currentUser);

void	service(Cmd *cmd, Server &server, User &currentUser);

void	servlist(Cmd *cmd, Server &server, User &currentUser);

void	squery(Cmd *cmd, Server &server, User &currentUser);

void	squit(Cmd *cmd, Server &server, User &currentUser);

void	stats(Cmd *cmd, Server &server, User &currentUser);

void	summon(Cmd *cmd, Server &server, User &currentUser);

void	time(Cmd *cmd, Server &server, User &currentUser);

void	topic(Cmd *cmd, Server &server, User &currentUser);

void	trace(Cmd *cmd, Server &server, User &currentUser);

void	user(Cmd *cmd, Server &server, User &currentUser);

void	usehost(Cmd *cmd, Server &server, User &currentUser);

void	users(Cmd *cmd, Server &server, User &currentUser);

void	version(Cmd *cmd, Server &server, User &currentUser);

void	wallops(Cmd *cmd, Server &server, User &currentUser);

void	who(Cmd *cmd, Server &server, User &currentUser);

void	whois(Cmd *cmd, Server &server, User &currentUser);

void	whowas(Cmd *cmd, Server &server, User &currentUser);
*/
#endif
