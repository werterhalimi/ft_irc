/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printTime.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:50:11 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/21 11:50:13 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

std::string		printCurrentTime()
{
	time_t	time_now = time(NULL);
	struct tm * time = gmtime(&time_now);
	std::ostringstream stream;

	stream << std::setfill('0');
	stream << std::setw(2) << time->tm_hour << ":";
	stream << std::setw(2) << time->tm_min << ":";
	stream << std::setw(2) << time->tm_sec << " "; // GMT
	return (stream.str());
}

std::string		printFullTime(struct tm * time)
{
	static std::string months[12] =
	{
		"Jan", "Feb", "Mar", "Apr",
		"May", "Jun", "Jul", "Aug",
		"Sep", "Oct", "Nov", "Dec"
	};
	std::ostringstream stream;

	stream << std::setfill('0');
	stream << std::setw(2) << time->tm_hour << ":";
	stream << std::setw(2) << time->tm_min << ":";
	stream << std::setw(2) << time->tm_sec << " "; // GMT
	stream << months[time->tm_mon] << " ";
	stream << std::setw(2) << time->tm_mday << " ";
	stream << time->tm_year + 1900;
	return (stream.str());
}
