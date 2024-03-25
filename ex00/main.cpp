/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:56:22 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/25 19:02:50 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

#define DATA "data.csv"

int	main(int argc, char *argv[])
{
	BitcoinExchange	exchange;

	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <input>" << std::endl;	
		return (EXIT_FAILURE);
	}
	if (2 < argc)
	{
		std::cerr << argv[0] << ": too many arguments" << std::endl;
		return (EXIT_FAILURE);
	}
	if (exchange.setData(DATA))
		return (EXIT_FAILURE);
	return (exchange.exchange(argv[1]));
}
