/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:59:05 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/20 19:06:13 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include "ft_irc.hpp"
# include <vector>
# include "User.h"
# include "Channel.h"
# include <string>
# include <iomanip>
# include <utility>
# include <iostream>
# include <stdexcept>
# include <netinet/in.h>
//# include <stdio.h>
//# include <string.h>
# include <sys/socket.h>
# include <unistd.h>
class Server
{
	public:
		Server(void);
		Server(std::string name);
		Server(int port, std::string pass);
		Server(Server const & src);
		~Server(void);

		Server &					operator=(Server const & src);

		void						launch(void);
		void						handleLogin(User & user, struct kevent * event);
		void						handleLogout(User & user);

		bool						hasNick(std::string nick) const;
		Channel *					getChannelByName(std::string const & name);
		std::string					prefix() const;
		int							getPort(void) const;
		std::string					getPass(void) const;
		std::string					getName(void) const;
		std::string					getHostname(void) const;
		std::vector<User *> &		getUsers(void) const;
		std::vector<Channel *> &	getChannels(void) const;
		int 						getChannelID(std::string const & name) const;
		int 						getUserID(std::string const & nickname) const;

	private:
		int					port;
		std::string			pass;
		std::string			servername;
		std::string			hostname;
		std::vector<User *> *		users;
		std::vector<Channel *> *	channels;
};

#endif
