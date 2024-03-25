/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/25 23:44:07 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

size_t	skipSpace(std::string const &str, size_t start)
{
	size_t	len;

	len = 0;
	while (isspace(str[start + len]))
		len++;
	return (len);
}

RPN::RPN(void)
{
}

RPN::RPN(RPN const &other): stack(other.stack)
{
}

RPN::~RPN(void)
{
}

size_t	RPN::parseValue(std::string const &str, size_t start)
{
	char const	*cstr;
	char		*end;
	double		value;

	cstr = str.c_str() + start;
	value = std::strtod(cstr, &end);
	if (errno == ERANGE)
	{
		if (value < 0)
			throw (std::underflow_error("underflow value"));
		else
			throw (std::overflow_error("overflow value"));
	}
	if (end == cstr)
		throw (std::runtime_error("syntax error"));
	this->stack.push(value);
	return (end - cstr);
}

size_t	RPN::parseOp(std::string const &str, size_t start)
{
	size_t	len;

	len = skipSpace(str, start);
	if (!std::strchr(OP, str[start + len]))
		throw (std::runtime_error("syntax error"));
	this->doOp(str[start + len++]);
	return (len);
}

#include <iostream>
void	RPN::doOp(char op)
{
	double	a;
	double	b;

	if (this->stack.size() < 2)
		throw (std::logic_error("syntax error"));
	b = this->stack.top();
	this->stack.pop();
	a = this->stack.top();
	this->stack.pop();

	switch (op)
	{
		case '+':
			this->stack.push(a + b);
			break;
		case '-':
			this->stack.push(a - b);
			break;
		case '*':
			this->stack.push(a * b);
			break;
		case '/':
			this->stack.push(a / b);
			break;
		default:
			throw (std::invalid_argument(std::string("invalid operation ") + op));
	}
}

double	RPN::compute(std::string const &str)
{
	size_t	len;
	double	res;
	
	len = 0;
	while (len < str.size())
	{
		try
		{
			len += this->parseValue(str, len);
		}
		catch (std::runtime_error &e)
		{
			len += this->parseOp(str, len);
		}
		len += skipSpace(str, len);
	}
	if (1 < this->stack.size())
		throw (std::logic_error("syntax error"));
	if (this->stack.size() < 1)
		return (0);
	res = this->stack.top();
	this->stack.pop();
	return (res);
}

RPN		&RPN::operator=(RPN const &other)
{
	this->stack = other.stack;
	return (*this);
}
