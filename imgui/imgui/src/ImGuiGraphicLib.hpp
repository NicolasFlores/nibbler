#pragma once

#include <vector>

#include <IGraphicLib.hpp>
#include <Vec2.hpp>
#include <SDL.h>
#include <Shader.hpp>
#include <Camera.hpp>
#include <glm/mat4x4.hpp>

struct Vertex {
	Vertex() {}
	Vertex(glm::vec3 p, glm::vec3 c) : Position(p), Color(c) {}
	glm::vec3 Position;
	glm::vec3 Color;
};

class ImGuiGraphicLib : public IGraphicLib {
public:
	ImGuiGraphicLib();
	~ImGuiGraphicLib();

	ImGuiGraphicLib &	operator=(ImGuiGraphicLib const & imgl);

	int OpenWindow(const std::string& name, Vec2<u32> size);
	void DrawSquare(Vec2<float> position, Vec2<float> size, Color color, u32 score);
	bool IsOpen() const;
	eNibblerEvent PollEvents();
	void Clear();
	void Expose();

	int PollError() const;
	std::string GetError() const;
	SDL_Window * getWin() const;
	Vec2<u32>	getSize() const;
	SDL_GLContext getContext() const;
	Shader *	getShader() const;
	Camera *	getCamera() const;
	glm::mat4	getProj() const;
	glm::mat4	getView() const;
	u32			getVAO() const;
	u32			getVBO() const;
	u32			getEBO() const;
	std::vector<Vertex> getVertices() const;
	std::vector<u32> getIndices() const;

private:
	void _initMesh();
	void _updateMeshData();
	SDL_Window* _window;
	Vec2<u32> _windowSize;
	SDL_GLContext _gl_context;
	Shader* _shader;
	Camera* _camera;
	bool _isOpen;

	int _errorCode;
	std::string _errorStr;

	glm::mat4 _proj;
	glm::mat4 _view;
	
	unsigned int VAO, VBO, EBO;
	
	std::vector<Vertex> _vertices;
	std::vector<unsigned int> _indices;

	ImGuiGraphicLib(ImGuiGraphicLib const & imgl);
};

extern "C" {
	IGraphicLib* createGraphicLib(void);
	void deleteGraphicLib(IGraphicLib* lib);
}
