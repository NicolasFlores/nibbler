/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Level.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <nflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 10:06:35 by nflores           #+#    #+#             */
/*   Updated: 2018/05/25 11:38:01 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <stdlib.h>
#include <iostream>

#include <IGraphicLib.hpp>
#include <ISoundLib.hpp>
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
	u32 _score;
	eCase *		_cases;
	eLevelState _state;
	bool		_noBorder;

	Level();
	Level(Level const & lvl);

	void spawnFood();

	Snake _snake;

public:
	Level(const u32 width, const u32 height, bool border);
	~Level();

	Level &			operator=(Level const & lvl);

	void Draw(IGraphicLib* lib);
	void Update(eNibblerEvent event, ISoundLib * sound);
	void playSound(ISoundLib * sound, std::string file);
	void stopSound(ISoundLib * sound, std::string file);

	u32	getWidth() const;
	u32	getHeight() const;
	u32 getScore() const;
	eCase*			getCases() const;
	bool			getNoBorder() const;
	void			setWidth(u32 width);
	void			setHeight(u32 height);
	void			setCases(u32 x, u32 y, eCase type);
	void			setBorder(bool border);

	eCase GetCase(u32 x, u32 y) const;
	void SetCase(u32 x, u32 y, eCase type);

	eLevelState GetState() const;
};

#endif
