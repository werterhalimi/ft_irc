/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:45:21 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/13 16:26:57 by shalimi          ###   ########.fr       */
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

std::string	*	split(std::string str, std::string sep);
#endif
