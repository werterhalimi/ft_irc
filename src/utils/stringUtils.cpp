/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:30:50 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/28 23:49:53 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

std::string	nicknameFromPrefix(std::string const & prefix)
{
	std::string ret;
	if (prefix.empty() || prefix[0] != ':') return ret;
	size_t	index = prefix.find("!");
	if (index == std::string::npos) return ret;
	ret = prefix.substr(1, index - 1);
	return ret;
}

bool	isLetter(char const & c)
{
	if (c >= 'A' && c <= 'Z')
		return (true);
	if (c >= 'a' && c <= 'z')
		return (true);
	return (false);
}

bool	isDigit(char const & c)
{
	return (c >= '0' && c <= '9');
}

bool	isSpecial(char const & c)
{
	if (c >= 91 && c <= 96)
		return (true);
	if (c >= 123 && c <= 125)
		return (true);
	return (false);
}
