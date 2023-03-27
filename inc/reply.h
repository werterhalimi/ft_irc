/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:59:16 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/23 18:05:34 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_H
# define REPLY_H

# include "ft_irc.hpp"
class Server;
class Channel;
class User;
class Cmd;


std::string rpl_endofwho(Server const & server, std::string client, std::string mask);
std::string	rpl_whoreply(Server const & server, User const & user, User const * target);
std::string	err_passwdmismatch(Server const & server, User const & user);

std::string	err_unknowncommand(Server const & server, User const & user, Cmd const & cmd);

std::string	rpl_welcome(Server const & server, User const & user);

std::string	rpl_yourhost(Server const & server, User const & user);

std::string	rpl_created(Server const & server, User const & user);

std::string	rpl_myinfo(Server const & server, User const & user);

std::string	err_needmoreparams(User const & user, Cmd const & cmd);

std::string	err_needmoreparams(Server const & server, User const & user, Cmd const & cmd);

std::string	err_nosuchchannel(User const & user, std::string const & name);

std::string	err_nosuchnick(User const & user, std::string const & name);

std::string	err_usersdontmatch(User const & user, size_t size);

std::string	rpl_umodeis(User const & user);

std::string	err_umodeunknownflag(User const & user);

std::string	err_nonicknamegiven(Server const & server, User const & user);

std::string	err_nicknameinuse(User const & user, std::string const & name);

std::string	err_nicknameinuse(Server const & server, User const & user, std::string const & name);

std::string	err_erroneusnickname(User const & user, std::string const & name);

std::string	err_erroneusnickname(Server const & server, User const & user, std::string const & name);

std::string	rpl_youreoper(User const & user);

std::string	err_nooperhost(User const & user);

std::string	rpl_usermode(User & user, int modeToAdd, int modeToRemove);

std::string	err_alreadyregistred(User const & user);

std::string	err_alreadyregistred(Server const & server, User const & user);

std::string	err_noorigin(Server const & server, User const & user);

std::string	err_badchanmask(User const & user, std::string const & name);

std::string	err_badchannelkey(User const & user, std::string const & name);

std::string	err_bannedfromchan(User const & user, std::string const & name, std::string const & mode);

std::string	err_notonchannel(User const & user, std::string const & name);

std::string	err_norecipient(User const & user, Cmd const & cmd);

std::string	err_notexttosend(User const & user);

std::string	err_cannotsendtochan(User const & user, std::string const & name);

std::string	rpl_privmsg(User const & user, std::vector<std::string> const & params);

std::string	rpl_error(User const & user, Cmd const & cmd);

std::string	rpl_part(Channel const & channel, User const & user, std::string * reason);

std::string	rpl_quit(User const & user, std::vector<std::string> const & reasons);

std::string	rpl_join(Channel const & channel, User const & user);

std::string	rpl_topic(Server const & server, Channel const & channel, User const & user);

std::string	rpl_notopic(Server const & server, Channel const & channel, User const & user);

std::string	rpl_endofnames(Server const & server, Channel const & channel, User const & user);

std::string	rpl_namreply(Server const & server, Channel const & channel, User const & user);

std::string	rpl_channelmodeis(Channel const & channel, User const & user);

std::string	err_chanoprivsneeded(Channel const & channel, User const & user);

std::string	err_unknownmode(User const & user, std::string const & mode);

std::string	rpl_channelmode(Server const & server, Channel & channel, int modeToAdd, int modeToRemove);

std::string	err_usernotinchannel(Channel const & channel, User const & user, std::string const & name);

std::string	rpl_kick(Channel const & channel, User const & user, std::string const & name, std::string const & msg);

#endif
