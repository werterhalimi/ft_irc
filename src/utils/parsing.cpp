/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:10:47 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/26 17:10:49 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_irc.hpp"

std::string	parsing(std::string const & src, std::string const & item)
{
	size_t	start = src.find(item + "=");
	if (start == std::string::npos)
		throw std::exception();
	size_t	length = item.size() + 1;
	size_t	end = src.find(',', start);
	if (end == std::string::npos)
		end = src.find('\n', start);
	start += length;
	end -= start;
	return (src.substr(start, end));
}
