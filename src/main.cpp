#include <Vec2.hpp>
#include <unistd.h>
#include <dlfcn.h>
#include <string.h>
#include <iostream>

#include <IGraphicLib.hpp>
#include <Level.hpp>

// time step in seconds
constexpr float gameTimeStep = 0.1f;

void	dlerror_print() {
	std::cerr << dlerror() << std::endl;
	exit(EXIT_FAILURE);
}

void    err_handler(int argc, char **argv, void **dl_handler) {
        if (argc != 4) {
                std::cerr << "Usage : ./nibbler [map_width] [map_height] [library]" << std::endl;
                exit(EXIT_FAILURE);
        }
        if (atoi(argv[1]) < 20 || atoi(argv[2]) < 20) {
                std::cerr << "Map size must be at least 20x20" << std::endl;
                exit(EXIT_FAILURE);
        }
        if (atoi(argv[1]) > 40 || atoi(argv[2]) > 40) {
                std::cerr << "Map size must be 40x40 max" << std::endl;
                exit(EXIT_FAILURE);
        }
	if (strcmp(argv[3], "sdl") == 0)
	        *dl_handler = dlopen("./sdl/nibbler_sdl.so", RTLD_LAZY | RTLD_LOCAL);
	else if (strcmp(argv[3], "ncurses") == 0)
		*dl_handler = dlopen("./ncurses/nibbler_ncurses.so", RTLD_LAZY | RTLD_LOCAL);
	else if (strcmp(argv[3], "imgui") == 0)
	        *dl_handler = dlopen("./imgui/nibbler_imgui.so", RTLD_LAZY | RTLD_LOCAL);
	else
		*dl_handler = dlopen(argv[3], RTLD_LAZY | RTLD_LOCAL);
        if (*dl_handler == NULL)
			dlerror_print();
}

int main(int argc, char **argv) {
	void			*dlHandler;
	unsigned int    width;
    unsigned int    height;

	err_handler(argc, argv, &dlHandler);

	width = atoi(argv[1]);// * 10;
	height = atoi(argv[2]);// * 10;
	t_nb_openner openFunc = (t_nb_openner)dlsym(dlHandler, "createGraphicLib");
	t_nb_closer closeFunc = (t_nb_closer)dlsym(dlHandler, "deleteGraphicLib");

	if (openFunc == NULL || closeFunc == NULL)
		dlerror_print();

	IGraphicLib* lib = openFunc();

	Vec2<u32> windowSize(width * CELL_PIXEL_SIZE, height * CELL_PIXEL_SIZE);
	lib->OpenWindow("Nibbler", windowSize);

	Level level(width, height);

	while (lib->IsOpen()) {
		eNibblerEvent event = lib->PollEvents();
		if (event == eNibblerEvent::NUM_1) {
			closeFunc(lib);
			dlclose(dlHandler);
			dlHandler = dlopen("./sdl/nibbler_sdl.so", RTLD_LAZY | RTLD_LOCAL);
			openFunc = (t_nb_openner)dlsym(dlHandler, "createGraphicLib");
			closeFunc = (t_nb_closer)dlsym(dlHandler, "deleteGraphicLib");
			if (dlHandler == NULL || openFunc == NULL || closeFunc == NULL)
				dlerror_print();
			lib = openFunc();
			lib->OpenWindow("Nibbler", windowSize);
			event = lib->PollEvents();
		}
		else if (event == eNibblerEvent::NUM_2) {
			closeFunc(lib);
			dlclose(dlHandler);
			dlHandler = dlopen("./imgui/nibbler_imgui.so", RTLD_LAZY | RTLD_LOCAL);
			openFunc = (t_nb_openner)dlsym(dlHandler, "createGraphicLib");
			closeFunc = (t_nb_closer)dlsym(dlHandler, "deleteGraphicLib");
			if (dlHandler == NULL || openFunc == NULL || closeFunc == NULL)
				dlerror_print();
			lib = openFunc();
			lib->OpenWindow("Nibbler", windowSize);
			event = lib->PollEvents();
		}
		else if (event == eNibblerEvent::NUM_3) {
			closeFunc(lib);
			dlclose(dlHandler);
			dlHandler = dlopen("./ncurses/nibbler_ncurses.so", RTLD_LAZY | RTLD_LOCAL);
			openFunc = (t_nb_openner)dlsym(dlHandler, "createGraphicLib");
			closeFunc = (t_nb_closer)dlsym(dlHandler, "deleteGraphicLib");
			if (dlHandler == NULL || openFunc == NULL || closeFunc == NULL)
				dlerror_print();
			lib = openFunc();
			lib->OpenWindow("Nibbler", windowSize);
			event = lib->PollEvents();
		}
		lib->Clear();
		level.Update(event);

		if (level.GetState() != eLevelState::PLAYING)
			break;

		level.Draw(lib);
		lib->Expose();
		//@TODO: sleeping too long here makes the window closing time too big
		usleep((int)(gameTimeStep * 1000000));
	}

	closeFunc(lib);
	dlclose(dlHandler);

	return 0;
}
