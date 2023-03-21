/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:59:05 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/21 17:49:47 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include "ft_irc.hpp"
# include <vector>
# include "User.h"
# include "Channel.h"
# include "Operator.hpp"
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
		Server();
		explicit Server(std::string const & name); // TODO Used ?
		Server(int port, std::string const & pass);
		Server(Server const & src);
		~Server();

		Server &					operator=(Server const & src);

		void						launch();
		void						handleLogin(User & user, struct kevent * event);
		void						handleLogout(User & user);

		Channel *					getChannelByName(std::string const & name);
		bool						hasNick(std::string const & nick) const;
		std::string					prefix() const;
		int							getPort() const;
		std::string					getPass() const;
		std::string					getName() const;
		std::string					getHostname() const;
		std::vector<User *> &		getUsers() const;
		std::vector<Operator *> &	getOperators() const;
		std::vector<Channel *> &	getChannels() const;
		int 						getChannelID(std::string const & name) const;
		int 						getUserID(std::string const & nickname) const;
		struct tm *					getTime() const;

	private:
		int							_port;
		std::string					_pass;
		std::string					_servername;
		std::string					_hostname;
		std::vector<User *> *		_users;
		std::vector<Operator *> *	_operators;
		std::vector<Channel *> *	_channels;
		struct tm *					_time;
};

#endif
