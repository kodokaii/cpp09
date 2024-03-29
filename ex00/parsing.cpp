/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:14:35 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/29 15:05:17 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"

size_t	skipSpace(std::string const &str, size_t start)
{
	size_t	len;

	len = 0;
	while (isspace(str[start + len]))
		len++;
	return (len);
}

size_t	parseUint(t_uint &output, std::string const &str, size_t start)
{
	char const	*cstr;
	char		*end;
	long		l;

	cstr = str.c_str() + start;
	l = std::strtol(cstr, &end, 10);
	if (l < 0)
		throw (std::underflow_error("not a positive number"));
	if (UINT_MAX < l)
		throw (std::overflow_error("too large a number"));
	if (end == cstr)
		throw (std::runtime_error("missing value"));
	output = l;
	return (end - cstr);
}

size_t	parseValue(float &output, std::string const &str, size_t start)
{
	char const	*cstr;
	char		*end;
	double		d;

	cstr = str.c_str() + start;
	d = std::strtod(cstr, &end);
	if (d < 0)
		throw (std::underflow_error("not a positive number"));
	if (1000 < d)
		throw (std::overflow_error("too large a number"));
	if (end == cstr)
		throw (std::runtime_error("missing value"));
	output = d;
	return (end - cstr);
}

size_t	parseDate(Date &output, std::string const &str, size_t start)
{
	size_t	len;
	t_uint	nb;

	try
	{
		len = skipSpace(str, start);
		len += parseUint(nb, str, start);
		output.setYear(nb);
		if (str[start + len++] != '-')
			throw (std::runtime_error("missing '-'"));
		len += parseUint(nb, str, start + len);
		output.setMonth(nb);
		if (str[start + len++] != '-')
			throw (std::runtime_error("missing '-'"));
		len += parseUint(nb, str, start + len);
		output.setDay(nb);
	}
	catch (std::exception &e)
	{
		throw (std::runtime_error(std::string("invalid date: ") + e.what()));
	}
	return (len);
}

size_t	parseDataLine(std::map<Date, float> &output, std::string const &str, size_t start)
{
	size_t	len;
	Date	date;
	float	value;

	len = parseDate(date, str, start);
	len += skipSpace(str, start + len);
	if (str[start + len++] != ',')
		throw (std::runtime_error("missing ','"));
	len += parseValue(value, str, start + len);
	len += skipSpace(str, start + len);
	if (str[start + len] != '\0')
		throw (std::runtime_error(std::string("parse error near '") + str[start + len] + '\''));
	output[date] = value;
	return (len);
}

size_t	parseInputLine(std::pair<Date, float> &output, std::string const &str, size_t start)
{
	size_t	len;

	len = parseDate(output.first, str, start);
	len += skipSpace(str, start + len);
	if (str[start + len++] != '|')
		throw (std::runtime_error("missing '|'"));
	len += parseValue(output.second, str, start + len);
	len += skipSpace(str, start + len);
	if (str[start + len] != '\0')
		throw (std::runtime_error(std::string("parse error near '") + str[start + len] + '\''));
	return (len);
}
