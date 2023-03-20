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
//# include <stdio.h>
# include <cstring>
# include <iostream>
# include <sstream>
# include <sys/socket.h>
# include <unistd.h>

# define PASS_FLAG				0x00000001
# define NICK_FLAG				0x00000002
# define USER_FLAG				0x00000004
# define OPERATOR_FLAG			0x00000008
# define AWAY_FLAG				0x00000010
# define INVISIBLE_FLAG			0x00000020
# define WALLOPS_FLAG			0x00000040
# define RESTRICTED_FLAG		0x00000080
# define GLOBAL_OPERATOR_FLAG	0x00000100
# define LOCAL_OPERATOR_FLAG	0x00000200

# define USER_MODE_FLAG_LETTERS	"aiwroO"

class User
{
	public:
		User();
		User(std::string const &username, std::string const &nickname, std::string const &hostname);
		User(User const & src);
		~User();


		void				sendReply(std::string const & reply) const;

		User &	operator=(User const & src);
		bool	operator==(User const & src);

		void				welcome() ;

		/* Setters */
		void				auth();
		void				setFd(int i);
		void				setUsername(std::string const &user);
		void				setNickname(std::string const &nick);

		/* Getters */
		bool				hasNick() const;
		bool				hasUser() const;
		bool				isLog() const;
		int &				getFd();
		socklen_t &			getSocklen();
		struct sockaddr_in &	getAddress();
		std::string getHostname() const;
		std::string getNickname() const;
		std::string	getUsername() const;
		std::string	prefix() const;
		bool				hasPass() const;
		bool				isAway() const;
		bool				isInvisible() const;
		bool				isWallops() const;
		bool				isRestricted() const;
		bool				isGlobalOperator() const;
		bool				isLocalOperator() const;
		bool				isOperator() const;
		void				setAway(bool flag);
		void				setInvisible(bool flag);
		void				setWallops(bool flag);
		void				setRestricted(bool flag);
		void				setGlobalOperator(bool flag);
		void				setLocalOperator(bool flag);

	private:
		unsigned int 	boolFlags;
//		bool			pass, user, nick, away, invisible, wallops, restricted, globalOperator, localOperator, _isOperator;
		struct sockaddr_in	*addr;
		socklen_t *		len;
		int				fd;
		std::string		username;
		std::string		nickname;
		std::string		hostname;
};
#endif
