/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:16:55 by ncotte            #+#    #+#             */
/*   Updated: 2023/03/20 17:16:58 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATOR_HPP
# define OPERATOR_HPP

# include <iostream>

class Operator
{
	private:
		std::string	_name;
		std::string	_host;
		std::string	_password;

	public:
		Operator(std::string const & name, std::string const & host, std::string const & password);
		~Operator();

		bool	isValidHost(std::string const & host) const;
		bool	isValidPassword(std::string const & password) const;

		std::string const &	getName() const;

	private:
		Operator();

		Operator(Operator const &op);

		Operator	&operator=(Operator const &op);
};

#endif
