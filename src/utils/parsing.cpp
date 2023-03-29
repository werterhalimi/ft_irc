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
# include "Channel.h"

int	parsingFlags(std::string const & src)
{
	int	boolFlags = 0;

	if (src.find("slots=") != std::string::npos)
		boolFlags |= CLIENT_LIMIT_FLAG;
	if (src.find("protectedTopic=YES") != std::string::npos)
		boolFlags |= PROTECTED_TOPIC_FLAG;
	if (src.find("inviteOnly=YES") != std::string::npos)
		boolFlags |= INVITE_ONLY_FLAG;
	return (boolFlags);
}

std::string	parsing(std::string const & src, std::string const & item, bool mandatory)
{
	size_t	start = src.find(item + "=");
	if (start == std::string::npos && mandatory)
		throw std::exception();
	else if (start == std::string::npos)
		return ("");
	size_t	length = item.size() + 1;
	size_t	end = src.find(',', start);
	if (end == std::string::npos)
		end = src.find('\n', start);
	start += length;
	end -= start;
	return (src.substr(start, end));
}
