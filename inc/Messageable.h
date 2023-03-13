/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Messageable.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:12:12 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/11 16:17:02 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGEABLE_H
# define MESSAGEABLE_H
# include "ft_irc.hpp"
# include "User.h"

class Messageable
{

	public:
		Messageable(void);
		Messageable(Messageable const & src);
		~Messageable(void);

		Messageable &	operator=(Messageable const & src);

		virtual void	sendMessage(std::string message, User sender, std::string target) = 0;
}
#endif
