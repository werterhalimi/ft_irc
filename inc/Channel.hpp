/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
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

# define INVITE_ONLY_FLAG			0x00000001
# define PROTECTED_TOPIC_FLAG		0x00000002
# define CLIENT_LIMIT_FLAG			0x00000004
# define BAN_CHANNEL_FLAG			0x00000008

# define CHANNEL_MODE_FLAG_LETTERS	"itlb"

class Server;

class Channel
{
	/* Attributes */
	private:
		unsigned int 			_boolFlags;
		std::string				_name;
		std::string 			_key;
		std::vector<User *> *	_users;
		std::vector<User *> *	_bannedUsers;
		std::vector<User *> *	_invitedUsers;
		size_t					_slots;
		std::string 			_topic;

	/* Member functions */
	public:
		/* Constructors & Destructor */
		Channel(std::string const & name, int slot);
		explicit Channel(std::string const & config);
		~Channel();

		/* Checkers */
		bool					hasUser(User & user) const;
		bool					isFull() const;
		bool					isBanned(User const & user) const;
		bool					isInvited(User const & user) const;

		/* Setters */
		void					setTopic(std::string const & topic);

		/* Specific setters */
		void					setInviteOnly(bool flag);
		void					setProtectedTopic(bool flag);
		void					setClientLimit(bool flag);
		void					setBanChannel(bool flag);
		void					addUser(Server const & server, User & user);
		void					addInvitedUser(User * user);
		void					removeUser(User & user, std::string const & reply);
		void					removeUser1Channel(User & user, std::string const & reply);

		/* Getters */
		std::string	const &		getName() const;
		std::string const &		getKey() const;
		std::vector<User *> &	getUsers() const;
		std::vector<User *> &	getBannedUsers() const;
		std::vector<User *> &	getInvitedUsers() const;
		size_t					getSlots() const;
		std::string const &		getTopic() const;

		/* Specific getters */
		bool					isInviteOnly() const;
		bool					isProtectedTopic() const;
		bool					isClientLimit() const;
		bool					isBanChannel() const;
		User * 					getUserByName(std::string const & name) const;

	private:
		/* Constructors */
		Channel();
		Channel(Channel const & src);

		/* Overload operators */
		Channel &				operator=(Channel const & src);
};
#endif
