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
		Channel(void);
		Channel(std::string name, int slot);
		Channel(Channel const & src);
		~Channel(void);

		void				addUser(Server const & server, User & user);
		bool				isBanned(User const & user) const;
		bool				isFull(void) const;
		bool				isInviteOnly(void) const;
		Channel &			operator=(Channel const & src);
		std::string			getName(void) const;
		size_t					getSlots(void) const;
		std::string  		getKey(void) const;
		std::string  		getTopic(void) const;
		std::vector<User *> &	getUsers(void) const;
		std::vector<User *> &	getBannedUsers(void) const;
	private:
		std::string					name;
		std::string 				key;
		std::vector<User *> *		users;
		std::vector<User *> *		bannedUsers;
		size_t							slots;
		std::string 				topic;
};
#endif
