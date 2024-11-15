/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:04:23 by nlaerema          #+#    #+#             */
/*   Updated: 2024/11/12 09:35:29 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <deque>
#include <climits>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include "PmergeMe.hpp"

#define CLOCK_TO_US(clock) double(clock) / double(CLOCKS_PER_SEC) * 1e+6

int	fillContainer(int argc, char *argv[], std::list<uint> &list, std::deque<uint> &deque)
{
	int		i;
	char	*end;
	long	value;

	for (i = 1; i < argc; i++)
	{
		value = std::strtol(argv[i], &end, 10);
		if (end == argv[i] || *end || value < 0 || UINT_MAX < value)
			return (EXIT_FAILURE);
		list.push_back(value);
		deque.push_back(value);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	std::list<uint>		list;	
	std::deque<uint>	deque;
	clock_t				listClock;
	clock_t				dequeClock;
	int					i;

	if (fillContainer(argc, argv, list, deque))
	{
		std::cerr << "Error" << std::endl;
		return (EXIT_FAILURE);
	}
	std::cout << "Before:";
	for (i = 1; i < argc; i++)
		std::cout << " " << deque[i - 1];
	std::cout << std::endl;
	listClock = PmergeMe(list);
	dequeClock = PmergeMe(deque);
	std::cout << "After: ";
	for (i = 1; i < argc; i++)
		std::cout << " " << deque[i - 1];
	std::cout << std::endl;
	std::cout << "Time to process a range of " << argc - 1
		<< " elements with std::list :  " << std::fixed << std::setprecision(0)
		<< CLOCK_TO_US(listClock) << "us" << std::endl;
	std::cout << "Time to process a range of " << argc - 1
		<< " elements with std::deque : " << std::fixed << std::setprecision(0)
		<< CLOCK_TO_US(dequeClock) << "us" << std::endl;
	return (EXIT_SUCCESS);
}
