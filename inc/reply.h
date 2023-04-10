/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:59:16 by ncotte            #+#    #+#             */
/*   Updated: 2023/04/10 15:24:11 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_H
# define REPLY_H

# include "ft_irc.hpp"

class Server;
class Channel;
class User;
class Cmd;

std::string	rpl_channelmode(Channel & channel, User & user, int modeToAdd, int modeToRemove);

std::string	rpl_channelmodeis(Channel const & channel, User const & user);

std::string	rpl_created(Server const & server, User const & user);

std::string rpl_endofwho(Server const & server, std::string const & client, std::string const & mask);

std::string	rpl_error(User const & user, Cmd const & cmd);
std::string	rpl_error(User const & user, std::string const & reason);

std::string	rpl_invite(User const & sender, User const & target, std::string const & chan);

std::string	rpl_inviting(User const & sender, User const & target, std::string const & chan);

std::string	rpl_join(Channel const & channel, User const & user);

std::string	rpl_kick(Channel const & channel, User const & user, std::string const & name, std::string const & msg);

std::string	rpl_kill(User const & userOp, User const & userKill, std::string const & reasons);

std::string	rpl_myinfo(Server const & server, User const & user);

std::string	rpl_part(Channel const & channel, User const & user, std::string * reason);

std::string	rpl_privmsg(User const & user, std::vector<std::string> const & params);

std::string	rpl_notice(User const & user, std::vector<std::string> const & params);

std::string	rpl_privmsg(User const & user, std::string target,  std::string const & param);

std::string	rpl_notice(User const & user, std::string target,  std::string const & param);

std::string	rpl_quit(User const & user, std::string const & reasons);

std::string	rpl_notopic(Server const & server, Channel const & channel, User const & user);

std::string	rpl_endofnames(Server const & server, Channel const & channel, User const & user);

std::string	rpl_namreply(Server const & server, Channel const & channel, User const & user);

std::string	rpl_topic(Server const & server, Channel const & channel, User const & user);

std::string	rpl_umodeis(User const & user);

std::string	rpl_usermode(User & user, int modeToAdd, int modeToRemove);

std::string	rpl_welcome(Server const & server, User const & user);

std::string	rpl_whoreply(Server const & server, User const & user, User const * target);

std::string	rpl_youreoper(User const & user);

std::string	rpl_yourhost(Server const & server, User const & user);

#endif
