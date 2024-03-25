/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/25 16:58:18 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Date.hpp"

Date::Date(t_uint year, t_uint month, t_uint day):	year(year),
													month(month),
													day(day)
{
	if (month <= 0 || MONTH_COUNT < month)
		throw (std::out_of_range("month out of range"));	
	if (day <= 0 || Date::getDayCount(year, month) < day)
		throw (std::out_of_range("day out of range"));	
}

Date::Date(Date const &other):	year(other.year),
								month(other.month),
								day(other.day)
{
}

Date::~Date(void)
{
}

void	Date::setYear(t_uint year)
{
	if (this->day <= 0 || Date::getDayCount(year, this->month) < this->day)
		throw (std::out_of_range("day out of range"));	
	this->year = year;
}

void	Date::setMonth(t_uint month)
{
	if (month <= 0 || MONTH_COUNT < month)
		throw (std::out_of_range("month out of range"));	
	if (this->day <= 0 || Date::getDayCount(this->year, month) < this->day)
		throw (std::out_of_range("day out of range"));	
	this->month = month;
}

void	Date::setDay(t_uint day)
{
	if (day <= 0 || Date::getDayCount(this->year, this->month) < day)
		throw (std::out_of_range("day out of range"));	
	this->day = day;
}

t_uint	Date::getYear(void) const
{
	return (this->year);
}

t_uint	Date::getMonth(void) const
{
	return (this->month);
}

t_uint	Date::getDay(void) const
{
	return (this->day);
}

Date	&Date::operator=(Date const &other)
{
	this->year = other.year;
	this->month = other.month;
	this->day = other.day;
	return (*this);
}

bool	Date::operator==(Date const &other) const
{
	return (this->year == other.year
			&& this->month == other.month
			&& this->day == other.day);
}

bool	Date::operator!=(Date const &other) const
{
	return (this->year != other.year
			|| this->month != other.month
			|| this->day != other.day);
}

bool	Date::operator<(Date const &other) const
{
	if (this->year != other.year)
		return (this->year < other.year);
	if (this->month != other.month)
		return (this->month < other.month);
	return (this->day < other.day);
}

bool	Date::operator>(Date const &other) const
{
	if (this->year != other.year)
		return (this->year > other.year);
	if (this->month != other.month)
		return (this->month > other.month);
	return (this->day > other.day);
}

bool	Date::operator<=(Date const &other) const
{
	if (this->year != other.year)
		return (this->year < other.year);
	if (this->month != other.month)
		return (this->month < other.month);
	return (this->day <= other.day);
}

bool	Date::operator>=(Date const &other) const
{
	if (this->year != other.year)
		return (this->year > other.year);
	if (this->month != other.month)
		return (this->month > other.month);
	return (this->day >= other.day);
}

t_uint	Date::getDayCount(t_uint year, t_uint month)
{
	switch (month)
	{
		case 1:
			return (31);
		case 2:
			if ((!(year % 4) && year % 100) || !(year % 400))
				return (29);
			else
				return (28);
		case 3:
			return (31);
		case 4:
			return (30);
		case 5:
			return (31);
		case 6:
			return (30);
		case 7:
			return (31);
		case 8:
			return (31);
		case 9:
			return (30);
		case 10:
			return (31);
		case 11:
			return (30);
		case 12:
			return (31);
		default:
			return (0);
	}
}

std::ostream    &operator<<(std::ostream &stream, Date const &date)
{
	stream << date.getYear() << '-' << date.getMonth() << '-' << date.getDay();
	return (stream);
}
