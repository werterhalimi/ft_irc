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
# include <vector>
# include "User.h"

class Cmd;
class Server;

class Channel
{
	public:
		Channel();
		Channel(std::string const & name, int slot);
		Channel(Channel const & src);
		~Channel();

		void					addUser(Server const & server, User & user);
		void					removeUser(Server const & server, User & user, std::string * reason);
		void					removeUserQuit(Server const & server, User & user, std::vector<std::string> & reason);
		bool					isBanned(User const & user) const;
		bool					hasUser(User & user) const;
		bool					isFull() const;
		bool					isInviteOnly() const;
		Channel &				operator=(Channel const & src);
		std::string	const &		getName() const;
		size_t					getSlots() const;
		std::string const &		getKey() const;
		std::string const &		getTopic() const;
		std::vector<User *> &	getUsers() const;
		std::vector<User *> &	getBannedUsers() const;
	private:
		std::string					_name;
		std::string 				_key;
		std::vector<User *> *		_users;
		std::vector<User *> *		_bannedUsers;
		size_t						_slots;
		std::string 				_topic;
};
#endif
