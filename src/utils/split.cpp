/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:11:35 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/13 16:41:01 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

static int	count_sep(std::string str, std::string sep)
{
	size_t	i = 0;
	int	n = 0;
	while (1)
	{
		i = str.find(sep, i);
		n++;
		if (i == std::string::npos)
			break ;
		i += sep.size();
	}
	return (n);
}

std::string	*	split(std::string str, std::string sep)
{
	int	n = count_sep(str, sep);
	std::string *ret = new std::string[n];
	int	i = 0;
	size_t	start = 0;
	size_t	index;
	while (i < n)
	{
		index = str.find(sep, start);
		ret[i] = str.substr((start > str.size()) ? str.size() : start, index - start);
		start = index + sep.size();
		i++;
	}
	return ret;
}