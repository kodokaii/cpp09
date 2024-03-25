/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:30:12 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/25 20:27:12 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <string>
#include <cerrno>
#include <cstring>
#include <climits>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include "Date.hpp"
#include "BitcoinExchange.hpp"

size_t  skipSpace(std::string const &str, size_t start = 0);
size_t	parseUint(t_uint &output, std::string const &str, size_t start = 0);
size_t	parseValue(float &output, std::string const &str, size_t star = 0);
size_t	parseDate(Date &output, std::string const &str, size_t start = 0);
size_t	parseDataLine(std::map<Date, float> &output, std::string const &str, size_t start = 0);
size_t	parseInputLine(std::pair<Date, float> &output, std::string const &str, size_t start = 0);
