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

# include "ft_irc.hpp"

class Operator
{
	/* Attributes */
	private:
		std::string			_name;
		std::string			_host;
		std::string			_password;

	/* Member functions */
	public:
		/* Constructors & Destructor */
		Operator(std::string const & name, std::string const & host, std::string const & password);
		explicit Operator(std::string const & config);
		~Operator();

		/* Checkers */
		bool				isValidHost(std::string const & host) const;
		bool				isValidPassword(std::string const & password) const;

		/* Getters */
		std::string const &	getName() const;

	private:
		/* Constructors */
		Operator();
		Operator(Operator const & src);

		/* Overload operators */
		Operator &			operator=(Operator const & src);
};

#endif
