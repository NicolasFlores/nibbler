#pragma once

#include "Vec2.hpp"
#include <string>

typedef unsigned int u32;

struct Color {
	Color() : r(0), g(0), b(0) {}
	Color(float r, float g, float b) : r(r), g(g), b(b) {}
	float r;
	float g;
	float b;
};

enum eNibblerError {
	NB_ERR_OK = 0,
	NB_ERR_WINDOW = 1,
};

enum class eNibblerEvent {
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NUM_1,
	NUM_2,
	NUM_3,
	LEAVE
};

class IGraphicLib {
public:
	virtual ~IGraphicLib() {}
	virtual int OpenWindow(const std::string& name, Vec2<u32> size) = 0;
	virtual void DrawSquare(Vec2<float> position, Vec2<float> size, Color color) = 0;
	virtual bool IsOpen() = 0;
	virtual eNibblerEvent PollEvents() = 0;
	virtual int PollError() = 0;
	virtual void Clear() = 0;
	virtual void Expose() = 0;
	virtual std::string GetError() = 0;
};

typedef IGraphicLib* (*t_nb_openner)(void);
typedef void (*t_nb_closer)(IGraphicLib*);
