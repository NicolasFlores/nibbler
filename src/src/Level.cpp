/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Level.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <nflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 10:17:27 by nflores           #+#    #+#             */
/*   Updated: 2018/05/25 11:37:45 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctime>
#include "Level.hpp"

// Constructors

Level::Level() : _width(0), _height(0), _score(0), _cases(NULL) {}

Level::Level(u32 width, u32 height, bool border) {
	std::srand(std::time(nullptr));
	this->_state = eLevelState::PLAYING;
	this->_noBorder = border;
	this->_width = width;
	this->_height = height;
	this->_score = 0;
	this->_cases = (eCase *)malloc((width + 1) * (height + 1) * sizeof(eCase));
	if (this->_cases == NULL) {
		std::cerr << "Malloc Error" << std::endl;
		exit(EXIT_FAILURE);
	}
	for (u32 i = 0; i < width + 1; i++) {
		for (u32 j = 0; j < height + 1; j++) {
			if (i == 0 || j == 0 || i == width || j == height)
				this->_cases[i + (width + 1) * j] = BORDER;
			else
				this->_cases[i + (width + 1) * j] = FREE;
		}
	}

	for (u32 x = 3; x < 8; x++)
		_snake.positions.push_front(Vec2<u32>(x, 3));
	this->spawnFood();

}

Level::Level(Level const & lvl) {
	this->_width = lvl.getWidth();
	this->_height = lvl.getHeight();
	this->_cases = lvl.getCases();
	this->_score = lvl.getScore();
}

Level::~Level() {
	free(this->_cases);
}

// Operators

Level &			Level::operator=(Level const & lvl) {
	this->_width = lvl.getWidth();
	this->_height = lvl.getHeight();
	this->_cases = lvl.getCases();
	this->_noBorder = lvl.getNoBorder();
	return *this;
}

// Getters and setters

u32	Level::getWidth() const {
	return this->_width + 1;
}

u32	Level::getHeight() const {
	return this->_height + 1;
}

u32 Level::getScore() const {
	return this->_score;
}
eCase*		Level::getCases() const {
	return this->_cases;
}

eCase Level::GetCase(u32 x, u32 y) const {
	return this->_cases[x + (y * (this->_width + 1))];
}

void Level::SetCase(u32 x, u32 y, eCase type) {
	this->_cases[x + (y * (this->_width + 1))] = type;
}

void			Level::setWidth(u32 width) {
	this->_width = width + 1;
}

void			Level::setHeight(u32 height) {
	this->_height = height + 1;
}

void			Level::setCases(u32 x, u32 y, eCase type) {
	this->_cases[x * y] = type;
}

bool			Level::getNoBorder() const {
	return this->_noBorder;
}

void			Level::setBorder(bool border) {
	this->_noBorder = border;
}

void Level::Update(eNibblerEvent event, ISoundLib * sound) {
	Snake::eDirection dir = _snake.getDirection();
	if (event == eNibblerEvent::UP &&
			(dir == Snake::eDirection::LEFT || dir == Snake::eDirection::RIGHT))
		_snake.setDirection(Snake::eDirection::UP);
	if (event == eNibblerEvent::DOWN &&
			(dir == Snake::eDirection::LEFT || dir == Snake::eDirection::RIGHT))
		_snake.setDirection(Snake::eDirection::DOWN);
	if (event == eNibblerEvent::LEFT &&
			(dir == Snake::eDirection::UP || dir == Snake::eDirection::DOWN))
		_snake.setDirection(Snake::eDirection::LEFT);
	if (event == eNibblerEvent::RIGHT &&
			(dir == Snake::eDirection::UP || dir == Snake::eDirection::DOWN))
		_snake.setDirection(Snake::eDirection::RIGHT);

	// Update snake pos
	Vec2<u32> snakePos = _snake.positions.at(0);
	if (_snake.getDirection() == Snake::eDirection::RIGHT)
		snakePos.x++;
	if (_snake.getDirection() == Snake::eDirection::LEFT) {
		if (snakePos.x == 1 && _noBorder)
			snakePos.x = this->_width - 1;
		else
			snakePos.x--;
	}
	if (_snake.getDirection() == Snake::eDirection::DOWN)
		snakePos.y++;
	if (_snake.getDirection() == Snake::eDirection::UP) {
		if (snakePos.y == 1 && _noBorder)
			snakePos.y = this->_height - 1;
		else
			snakePos.y--;
	}
	if (snakePos.x >= this->_width && _noBorder)
		snakePos.x = 1;

	if (snakePos.y >= this->_height && _noBorder)
		snakePos.y = 1;

	// Check the content of the new position of the snake
	eCase content = this->GetCase(snakePos.x, snakePos.y);
	if (content == SNAKE || (!_noBorder && content == BORDER)) {
		_state = eLevelState::LOST;
		if (sound) {
			this->playSound(sound, "fail-trombone-01.wav");
			sleep(5);
		}
		return;
	}
	if (content == FOOD) {
		this->SetCase(snakePos.x, snakePos.y, FREE);
		this->spawnFood();
		this->_score++;
		if (sound)
			this->playSound(sound, "lib/irrKlang/irrKlang-64bit-1.6.0/media/bell.wav");
	} else {
		_snake.positions.pop_back();
	}

	_snake.positions.push_front(snakePos);

	//Update grid content

	// Clear snake position
	for (u32 x = 0; x < this->_width + 1; x++) {
		for (u32 y = 0; y < this->_height + 1; y++) {
			if (this->GetCase(x, y) == SNAKE)
				this->SetCase(x, y, FREE);
		}
	}

	// Mark snake positions
	for (auto &elem : _snake.positions)
		this->SetCase(elem.x, elem.y, eCase::SNAKE);
}

void Level::Draw(IGraphicLib* lib) {
	Vec2<u32> snakeHead = _snake.positions.at(0);
	for (u32 x = 0; x < this->_width + 1; x++) {
		for (u32 y = 0; y < this->_height + 1; y++) {
			eCase content = this->GetCase(x, y);
			if (content == eCase::SNAKE) {
				Color c;
				if (x == snakeHead.x && y == snakeHead.y)
					c.b = 255.0f;
				else
					c.g = 255.0f;
				lib->DrawSquare(
						Vec2<float>(x * CELL_PIXEL_SIZE, y * CELL_PIXEL_SIZE),
						Vec2<float>(CELL_PIXEL_SIZE, CELL_PIXEL_SIZE),
						c,
						this->_score
						);
			} else if (content == eCase::FOOD) {
				lib->DrawSquare(
						Vec2<float>(x * CELL_PIXEL_SIZE, y * CELL_PIXEL_SIZE),
						Vec2<float>(CELL_PIXEL_SIZE, CELL_PIXEL_SIZE),
						Color(255, 0, 0),
						this->_score
						);
			}
			else if (content == eCase::BORDER) {
				lib->DrawSquare(
						Vec2<float>(x * CELL_PIXEL_SIZE, y * CELL_PIXEL_SIZE),
						Vec2<float>(CELL_PIXEL_SIZE, CELL_PIXEL_SIZE),
						Color(255, 255, 255),
						this->_score
						);
			}
		}
	}
}

void Level::playSound(ISoundLib * sound, std::string file) {
	sound->playMusic(file, false);
}

void Level::spawnFood() {
	// First check if at least one cell is available
	bool isAvailable = false;
	for (u32 x = 0; x < this->_width + 1; x++) {
		for (u32 y = 0; y < this->_height + 1; y++) {
			if (this->GetCase(x, y) == eCase::FREE)
				isAvailable = true;
		}
	}
	if (!isAvailable) {
		this->_state = eLevelState::WON;
		return;
	}

	u32 randX, randY;
	do {
		randX = std::rand() % this->_width;
		randY = std::rand() % this->_height;
	} while (this->GetCase(randX, randY) != eCase::FREE);
	this->SetCase(randX, randY, eCase::FOOD);
}

eLevelState Level::GetState() const {
	return _state;
}
