/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 23:26:30 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/25 23:34:22 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int	main(int argc, char *argv[])
{
	RPN	rpn;
	
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <expression>" << std::endl;
		return (EXIT_FAILURE);
	}
	if (2 < argc)
	{
		std::cerr << argv[0] << ": too many arguments" << std::endl;
		return (EXIT_FAILURE);
	}
	try
	{
		std::cout << rpn.compute(argv[1]) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << argv[0] << ": " << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
