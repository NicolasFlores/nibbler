#include <SDLGraphicLib.hpp>

SDLGraphicLib::SDLGraphicLib() :
	_isOpen(false),
	_errorCode(0),
	_errorStr("")
{
	if ((_errorCode = SDL_Init(SDL_INIT_VIDEO)) != 0)
		_errorStr = SDL_GetError();
}

SDLGraphicLib::~SDLGraphicLib() {
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

int SDLGraphicLib::OpenWindow(const std::string& name, Vec2<u32> size) {
	_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			size.x, size.y, SDL_WINDOW_SHOWN);
	if (!_window) {
		_errorCode = eNibblerError::NB_ERR_WINDOW;
		_errorStr = "Could not open SDL window";
		_isOpen = false;
		return _errorCode;
	}
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	_isOpen = true;
	return 0;
}

void SDLGraphicLib::Clear() {
	SDL_RenderClear(_renderer);
}

void SDLGraphicLib::Expose() {
	SDL_RenderPresent(_renderer);
}

void SDLGraphicLib::DrawSquare(Vec2<float> position, Vec2<float> size, Color color) {
	SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, 255);
	SDL_Rect r = {
		.x = (int)position.x,
		.y = (int)position.y,
		.w = (int)size.x,
		.h = (int)size.y
	};
	SDL_RenderFillRect(_renderer, &r);
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
}

int SDLGraphicLib::PollError() {
	return _errorCode;
}

std::string SDLGraphicLib::GetError() {
	return _errorStr;
}

bool SDLGraphicLib::IsOpen() {
	return _isOpen;
}

eNibblerEvent SDLGraphicLib::PollEvents() {
	SDL_Event event;
	eNibblerEvent lastEvent = eNibblerEvent::NONE;

	while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				_isOpen = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						_isOpen = false;
						break;
					case SDLK_w:
					case SDLK_UP:
						lastEvent = eNibblerEvent::UP;
						break;
					case SDLK_s:
					case SDLK_DOWN:
						lastEvent = eNibblerEvent::DOWN;
						break;
					case SDLK_a:
					case SDLK_LEFT:
						lastEvent = eNibblerEvent::LEFT;
						break;
					case SDLK_d:
					case SDLK_RIGHT:
						lastEvent = eNibblerEvent::RIGHT;
						break;
					case SDLK_2:
						lastEvent = eNibblerEvent::NUM_2;
						break;
					case SDLK_3:
						lastEvent = eNibblerEvent::NUM_3;
						break;
				}
				break;
		}
	}
	return lastEvent;
}

IGraphicLib* createGraphicLib(void) {
	return new SDLGraphicLib();
}

void deleteGraphicLib(IGraphicLib* lib) {
	SDLGraphicLib* sdlGl = dynamic_cast<SDLGraphicLib*>(lib);
	delete sdlGl;
}
