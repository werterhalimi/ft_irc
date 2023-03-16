/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:07:33 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/15 19:33:57 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef USER_H
# define USER_H
# include "ft_irc.hpp"
# include <vector>
# include <netinet/in.h>
# include <stdio.h>
# include <iostream>
# include <sstream>
# include <sys/socket.h>
# include <unistd.h>

class User
{
	public:
		User(void);
		User(std::string username, std::string nickname, std::string hostname);
		User(User const & src);
		~User(void);


		void				sendReply(std::string reply);

		User &	operator=(User const & src);
		bool	operator==(User const & src);

		void				welcome(void) ;

		/* Setters */
		void				auth(void);
		void				setFd(int i);
		void				setUsername(std::string &user);
		void				setNickname(std::string &nick);

		/* Getters */
		bool				hasNick(void) const;
		bool				hasUser(void) const;
		bool				isLog() const;
		int &				getFd();
		socklen_t &			getSocklen();
		struct sockaddr_in &	getAddress();
		std::string getHostname(void) const;
		std::string getNickname(void) const;
		std::string	getUsername(void) const;
		std::string	prefix() const;
		bool				hasPass(void) const;

	private:
		bool			pass, user, nick;
		struct sockaddr_in	*addr;
		socklen_t *		len;
		int				fd;
		std::string		username;
		std::string		nickname;
		std::string		hostname;
};
#endif
