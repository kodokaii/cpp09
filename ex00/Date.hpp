/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/25 16:35:33 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stdexcept>

#define MONTH_COUNT 12

typedef unsigned int	t_uint;

class Date
{
	protected:
		t_uint		year;
		t_uint		month;
		t_uint		day;

	public:
				Date(t_uint year = 1970, t_uint month = 1, t_uint day = 1);
				Date(Date const &other);
				~Date(void);
		void	setYear(t_uint year);
		void	setMonth(t_uint month);
		void	setDay(t_uint day);
		t_uint	getYear(void) const;
		t_uint	getMonth(void) const;
		t_uint	getDay(void) const;
		Date	&operator=(Date const &other);
		bool	operator==(Date const &other) const;
		bool	operator!=(Date const &other) const;
		bool	operator<(Date const &other) const;
		bool	operator>(Date const &other) const;
		bool	operator<=(Date const &other) const;
		bool	operator>=(Date const &other) const;

		static t_uint	getDayCount(t_uint year, t_uint month);
};

std::ostream    &operator<<(std::ostream &stream, Date const &date);
