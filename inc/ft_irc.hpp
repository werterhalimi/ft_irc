/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:45:21 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/15 19:29:48 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP
# define LOG_LEVEL 0
# include "constants.h"
# include <iostream>
# include <string>
# include <algorithm>
# include <vector>
# include <sys/event.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>


/* Utils */

std::string	*	split(char * str, std::string sep);
bool			isLetter(char const & c);
bool			isDigit(char const & c);
bool			isSpecial(char const & c);
#endif
