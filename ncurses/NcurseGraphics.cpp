/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NcurseGraphics.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <nflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 11:21:40 by nflores           #+#    #+#             */
/*   Updated: 2018/05/22 11:06:10 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NcurseGraphics.hpp"

// Constructors

NcurseGraphics::NcurseGraphics() : _win(NULL), _isOpen(false), _errorCode(0), _errorStr("") {
	// system("osascript window");
	initscr();
	start_color();
    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
	init_pair(3, COLOR_BLACK, COLOR_BLUE);
	init_pair(4, COLOR_BLACK, COLOR_WHITE);
	cbreak();
	nodelay(stdscr, true);
	nonl();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);
	refresh();
}

NcurseGraphics::~NcurseGraphics() {
	endwin();
}

// Methods

int				NcurseGraphics::OpenWindow(const std::string& name, Vec2<u32> size) {
	(void) name;
	(void) size;
	_win = stdscr; //subwin(stdscr, size.y, size.x, 0, 0);
	if (!_win) {
		_errorCode = eNibblerError::NB_ERR_WINDOW;
		_errorStr = "Could not open Ncurses window";
		return _errorCode;
	}
	wrefresh(_win);
	_isOpen = true;
	return 0;
}

void			NcurseGraphics::DrawSquare(Vec2<float> position, Vec2<float> size, Color color) {
	(void) size;
	(void) position;
	if (color.b == 255.0f) {
		move((int)(position.y / 10), (int)(position.x / 10));
		attron(COLOR_PAIR(3));
	}
	else if (color.g == 255.0f) {
		move((int)(position.y / 10), (int)(position.x / 10));
		attron(COLOR_PAIR(2));
	}
	else if (color.r == 255.0f) {
		move((int)(position.y / 10), (int)(position.x / 10));
		attron(COLOR_PAIR(1));
	}
	else if (color.r == 0 == color.b == color.g) {
		move((int)(position.y / 10), (int)(position.x / 10));
		attron(COLOR_PAIR(4));
	}
	else {	
		move((int)(position.y / 10), (int)(position.x / 10));
		attron(COLOR_PAIR(0));
	}
	printw(" ");
	wrefresh(_win);
}

eNibblerEvent	NcurseGraphics::PollEvents() {
	clear();

	int key;
	eNibblerEvent ret = eNibblerEvent::NONE;

	while ((key = getch()) != -1) {
		switch (key) {
			case KEY_END:
				_isOpen = false;
				ret = eNibblerEvent::LEAVE;
				endwin();
				break;
			case 27:
				_isOpen = false;
				ret = eNibblerEvent::LEAVE;
				endwin();
				break;
			case KEY_UP:
				ret = eNibblerEvent::UP;
				break;
			case KEY_DOWN:
				ret = eNibblerEvent::DOWN;
				break;
			case KEY_LEFT:
				ret = eNibblerEvent::LEFT;
				break;
			case KEY_RIGHT:
				ret = eNibblerEvent::RIGHT;
				break;
			case 49:
				ret = eNibblerEvent::NUM_1;
				break;
			case 50:
				ret = eNibblerEvent::NUM_2;
				break;
		}
	}
	return ret;
}

void			NcurseGraphics::Clear() {
	clear();
}

void 			NcurseGraphics::Expose() {}

// getters setters

int 			NcurseGraphics::PollError() {
	return _errorCode;
}

bool 			NcurseGraphics::IsOpen() {
	return _isOpen;
}

std::string		NcurseGraphics::GetError() {
	return _errorStr;
}

IGraphicLib* 	createGraphicLib(void) {
	return new NcurseGraphics();
}

void 			deleteGraphicLib(IGraphicLib* lib) {
	NcurseGraphics * nc = dynamic_cast<NcurseGraphics *>(lib);
	delete nc;
}
