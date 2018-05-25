#pragma once

#include <IGraphicLib.hpp>
#include <Vec2.hpp>
#include <SDL.h>

class SDLGraphicLib : public IGraphicLib {
public:
	SDLGraphicLib();
	~SDLGraphicLib();

	SDLGraphicLib &	operator=(SDLGraphicLib const & sgl);

	int OpenWindow(const std::string& name, Vec2<u32> size);
	void DrawSquare(Vec2<float> position, Vec2<float> size, Color color, u32 score);
	bool IsOpen() const;
	eNibblerEvent PollEvents();
	void Clear();
	void Expose();

	int PollError() const;
	std::string GetError() const;
	SDL_Window * getWin() const;
	SDL_Renderer * getRenderer() const;

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	bool _isOpen;

	int _errorCode;
	std::string _errorStr;

	SDLGraphicLib(SDLGraphicLib const &sgl);
};

extern "C" {
	IGraphicLib* createGraphicLib(void);
	void deleteGraphicLib(IGraphicLib* lib);
}
