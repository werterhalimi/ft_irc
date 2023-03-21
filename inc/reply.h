/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:59:16 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 14:59:18 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_H
# define REPLY_H

# include "constants.h"
# include "Server.h"

class Cmd;

std::string	err_passwdmismatch(Server const & server, User const & user);

std::string	err_unknowncommand(Server const & server, User const & user, Cmd const & cmd);

std::string	rpl_welcome(Server const & server, User const & user);

std::string	rpl_yourhost(Server const & server, User const & user);

std::string	rpl_created(Server const & server, User const & user);

std::string	rpl_myinfo(Server const & server, User const & user);

std::string	err_needmoreparams(User const & user, Cmd const & cmd);

std::string	err_nosuchchannel(User const & user, std::string const & name);

std::string	err_nosuchnick(User const & user, std::string const & name);

std::string	err_usersdontmatch(User const & user, size_t size);

std::string	rpl_umodeis(User const & user);

std::string	err_umodeunknownflag(User const & user);

std::string	err_nonicknamegiven(Server const & server, User const & user);

std::string	err_nicknameinuse(User const & user, std::string const & name);

std::string	err_erroneusnickname(User const & user, std::string const & name);

std::string	rpl_youreoper(User const & user);

std::string	err_nooperhost(User const & user);

std::string	rpl_mode(User & user, int modeToAdd, int modeToRemove);

std::string	err_alreadyregistred(User const & user);

std::string	err_noorigin(Server const & server, User const & user);

#endif
