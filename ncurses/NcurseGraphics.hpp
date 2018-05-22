/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NcurseGraphics.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <nflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 09:50:49 by nflores           #+#    #+#             */
/*   Updated: 2018/05/15 13:17:20 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NCURSE_GRAPHICS_HPP
#define NCURSE_GRAPHICS_HPP

#include "../src/IGraphicLib.hpp"
#include "../src/Vec2.hpp"

#include <curses.h>
#include <unistd.h>

class NcurseGraphics : public IGraphicLib {

public:
	NcurseGraphics();
	~NcurseGraphics();

	int 			OpenWindow(const std::string& name, Vec2<u32> size);
	void 			DrawSquare(Vec2<float> position, Vec2<float> size, Color color);
	eNibblerEvent	PollEvents();
	int 			PollError();
	void 			Clear();
	void 			Expose();
	std::string 	GetError();
	bool			IsOpen();

private:
	WINDOW *		_win;
	bool			_isOpen;
	int				_errorCode;
	std::string 	_errorStr;
};

extern "C" {
	IGraphicLib *	createGraphicLib();
	void			deleteGraphicLib(IGraphicLib * lib);
}


#endif
