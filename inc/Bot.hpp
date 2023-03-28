/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 23:01:41 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/29 00:26:00 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_CPP
# define BOT_CPP
# include "User.h"
# include "Server.h"

class Server;

class Bot : public User
{
	public:
		Bot(void);
		Bot(std::string name, Server & server);
		~Bot(void);
		Bot(Bot const & src);

		Bot &	operator=(Bot const & src);	
		void				sendReply(std::string const & reply) const;
	private:
		Server	*	_server;
};
#endif
