/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readFd.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 19:24:38 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/26 19:24:41 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

std::vector<std::string>	readFd(int fd)
{
	char buff[513];
	ssize_t read_return;
	size_t buff_len = 0;

	do
	{
		read_return = read(fd, buff + buff_len, 513);
		if (read_return < 0)
			throw std::exception();
		buff_len += read_return;
		buff[buff_len] = 0;
	}
	while (buff[buff_len - 1] != '\n' || buff[buff_len - 2] != '\r');
	return (split(buff, "\r\n"));
}
