/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/25 20:12:31 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "parsing.hpp"

class BitcoinExchange
{
	protected:
		std::map<Date, float>	data;

	public:
					BitcoinExchange(void);
					BitcoinExchange(BitcoinExchange const &other);
					~BitcoinExchange(void);
		int			setData(std::string const &filename);
		int			exchange(std::string const &filename);
		BitcoinExchange	&operator=(BitcoinExchange const &other);
};
