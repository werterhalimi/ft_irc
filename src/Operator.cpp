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

/* Public */

/* Constructors & Destructor */

Operator::Operator(std::string const & name, std::string const & host, std::string const & password) :
	_name(name),
	_host(host),
	_password(password)
{
	#if LOG_LEVEL == 10
		std::cout << BOLD_BLUE << "Operator name, host & password constructor @ " << BOLD_MAGENTA << this << RESET_COLOR << std::endl;
	#endif
}

Operator::Operator(std::string const & config)
{
	#if LOG_LEVEL == 10
		std::cout << BOLD_BLUE << "Operator config constructor @ " << BOLD_MAGENTA << this << RESET_COLOR << std::endl;
	#endif
	try
	{
		this->_name = parsing(config, "name", true);
		this->_host = parsing(config, "host", true);
		this->_password = parsing(config, "password", true);
	}
	catch (std::exception &e)
	{
		throw std::exception();
	}
}

Operator::~Operator()
{
	#if LOG_LEVEL == 10
		std::cout << BOLD_BLUE << "Operator default destructor @ " << BOLD_MAGENTA << this << RESET_COLOR << std::endl;
	#endif
}

/* Checkers */

bool	Operator::isValidHost(std::string const & host) const
{
	return (host == this->_host);
}

bool	Operator::isValidPassword(std::string const & password) const
{
	return (password == this->_password);
}

/* Getters */

std::string const &	Operator::getName() const
{
	return (this->_name);
}

/* Private */

/* Constructors */

Operator::Operator()
{
	#if LOG_LEVEL == 10
		std::cout << BOLD_BLUE << "Operator name, host & password constructor @ " << BOLD_MAGENTA << this << RESET_COLOR << std::endl;
	#endif
}

Operator::Operator(Operator const & src)
{
	#if LOG_LEVEL == 10
		std::cout << BOLD_BLUE << "Operator name, host & password constructor @ " << BOLD_MAGENTA << this << RESET_COLOR << std::endl;
	#endif
	*this = src;
}

/* Overload operators */

Operator &	Operator::operator=(Operator const & src)
{
	if (this != &src)
	{
		this->_name = src._name;
		this->_host = src._host;
		this->_password = src._password;
	}
	return *this;
}
