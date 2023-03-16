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
# include "ft_irc.hpp"
# include <vector>
# include "User.h"

class Channel
{
	public:
		Channel(void);
		Channel(std::string name);
		Channel(Channel const & src);
		~Channel(void);

		Channel &			operator=(Channel const & src);
		std::string			getName(void) const;
		std::vector<User> &	getUsers(void) const;
	private:
		std::string			name;
		std::vector<User> *	users;	
};
#endif
