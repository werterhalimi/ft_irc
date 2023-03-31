/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 23:01:41 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/29 20:47:06 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_CPP
# define BOT_CPP

# include "Server.hpp"

class Bot : public User
{
	/* Attributes */
	private:
		Server *	_server;

	/* Member functions */
	public:
		/* Constructors & Destructor */
		Bot(std::string const & name, Server & server);
		~Bot();

		/* Functions */
		void		sendReply(std::string const & reply) const;
		void		reply(User const * user, std::string const & message) const;

	private:
		/* Constructors */
		Bot();
		Bot(Bot const & src);

		/* Overload operators */
		Bot &		operator=(Bot const & src);
};

#endif
