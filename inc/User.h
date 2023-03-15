/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:07:33 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/11 20:43:27 by shalimi          ###   ########.fr       */
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


		void				log(char *buff);

		User &	operator=(User const & src);
		bool	operator==(User const & src);

		std::string	prefix() const;

		std::string	getUsername(void) const;
		std::string getNickname(void) const;
		std::string getHostname(void) const;
		struct sockaddr_in &	getAddress();
		socklen_t &			getSocklen();
		int &				getFd();
		bool				isLog();
		void				setFd(int i);


	private:
		bool			logged;
		struct sockaddr_in	*addr;
		socklen_t *		len;
		int				fd;
		std::string		username;
		std::string		nickname;
		std::string		hostname;
};
#endif
