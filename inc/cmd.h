/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:58:47 by ncotte            #+#    #+#             */
/*   Updated: 2023/04/10 15:23:39 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "ft_irc.hpp"

class Cmd;
class Server;
class User;

std::string	cap(Cmd * cmd, Server & server, User & currentUser);

std::string	notice(Cmd * cmd, Server & server, User & currentUser);

std::string	invite(Cmd * cmd, Server & server, User & currentUser);

std::string	join(Cmd * cmd, Server & server, User &currentUser);

std::string	kick(Cmd *  cmd, Server & server, User & currentUser);

std::string	kill(Cmd *  cmd, Server & server, User & currentUser);

std::string	mode(Cmd * cmd, Server & server, User & currentUser);

std::string	nick(Cmd * cmd, Server & server, User & currentUser);

std::string	oper(Cmd * cmd, Server & server, User & currentUser);

std::string	part(Cmd * cmd, Server & server, User & currentUser);

std::string	pass(Cmd * cmd, Server & server, User & currentUser);

std::string	ping(Cmd * cmd, Server & server, User & currentUser);

std::string	pong(Cmd * cmd, Server & server, User & currentUser);

std::string	privmsg(Cmd * cmd, Server & server, User & currentUser);

std::string	quit(Cmd * cmd, Server & server, User & currentUser);

std::string	topic(Cmd *  cmd, Server & server, User & currentUser);

std::string	user(Cmd * cmd, Server & server, User & currentUser);

std::string	who(Cmd * cmd, Server & server, User & currentUser);

#endif
