/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:59:05 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/27 17:03:07 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "ft_irc.hpp"
# include "User.h"
# include "Channel.h"
# include <utility>
# include <stdexcept>
//# include <stdio.h>
//# include <string.h>

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
		void						handleLogout(User & user, std::vector<std::string> reason);

		Channel *					getChannelByName(std::string const & name) const;
		User *						getUserByName(std::string const & name) const;
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

		void						serverConfig(const char * path);

	private:
		int							_port;
		std::string					_pass;
		std::string					_servername;
		std::string					_hostname; // TODO use ?
		std::vector<User *> *		_users;
		std::vector<Operator *> *	_operators;
		std::vector<Channel *> *	_channels;
		struct tm *					_time;
		int							_kq_fd;
};

#endif
