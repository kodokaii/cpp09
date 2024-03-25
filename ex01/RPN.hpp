/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/25 23:20:52 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stack>
#include <cerrno>
#include <string>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <stdexcept>

#define OP "+-/*"

class RPN
{
	protected:
		std::stack<double>	stack;
		
		size_t	parseValue(std::string const &str, size_t start);
		size_t	parseOp(std::string const &str, size_t start);
		void	doOp(char op);

	public:
				RPN(void);
				RPN(RPN const &other);
				~RPN(void);
		double	compute(std::string const &str);
		RPN	&operator=(RPN const &other);
};
