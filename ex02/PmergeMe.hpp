/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:16:09 by nlaerema          #+#    #+#             */
/*   Updated: 2024/11/12 09:29:52 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <ctime>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>

namespace std 
{
	template< class InputIt >
	InputIt next(InputIt it, size_t n)
	{
		std::advance(it, n);
		return (it);
	}
}

template <typename Integer>
inline Integer floorMult(Integer i, Integer mult)
{
	return (i - i % mult);
}

template <class InputIt>
struct Unit {
	InputIt	begin;
	InputIt value;
	InputIt end;

	InputIt init(InputIt it, size_t unitSize)
	{
		this->begin = it;
		std::advance(it, unitSize - 1);
		this->value = it;		
		it++;
		this->end = it;
		return (it);
	}
};

template <class Container>
static void	_pairSort(Container &x, size_t unitSize)
{
	typedef typename Container::iterator	InputIt;
	Unit<InputIt>	unit[2];
	InputIt			it;

	it = x.begin();
	for (size_t i = 0; i + unitSize * 2 <= x.size(); i += unitSize * 2)
	{
		it = unit[0].init(it, unitSize);
		it = unit[1].init(it, unitSize);
		if (*unit[1].value < *unit[0].value)
			std::swap_ranges(unit[0].begin, unit[0].end, unit[1].begin);
	}
}

template <class Container, class InputIt>
static void	_insert(Container &s, InputIt first, Unit<InputIt> const &unit, size_t unitSize, size_t size)
{
	size_t			middleSize;
	Unit<InputIt>	middle;

	if (2 * unitSize <= size)
	{
		middleSize = floorMult(size / 2, unitSize);
		middle.init(std::next(first, middleSize), unitSize);
		if (*unit.value < *middle.value)
			_insert(s, first, unit, unitSize, middleSize);
		else
			_insert(s, middle.begin, unit, unitSize, size - middleSize);
	}
	else if (unitSize <= size)
	{
		middle.init(first, unitSize);
		if (*middle.value < *unit.value)
			s.insert(middle.end, unit.begin, unit.end);
		else
			s.insert(first, unit.begin, unit.end);
	}
	else
		s.insert(first, unit.begin, unit.end);
}

template <class Container, class InputIt>
static InputIt	_insertGroup(Container &s, InputIt it, InputIt end, size_t unitSize, size_t size, bool odd)
{
	if (it != end)
	{
		Unit<InputIt> unit;

		unit.init(it, unitSize);
		if (odd)
		{
			s.insert(s.end(), unit.begin, unit.end);
			it = _insertGroup(s, unit.end, end, unitSize, size, !odd);
		}
		else
		{
			if (s.size() < size)
				it = _insertGroup(s, unit.end, end, unitSize, size, !odd);
			_insert(s, s.begin(), unit, unitSize, std::min(size, s.size()));
		}
	}
	return (it);
}

template <class Container>
static void _insertSort(Container &s, Container &x, size_t unitSize)
{
	typedef typename Container::iterator	InputIt;
	size_t	insertSize = 1;
	size_t	powerTwo = 1;
	InputIt	end;
	InputIt	it;

	it = std::next(x.begin(), unitSize);
	end = std::next(x.begin(), floorMult(x.size(), unitSize));
	s.insert(s.begin(), x.begin(), it);
	while (it != end)
	{
		powerTwo *= 2;
		insertSize += powerTwo;
		it = _insertGroup(s, it, end, unitSize, insertSize * unitSize, true);
		if (it != end)
			std::advance(it, unitSize);
	}
	s.insert(s.end(), end, x.end());
}

template <class Container>
static void	_mergeInsertSort(Container &s, size_t unitSize)
{
	if (unitSize * 2 <= s.size())
	{
		Container	x;

		s.swap(x);
		_pairSort(x, unitSize);
		_mergeInsertSort(x, unitSize * 2);
		_insertSort(s, x, unitSize);
	}
}

template <class Container>
clock_t	PmergeMe(Container &s)
{
	clock_t	clockStart(std::clock());
	_mergeInsertSort(s, 1);
	return (std::clock() - clockStart);
}
