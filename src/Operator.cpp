/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operator.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:17:36 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/20 17:17:38 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operator.hpp"

Operator::Operator(std::string const & name, std::string const & host, std::string const & password) :
	_name(name),
	_host(host),
	_password(password)
{
	#if LOG_LEVEL
		std::cout << "Operator name, host & password constructor @ " << this << std::endl;
	#endif
}

Operator::Operator(std::string const & config)
{
	#if LOG_LEVEL
		std::cout << "Operator config constructor @ " << this << std::endl;
	#endif
	try
	{
		this->_name = parsing(config, "name");
		this->_host = parsing(config, "host");
		this->_password = parsing(config, "password");
	}
	catch (std::exception &e)
	{
		throw std::exception();
	}
}

Operator::~Operator()
{
	#if LOG_LEVEL
		std::cout << "Operator default destructor @ " << this << std::endl;
	#endif
}

bool	Operator::isValidHost(std::string const & host) const
{
	return (host == this->_host);
}

bool	Operator::isValidPassword(std::string const & password) const
{
	return (password == this->_password);
}

std::string const &	Operator::getName() const
{
	return (this->_name);
}
