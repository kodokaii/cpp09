/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/25 20:51:10 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &other): data(other.data)
{
}

BitcoinExchange::~BitcoinExchange(void)
{
}

int			BitcoinExchange::setData(std::string const &filename)
{
    std::ifstream   file;
    std::string     line;
    t_uint          lineCount;

    lineCount = 1;
    file.open(filename.c_str());
    if (file.is_open())
	{
		try
		{
			getline(file, line);
			while (!file.eof())
			{
				lineCount++;
				getline(file, line);
				if (skipSpace(line) != line.size())
					parseDataLine(this->data, line);
			}
			if (lineCount < 1)
			{
				std::cerr << "Error: " << filename << ": missing data" << std::endl;
				return (EXIT_FAILURE);
			}
		}
		catch (std::exception &e)
		{
			std::cerr << "Error: " << filename << ": line " << lineCount << ": " << e.what() << std::endl;
			return (EXIT_FAILURE);
		}
	}
	else
	{
		std::cerr << "Error: " << filename << ": " << std::strerror(errno) << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		BitcoinExchange::exchange(std::string const &filename)
{
	std::map<Date, float>::iterator	upper;
	std::pair<Date, float>			input;
    std::ifstream					file;
    std::string						line;
    t_uint							lineCount;

    lineCount = 1;
    file.open(filename.c_str());
    if (file.is_open())
	{
		getline(file, line);
		while (!file.eof())
		{
			try
			{
				lineCount++;
				getline(file, line);
				if (skipSpace(line) != line.size())
				{
					parseInputLine(input, line);
					upper = this->data.upper_bound(input.first);
					if (upper == this->data.begin())
						throw (std::runtime_error("no entry in data base"));
					std::cout << input.first << " => " << input.second <<
						" = " << input.second * (*--upper).second << std::endl;
				}
			}
			catch (std::exception &e)
			{
				std::cerr << "Error: " << filename << ": line " << lineCount << ": " << e.what() << std::endl;
			}
		}
		if (lineCount < 1)
		{
			std::cerr << "Error: " << filename << ": missing input" << std::endl;
			return (EXIT_FAILURE);
		}
	}
	else
	{
		std::cerr << "Error: " << filename << ": " << std::strerror(errno) << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

BitcoinExchange	&BitcoinExchange::operator=(BitcoinExchange const &other)
{
	this->data = other.data;
	return (*this);
}
