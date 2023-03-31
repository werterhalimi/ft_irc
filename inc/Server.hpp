/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:59:05 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/31 19:12:14 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "Channel.hpp"

class Server
{
	/* Attributes */
	private:
		int							_port;
		std::string					_pass;
		std::string					_servername;
		std::vector<User *> *		_users;
		std::vector<Operator *> *	_operators;
		std::vector<Channel *> *	_channels;
		struct tm *					_time;
		int							_kq_fd;
		volatile bool				_running;

	/* Member functions */
	public:
		/* Constructors & Destructor */
		Server(int port, std::string const & pass);
		~Server();

		/* Functions */
		void						launch();
		void						handleLogout(Cmd const & cmd, User & user, std::string const & reason);

		/* Checkers */
		bool						hasNick(std::string const & nick) const;

		/* Specific setters */
		void						registerCustomUser(User & user);
		void						createChannel(std::string const & name, int slots);
		void						removeChannel(Channel const * channel);
		void						stop();

		/* Getters */
		int							getPort() const;
		std::string					getPass() const;
		std::string					getName() const;
		std::vector<User *> &		getUsers() const;
		std::vector<Operator *> &	getOperators() const;
		std::vector<Channel *> &	getChannels() const;
		struct tm *					getTime() const;

		/* Specific getters */
		Channel *					getChannelByName(std::string const & name) const;
		User *						getUserByName(std::string const & name) const;
		std::string					getPrefix() const;

	private:
		/* Constructors */
		Server();
		Server(Server const & src);

		/* Overload operators */
		Server &					operator=(Server const & src);

		/* Functions */
		void						handleLogin(User & user, struct kevent * event);
		void						userLogout(User & user);
		void						serverConfig(const char * path);
};

#endif
