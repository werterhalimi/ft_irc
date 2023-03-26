/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:45:21 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/20 20:25:58 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP

# ifndef LOG_LEVEL
#  define LOG_LEVEL 0
# endif

# include "constants.h"
# include <iostream>
# include <string>
# include <algorithm>
# include <vector>
# include <sys/event.h>
# include <sys/socket.h>
# include <netinet/in.h>

//# include <sys/time.h>
//# include <stdio.h>
//# include <stdlib.h>

# include <ctime>
# include <cstdio>
# include <cstdlib>

# include <unistd.h>
# include <sstream>
# include <fstream>
# include <iomanip>

/* Utils */

std::vector<std::string>	split(std::string const & str, std::string const & sep);
std::string					parsing(std::string const & src, std::string const & item);
std::vector<std::string>	readFd(int fd);
bool						isLetter(char const & c);
bool						isDigit(char const & c);
bool						isSpecial(char const & c);
std::string					printTime(struct tm * time);

#endif
