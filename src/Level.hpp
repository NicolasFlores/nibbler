/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Level.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <nflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 10:06:35 by nflores           #+#    #+#             */
/*   Updated: 2018/05/17 13:50:57 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <stdlib.h>
#include <iostream>

#include <IGraphicLib.hpp>
#include <Snake.hpp>

#define CELL_PIXEL_SIZE 10

enum eCase {
	FREE,
	FOOD,
	SNAKE,
	HEAD,
	BORDER
};

enum class eLevelState {
	PLAYING,
	WON,
	LOST,
};

class Level {

private:
	u32	_width;
	u32	_height;
	eCase *		_cases;
	eLevelState _state;

	Level();
	Level(Level const & lvl);

	void spawnFood();

	Snake _snake;

public:
	Level(const u32 width, const u32 height);
	~Level();

	Level &			operator=(Level const & lvl);

	void Draw(IGraphicLib* lib);
	void Update(eNibblerEvent event);

	u32	getWidth() const;
	u32	getHeight() const;
	eCase*			getCases() const;
	void			setWidth(u32 width);
	void			setHeight(u32 height);
	void			setCases(u32 x, u32 y, eCase type);

	eCase GetCase(u32 x, u32 y) const;
	void SetCase(u32 x, u32 y, eCase type);

	eLevelState GetState() const;
};

#endif
