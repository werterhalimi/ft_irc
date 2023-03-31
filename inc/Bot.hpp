/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 23:01:41 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/31 16:07:06 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_CPP
# define BOT_CPP

# define NB_BOT_CMD 3
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

		/* Getter */
		Server &	getServer(void) const;

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

void	del(Bot const * bot, User const * usr, std::vector<std::string> const & params);
void	create(Bot const * bot, User const * usr, std::vector<std::string> const & params);
void	stop(Bot const * bot, User const * usr, std::vector<std::string> const & params);
#endif
