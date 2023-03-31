/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:47:12 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/31 11:47:14 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "ft_irc.hpp"

class Server;
class Channel;
class User;
class Cmd;

std::string	err_alreadyregistred(Server const & server, User const & user);

std::string	err_badchanmask(User const & user, std::string const & name);

std::string	err_badchannelkey(User const & user, std::string const & name);

std::string	err_bannedfromchan(User const & user, std::string const & name);

std::string	err_cannotsendtochan(User const & user, std::string const & name);

std::string	err_channelisfull(User const & user, std::string const & name);

std::string	err_chanoprivsneeded(Channel const & channel, User const & user);

std::string	err_erroneusnickname(Server const & server, User const & user, std::string const & name);

std::string	err_inviteonlychan(User const & user, std::string const & name);

std::string	err_needmoreparams(User const & user, Cmd const & cmd);
std::string	err_needmoreparams(Server const & server, User const & user, Cmd const & cmd);

std::string	err_nicknameinuse(Server const & server, User const & user, std::string const & name);

std::string	err_nonicknamegiven(Server const & server, User const & user);

std::string	err_nooperhost(User const & user);

std::string	err_noorigin(Server const & server, User const & user);

std::string	err_noprivileges(User const & user);

std::string	err_norecipient(User const & user, Cmd const & cmd);

std::string	err_nosuchchannel(User const & user, std::string const & name);

std::string	err_nosuchnick(User const & user, std::string const & name);

std::string	err_notexttosend(User const & user);

std::string	err_notonchannel(User const & user, std::string const & name);

std::string	err_passwdmismatch(Server const & server, User const & user);

std::string	err_umodeunknownflag(User const & user);

std::string	err_unknowncommand(Server const & server, User const & user, Cmd const & cmd);

std::string	err_unknownerror(Server const & server, User const & user, Cmd const & cmd);

std::string	err_unknownmode(User const & user, std::string const & mode);

std::string	err_usernotinchannel(Channel const & channel, User const & user, std::string const & name);

std::string	err_useronchannel(User const & user, std::string const & name);

std::string	err_usersdontmatch(User const & user, size_t size);

#endif
