/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:12:52 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/23 19:34:04 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_HPP
# define CMD_HPP

# include "ft_irc.hpp"
# include "User.h"
//# include "cmd.h"
//# include <cstdio>
# include "reply.h"

# define NB_PARAMS	15
# define NB_CMD		12

class Server;

class Cmd
{
	private:
		std::string					_prefix;
		std::string					_cmd;
		std::vector<std::string>& 	_params;

	public:
//		explicit Cmd(std::string const &msg, Server * server);
		explicit Cmd(std::string const &msg);
		explicit Cmd(User const &user);
		explicit Cmd(Server const &server);

		~Cmd();

		std::string 					toString() const;

		void		 					execute(Server &server, User &currentUser);

		std::string const				&getCmdNames(size_t i) const;

		std::string const				&getCmd() const;

		std::vector<std::string> const	&getParams() const;

		std::string const				&getOneParam(size_t i) const;

		void							setCmd(std::string const &cmd);

		void							addParam(std::string const &param);

		void							addParams(std::vector<std::string> const &params);

	private:
		Cmd();

		Cmd(Cmd const &cmd);

		Cmd		&operator=(Cmd const &cmd);

		void	parse(std::string const &msg);
};

//std::string	reply(User &user, std::string const & cmd, std::string const & msg);

std::string	pass(Cmd *cmd, Server &server, User &currentUser);

std::string	who(Cmd *cmd, Server &server, User &currentUser);

std::string	join(Cmd *cmd, Server &server, User &currentUser);

std::string	part(Cmd *cmd, Server &server, User &currentUser);

std::string	nick(Cmd *cmd, Server &server, User &currentUser);

std::string	user(Cmd *cmd, Server &server, User &currentUser);

std::string	ping(Cmd *cmd, Server &server, User &currentUser);

std::string	pong(Cmd *cmd, Server &server, User &currentUser);

std::string	privmsg(Cmd *cmd, Server &server, User &currentUser);

std::string	mode(Cmd *cmd, Server &server, User &currentUser);

std::string	oper(Cmd *cmd, Server &server, User &currentUser);

std::string	quit(Cmd *cmd, Server &server, User &currentUser);

std::string	kick(Cmd * cmd, Server & server, User & usr);

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

void	motd(Cmd *cmd, Server &server, User &currentUser);

void	names(Cmd *cmd, Server &server, User &currentUser);

void	notice(Cmd *cmd, Server &server, User &currentUser);

void	part(Cmd *cmd, Server &server, User &currentUser);

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

void	usehost(Cmd *cmd, Server &server, User &currentUser);

void	users(Cmd *cmd, Server &server, User &currentUser);

void	version(Cmd *cmd, Server &server, User &currentUser);

void	wallops(Cmd *cmd, Server &server, User &currentUser);

void	who(Cmd *cmd, Server &server, User &currentUser);

void	whois(Cmd *cmd, Server &server, User &currentUser);

void	whowas(Cmd *cmd, Server &server, User &currentUser);
*/
#endif
