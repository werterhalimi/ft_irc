/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:11:35 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/30 16:10:49 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

std::vector<std::string> split(std::string const & str, char const	* sep)
{
	return split(str, std::string(sep));
}

std::vector<std::string> split(std::string const & str, std::string const & sep)
{
	std::vector<std::string> ret;
	std::string tmp;
	size_t	start = 0;
	size_t	index = str.find(sep, start);

	while (start != str.size())
	{
		tmp = str.substr((start > str.size()) ? str.size() : start, index - start);
		start = index + sep.size();
		ret.push_back(tmp);
		if (index == std::string::npos) break;
		index = str.find(sep, start);
	}
	//if (start < str.size() - 1)
	//	ret.push_back(str.substr(start, str.size()));
	return (ret);
}
