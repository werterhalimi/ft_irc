/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:11:35 by shalimi           #+#    #+#             */
/*   Updated: 2023/03/20 20:26:44 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

std::vector<std::string> split(std::string const & str, std::string const & sep)
{
	std::vector<std::string> ret;
	std::string tmp;
	size_t	start = 0;
	size_t	index = str.find(sep, start);

	do
	{
		tmp = str.substr((start > str.size()) ? str.size() : start, index - start);
		start = index + sep.size();
		ret.push_back(tmp);
		index = str.find(sep, start);
	} while (index != std::string::npos);
	return (ret);
}
