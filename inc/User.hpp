/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:07:33 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/30 17:22:39 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_H
# define USER_H

# include "Operator.hpp"

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
	/* Attributes */
	private:
		unsigned int 				_boolFlags;
		struct sockaddr_in			_addr;
		socklen_t 					_len;
		int							_fd;
		std::string					_username;
		std::string					_nickname;
		std::string					_hostname;
		std::string					_realname;
		struct kevent *				_event;
		std::vector<Channel *> *	_channels;
		char						_buffer[513];
		int							_bufferLength;

	/* Member functions */
	public:
		/* Constructors & Destructor */
		User();
		User(std::string const &username, std::string const &nickname, std::string const &hostname);
		virtual ~User();

		/* Overload operators */
		bool						operator==(User const & src) const;

		/* Functions */
		virtual void				sendReply(std::string const & reply) const;
		void						welcome(Server const & server) const;
		void						handleCmd(Server & server);

		/* Checkers */
		bool						isLog() const;
		bool						loginOperator(Operator const * op, std::string const &password);

		/* Setters */
		void						setKEvent(struct kevent * event);
		void						setFd(int i);
		void						setUsername(std::string const &user);
		void						setNickname(std::string const &nick);
		void						setRealname(std::string const &user);
		void						setHostname();

		/* Specific setters */
		void						auth();
		void						setAway(bool flag);
		void						setInvisible(bool flag);
		void						setWallops(bool flag);
		void						setRestricted(bool flag);
		void						setGlobalOperator(bool flag);
		void						setLocalOperator(bool flag);
		void						addChannel(Channel * chan);
		void						removeChannel(Channel * chan);

		/* Getters */
		struct kevent *				getKEvent() const;
		int 						getFd() const;
		socklen_t *					getSocklenPtr();
		struct sockaddr_in *		getAddressPtr();
		std::vector<Channel *> *	getChannels() const;
		std::string 				getRealname() const;
		std::string					getUsername() const;
		std::string 				getNickname() const;
		std::string 				getHostname() const;
		std::string					prefix() const;

		/* Specific getters */
		bool						hasPass() const;
		bool						hasNick() const;
		bool						hasUser() const;
		bool						isAway() const;
		bool						isInvisible() const;
		bool						isWallops() const;
		bool						isRestricted() const;
		bool						isGlobalOperator() const;
		bool						isLocalOperator() const;
		bool						isOperator() const;

	protected:
		/* Constructors */
		User(User const & src);

		/* Overload operators */
		User &						operator=(User const & src);

		/* Specific setters */
		void						initBuffer();
};
#endif
