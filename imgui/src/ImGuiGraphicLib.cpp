#include <ImGuiGraphicLib.hpp>
#include <imgui.h>
#include <imgui_impl_sdl_gl3.h>
#include <stdio.h>
#include <GL/gl3w.h>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

ImGuiGraphicLib::ImGuiGraphicLib() :
	_shader(NULL),
	_isOpen(false),
	_errorCode(0),
	_errorStr("")
{
	if ((_errorCode = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)) != 0)
		_errorStr = SDL_GetError();
	
}

ImGuiGraphicLib::~ImGuiGraphicLib() {
	delete this->_shader;
	delete this->_camera;
	ImGui_ImplSdlGL3_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(_gl_context);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

int ImGuiGraphicLib::OpenWindow(const std::string& name, Vec2<u32> size) {
	_windowSize = size;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);

	_window = SDL_CreateWindow(("ImGui " + name).c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.x, size.y, SDL_WINDOW_OPENGL);
	if (!_window) {
		_errorCode = eNibblerError::NB_ERR_WINDOW;
		_errorStr = "Could not open SDL window";
		_isOpen = false;
		return _errorCode;
	}
	_gl_context = SDL_GL_CreateContext(_window);
	SDL_GL_SetSwapInterval(1);
	gl3wInit();
	// Setup Dear ImGui binding
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	ImGui_ImplSdlGL3_Init(_window);

	// Setup style
	ImGui::StyleColorsDark();

	_shader = new Shader("./shaders/vertex.glsl", "./shaders/fragment.glsl");
	_camera = new Camera(glm::vec3(0, 0, -2), glm::vec3(0, 1, 0), 45.0f, 0);

	_proj = glm::perspective(glm::radians(45.0f), (float)size.x / size.y, 0.1f, 40.0f);
	_view = glm::mat4(1);
	_isOpen = true;

	_initMesh();

	return 0;
}

void ImGuiGraphicLib::Clear() {
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
}

void _check_gl_error() {
        GLenum err (glGetError());

        while(err!=GL_NO_ERROR) {
			std::string error;

                switch(err) {
                        case GL_INVALID_OPERATION:      error="INVALID_OPERATION";      break;
                        case GL_INVALID_ENUM:           error="INVALID_ENUM";           break;
                        case GL_INVALID_VALUE:          error="INVALID_VALUE";          break;
                        case GL_OUT_OF_MEMORY:          error="OUT_OF_MEMORY";          break;
                        case GL_INVALID_FRAMEBUFFER_OPERATION:  error="INVALID_FRAMEBUFFER_OPERATION";  break;
                }

				std::cerr << "GL_" << error.c_str() <<std::endl;
                err=glGetError();
        }
}

void ImGuiGraphicLib::Expose() {
	_view = glm::rotate(glm::mat4(1.0f), glm::radians(20.0f), glm::vec3(1.0f, 1.0f, .0f));
	int viewLoc = glGetUniformLocation(_shader->ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_view));

	int projLoc = glGetUniformLocation(_shader->ID, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(_proj));

	_shader->Use();
	if (_indices.size() > 0) {
		_updateMeshData();
		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, this->_indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	_indices.erase(_indices.begin(), _indices.end());
	_vertices.erase(_vertices.begin(), _vertices.end());

	ImGui::Render();
	ImGui_ImplSdlGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(_window);
}

void ImGuiGraphicLib::DrawSquare(Vec2<float> position, Vec2<float> size, Color color) {
	u32 currentIndex = 0;
	if (_indices.size() > 0)
		currentIndex = _indices.back() + 2;

	// Front
	_indices.push_back(currentIndex + 0);
	_indices.push_back(currentIndex + 1);
	_indices.push_back(currentIndex + 2);
	_indices.push_back(currentIndex + 1);
	_indices.push_back(currentIndex + 3);
	_indices.push_back(currentIndex + 2);

	// Back
	_indices.push_back(currentIndex + 4);
	_indices.push_back(currentIndex + 5);
	_indices.push_back(currentIndex + 6);
	_indices.push_back(currentIndex + 5);
	_indices.push_back(currentIndex + 7);
	_indices.push_back(currentIndex + 6);

	// Top
	_indices.push_back(currentIndex + 8);
	_indices.push_back(currentIndex + 9);
	_indices.push_back(currentIndex + 10);
	_indices.push_back(currentIndex + 9);
	_indices.push_back(currentIndex + 11);
	_indices.push_back(currentIndex + 10);
	
	// Top
	_indices.push_back(currentIndex + 12);
	_indices.push_back(currentIndex + 13);
	_indices.push_back(currentIndex + 14);
	_indices.push_back(currentIndex + 13);
	_indices.push_back(currentIndex + 15);
	_indices.push_back(currentIndex + 14);

	position = (position / Vec2<float>(_windowSize.x / 2, _windowSize.y / 2) - Vec2<float>(1.f, 1.f)) * Vec2<float>(1, -1);
	size = size / Vec2<float>(_windowSize.x / 2, _windowSize.y / 2);

	auto glmColor = glm::vec3(color.r, color.g, color.b);

	float offsetZ = -0.05;

	// Front
	_vertices.push_back(Vertex(glm::vec3(position.x, position.y, 0), glmColor));
	_vertices.push_back(Vertex(glm::vec3(position.x + size.x, position.y, 0), glmColor));
	_vertices.push_back(Vertex(glm::vec3(position.x, position.y - size.y, 0), glmColor));
	_vertices.push_back(Vertex(glm::vec3(position.x + size.x, position.y - size.y, 0), glmColor));
	
	// Back
	_vertices.push_back(Vertex(glm::vec3(position.x, position.y, offsetZ), glmColor));
	_vertices.push_back(Vertex(glm::vec3(position.x + size.x, position.y, offsetZ), glmColor));
	_vertices.push_back(Vertex(glm::vec3(position.x, position.y - size.y, offsetZ), glmColor));
	_vertices.push_back(Vertex(glm::vec3(position.x + size.x, position.y - size.y, offsetZ), glmColor));
	
	// Top
	_vertices.push_back(Vertex(glm::vec3(position.x, position.y, 0), glmColor));
	_vertices.push_back(Vertex(glm::vec3(position.x, position.y, offsetZ), glmColor));
	_vertices.push_back(Vertex(glm::vec3(position.x + size.x, position.y, 0), glmColor));
	_vertices.push_back(Vertex(glm::vec3(position.x + size.x, position.y, offsetZ), glmColor));
	
	// Bottom
	_vertices.push_back(Vertex(glm::vec3(position.x, position.y - size.y, 0), glmColor));
	_vertices.push_back(Vertex(glm::vec3(position.x + size.x, position.y - size.y, 0), glmColor));
	_vertices.push_back(Vertex(glm::vec3(position.x, position.y - size.y, offsetZ), glmColor));
	_vertices.push_back(Vertex(glm::vec3(position.x + size.x, position.y - size.y, offsetZ), glmColor));
}

int ImGuiGraphicLib::PollError() {
	return _errorCode;
}

std::string ImGuiGraphicLib::GetError() {
	return _errorStr;
}

bool ImGuiGraphicLib::IsOpen() {
	return _isOpen;
}

eNibblerEvent ImGuiGraphicLib::PollEvents() {
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
					case SDLK_1:
						lastEvent = eNibblerEvent::NUM_1;
						break;
					case SDLK_3:
						lastEvent = eNibblerEvent::NUM_3;
						break;
				}
				break;
		}
	}
	ImGui_ImplSdlGL3_NewFrame(_window);
	return lastEvent;
}

void ImGuiGraphicLib::_initMesh() {
	glGenVertexArrays(1, &(this->VAO));
	glGenBuffers(1, &(this->VBO));
	glGenBuffers(1, &(this->EBO));

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
	                      (void*)offsetof(Vertex, Position));

	// vertex color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
	                      (void*)offsetof(Vertex, Color));

	glBindVertexArray(0);
}

void ImGuiGraphicLib::_updateMeshData() {
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glBufferData(GL_ARRAY_BUFFER, this->_vertices.size() * sizeof(Vertex),
	             &(this->_vertices[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	             this->_indices.size() * sizeof(unsigned int),
	             &(this->_indices[0]), GL_STATIC_DRAW);
	glBindVertexArray(0);
}

IGraphicLib* createGraphicLib(void) {
	return new ImGuiGraphicLib();
}

void deleteGraphicLib(IGraphicLib* lib) {
	ImGuiGraphicLib* imguiGl = dynamic_cast<ImGuiGraphicLib*>(lib);
	delete imguiGl;
}
// ImGui - standalone example application for SDL2 + OpenGL
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)
// (GL3W is a helper library to access OpenGL functions since there is no standard header to access modern OpenGL functions easily. Alternatives are GLEW, Glad, etc.)

/*
int main(int, char**)
{
	// Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
	{
		printf("Error: %s\n", SDL_GetError());
		return -1;
	}

	// Setup window
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);
	SDL_Window* window = SDL_CreateWindow("ImGui SDL2+OpenGL3 example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
	SDL_GLContext gl_context = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(1); // Enable vsync
	gl3wInit();

	// Setup Dear ImGui binding
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	ImGui_ImplSdlGL3_Init(window);

	// Setup style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them. 
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple. 
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'misc/fonts/README.txt' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != NULL);

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Main loop
	bool done = false;
	while (!done)
	{
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSdlGL3_ProcessEvent(&event);
			if (event.type == SDL_QUIT)
				done = true;
		}
		ImGui_ImplSdlGL3_NewFrame(window);

		// 1. Show a simple window.
		// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
		{
			static float f = 0.0f;
			static int counter = 0;
			ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}

		// 2. Show another simple window. In most cases you will use an explicit Begin/End pair to name your windows.
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}

		// 3. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow(). Read its code to learn more about Dear ImGui!
		if (show_demo_window)
		{
			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
			ImGui::ShowDemoWindow(&show_demo_window);
		}

		// Rendering
		glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::Render();
		ImGui_ImplSdlGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(window);
	}

	// Cleanup
	ImGui_ImplSdlGL3_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
*/
