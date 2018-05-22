#pragma once

#include <IGraphicLib.hpp>
#include <Vec2.hpp>
#include <SDL.h>

class SDLGraphicLib : public IGraphicLib {
public:
	SDLGraphicLib();
	~SDLGraphicLib();

	int OpenWindow(const std::string& name, Vec2<u32> size);
	void DrawSquare(Vec2<float> position, Vec2<float> size, Color color);
	bool IsOpen();
	eNibblerEvent PollEvents();
	void Clear();
	void Expose();

	int PollError();
	std::string GetError();

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	bool _isOpen;

	int _errorCode;
	std::string _errorStr;
};

extern "C" {
	IGraphicLib* createGraphicLib(void);
	void deleteGraphicLib(IGraphicLib* lib);
}
