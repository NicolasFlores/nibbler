/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <nflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 11:11:54 by nflores           #+#    #+#             */
/*   Updated: 2018/05/14 10:10:06 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Snake.hpp"

// Constructors

Snake::Snake() : _direction(eDirection::RIGHT) {}

Snake::Snake(const Snake& rhs) {
	*this = rhs;
}

Snake& Snake::operator=(const Snake& rhs) {
	this->positions = rhs.positions;
	return *this;
}

Snake::eDirection Snake::getDirection() const {
	return this->_direction;
}

void Snake::setDirection(Snake::eDirection dir) {
	this->_direction = dir;
}
