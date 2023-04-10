/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:45:21 by ncotte            #+#    #+#             */
/*   Updated: 2023/04/10 15:05:22 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP

# ifndef LOG_LEVEL
#  define LOG_LEVEL 0
# endif

# include "constants.h"
# include <iostream>
# include <cstring>
# include <algorithm>
# include <vector>
# include <sys/event.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <ctime>
# include <cstdio>
# include <cstdlib>
# include <unistd.h>
# include <sstream>
# include <fstream>
# include <iomanip>
# include <utility>
# include <stdexcept>

//# include <sys/time.h>
//# include <stdio.h>
//# include <stdlib.h>

/* Utils */

int							stoi(std::string const & str);
std::string					itos(int i);
std::vector<std::string>	split(std::string const & str, std::string const & sep);
std::vector<std::string>	split(std::string const & str, char const * sep);
std::string					parsing(std::string const & src, std::string const & item, bool mandatory);
int							parsingFlags(std::string const & src);
bool						isLetter(char const & c);
bool						isDigit(char const & c);
bool						isSpecial(char const & c);
bool						isEmpty(std::string const & str);
std::string					printCurrentTime();
std::string					printFullTime(struct tm * time);

/* Templates */

template <typename T>
void	deleteVector(std::vector<T> * vector)
{
	typename std::vector<T>::iterator it = vector->begin();
	while (it != vector->end())
	{
		delete (*it);
		it++;
	}
	delete vector;
}

template <typename T>
void	removeFromVector(typename std::vector<T> & vec, T el)
{
	typename std::vector<T>::iterator	pos = std::find(vec.begin(), vec.end(), el);
	if (pos == vec.end())
		return ;
	vec.erase(pos);
}

#endif
