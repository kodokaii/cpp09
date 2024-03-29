/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:16:09 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/29 03:05:27 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <ctime>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>

template <class BidirIt>
static void _mergePair(BidirIt first, BidirIt middle, BidirIt last)
{
	typedef typename std::iterator_traits<BidirIt>::value_type	Container;

	Container	tmpBegin[distance(first, last)];
	Container	*tmpEnd;
	BidirIt		a;
	BidirIt		b;

	a = first;
	b = middle;
	tmpEnd = tmpBegin;
	while (a != middle && b != last)
	{
		if (*a < *b)
		{
			*tmpEnd++ = *a++;
			*tmpEnd++ = *a++;
		}
		else
		{
			*tmpEnd++ = *b++;
			*tmpEnd++ = *b++;
		}
	}
	while (a != middle)
	{
		*tmpEnd++ = *a++;
		*tmpEnd++ = *a++;
	}
	std::copy(tmpBegin, tmpEnd, first);
}

template <class BidirIt>
static void	_mergePairSort(BidirIt first, BidirIt last, size_t size)
{
	BidirIt		middle;
	size_t		middleSize;	

	if (2 <= size)
	{
		middle = first;
		middleSize = size / 2;
		std::advance(middle, middleSize - (middleSize % 2));
		if (2 < size)
		{
			_mergePairSort(first, middle, middleSize - (middleSize % 2));
			_mergePairSort(middle, last, middleSize + (middleSize % 2));
			_mergePair(first, middle, last);	
		}
		else if (*first < *++middle)
			std::iter_swap(first, middle);
	}
}

template <class Container, class BidirIt>
static void	_insert(Container &s, BidirIt first, BidirIt pos, size_t size)
{
	BidirIt		middle;

	if (2 <= size)
	{
		middle = first;
		std::advance(middle, size / 2);
		if (*pos < *middle)
			_insert(s, first, pos, size / 2);
		else
			_insert(s, middle, pos, (size + 1) / 2);
	}
	else
	{
		if (*first < *pos)
			s.insert(++first, *pos);
		else
			s.insert(first, *pos);
	}
}

template <class Container, class BidirIt>
static BidirIt	_insertJacobsthalSort(Container &s, BidirIt first, BidirIt last, size_t groupFirst, size_t groupEnd)
{
	BidirIt	next;

	next = first;
	if (first != last && groupFirst < groupEnd)
	{
		++next;
		if (!(groupFirst % 2) && next != last)
		{
			s.push_back(*first);
			next = _insertJacobsthalSort(s, next, last, groupFirst + 1, groupEnd);
		}
		else
		{
			next = _insertJacobsthalSort(s, next, last, groupFirst + 1, groupEnd);
			//BEUGER
			_insert(s, s.begin(), first, std::min(groupFirst, s.size()));
		}
	}
	return (next);
}

template <class Container>
clock_t			mergeInsertSort(Container &s)
{
	clock_t							clockStart(std::clock());
	size_t							groupFirst;
	typename Container::iterator	nextGroup;
	Container						x;

	s.swap(x);
	if (x.size() % 2)
		_mergePairSort(x.begin(), --x.end(), x.size());
	else
		_mergePairSort(x.begin(), x.end(), x.size());
	groupFirst = 2;
	nextGroup = _insertJacobsthalSort(s, x.begin(), x.end(), 0, groupFirst);
	while (nextGroup != x.end())
	{
		nextGroup = _insertJacobsthalSort(s, nextGroup, x.end(), groupFirst, groupFirst * 2);
		groupFirst *= 2;
	}
	return (std::clock() - clockStart);
}
