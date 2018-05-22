/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <nflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:57:06 by nflores           #+#    #+#             */
/*   Updated: 2018/05/14 10:09:01 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <IGraphicLib.hpp>
#include <deque>

class Snake {
public:
	enum class eDirection {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	Snake();
	Snake(const Snake& rhs);

	Snake& operator=(const Snake& rhs);

	eDirection getDirection() const;
	void setDirection(eDirection dir);
	std::deque<Vec2<u32>> positions;

private:
	eDirection _direction;

};

#endif
