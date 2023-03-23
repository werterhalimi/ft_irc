/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:07:33 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/23 17:03:09 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef USER_H
# define USER_H
# include "ft_irc.hpp"
# include "Operator.hpp"
# include <vector>
# include <netinet/in.h>
//# include <stdio.h>
# include <cstring>
# include <iostream>
# include <sstream>
# include <sys/socket.h>
# include <arpa/inet.h>
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

class Server;
class Channel;

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

		void				welcome(Server const & server) const;

		/* Setters */
		void				addChannel(Channel * chan);
		void				removeChannel(Channel * chan);
		void				setKEvent(struct kevent * event);
		void				auth();
		void				setFd(int i);
		void				setUsername(std::string const &user);
		void				setRealname(std::string const &user);
		void				setNickname(std::string const &nick);
		void				setHostname();
		void				setAway(bool flag);
		void				setInvisible(bool flag);
		void				setWallops(bool flag);
		void				setRestricted(bool flag);
		void				setGlobalOperator(bool flag);
		void				setLocalOperator(bool flag);
		bool				loginOperator(Operator const * op, std::string const &password);

		/* Getters */
		struct kevent *		getKEvent() const;
		bool				hasNick() const;
		bool				hasUser() const;
		bool				isLog() const;
		int &				getFd();
		socklen_t *			getSocklenPtr();
		struct sockaddr_in *	getAddressPtr();
		std::vector<Channel *>*	getChannels() const;
		std::string getHostname() const;
		std::string getRealname() const;
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

	private:
		unsigned int 			_boolFlags;
		struct sockaddr_in		_addr;
		socklen_t 				_len;
		int						_fd;
		std::string				_username;
		std::string				_nickname;
		std::string				_hostname;
		std::string				_realname;
		struct kevent *			_event;
		std::vector<Channel *>*	_channels;
};
#endif
