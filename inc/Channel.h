/*	
 *	o ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:03:53 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/11 17:13:39 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_H
# define CHANNEL_H
# include "Cmd.hpp"
# include "ft_irc.hpp"
# include "User.h"

# define INVITE_ONLY_FLAG			0x00000001
# define PROTECTED_TOPIC_FLAG		0x00000002
# define CLIENT_LIMIT_FLAG			0x00000004
# define BAN_CHANNEL_FLAG			0x00000008

# define CHANNEL_MODE_FLAG_LETTERS	"itlb" // TODO ban

class Cmd;
class Server;

class Channel
{
	public:
		Channel();
		Channel(std::string const & name, int slot);
		explicit Channel(std::string const & config);
		Channel(Channel const & src);
		~Channel();

		void					addUser(Server const & server, User & user);
		void					addInvitedUser(User * user);
		void					removeUser(User & user, std::string const & reply);
		void					removeUser1Channel(User & user, std::string const & reply);
		bool					isBanned(User const & user) const;
		bool					isInvited(User const & user) const;
		bool					hasUser(User & user) const;
		bool					isFull() const;
		bool					isInviteOnly() const;
		bool					isProtectedTopic() const;
		bool					isClientLimit() const;
		bool					isBanChannel() const;
		void					setInviteOnly(bool flag);
		void					setProtectedTopic(bool flag);
		void					setClientLimit(bool flag);
		void					setBanChannel(bool flag);
		Channel &				operator=(Channel const & src);
		std::string	const &		getName() const;
		size_t					getSlots() const;
		std::string const &		getKey() const;
		std::string const &		getTopic() const;
		std::vector<User *> &	getUsers() const;
		User * 					getUserByName(std::string const & name) const;
		std::vector<User *> &	getBannedUsers() const;
		std::vector<User *> &	getInvitedUsers() const;
		void					setTopic(std::string const & topic);

	private:
		unsigned int 			_boolFlags;
		std::string				_name;
		std::string 			_key;
		std::vector<User *> *	_users;
		std::vector<User *> *	_bannedUsers;
		std::vector<User *> *	_invitedUsers;
		size_t					_slots;
		std::string 			_topic;
};
#endif
