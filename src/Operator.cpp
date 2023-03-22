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

Operator::Operator(std::string const & name, std::string const & host, std::string const & password) : _name(name), _host(host), _password(password)
{
}

Operator::~Operator()
{
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