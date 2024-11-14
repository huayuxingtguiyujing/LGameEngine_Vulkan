#include "WindowSystem.h"

#include <iostream>

namespace GameEngine {

	WindowSystem::WindowSystem() {
	}
	WindowSystem::~WindowSystem() {
	}

	bool WindowSystem::initWindow(WindowCreateInfo info) {
		// sdl init
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			//return 1;
			return false;
		}

		// create sdl window
		window = SDL_CreateWindow(
			"Vulkan Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			info.width, info.height, SDL_WINDOW_VULKAN
		);
		if (window == NULL) {
			std::cout << "Window init failed" << std::endl;
			//return false;
		}

		std::cout << "windowSystem 成功初始化" << std::endl;
		return true;
	}

	void WindowSystem::update(bool& done, unsigned int deltaT) {
		handleEvent(done, deltaT);
	}

	void WindowSystem::endWindow() {
		SDL_DestroyWindow(window);
		window = nullptr;
		SDL_Quit();
	}

	// 处理所有的时间，放到 mainloop 中执行
	void WindowSystem::handleEvent(bool& done, unsigned int deltaT) {
		SDL_Event sdlEvent;
		// 获取当前的事件
		while (SDL_PollEvent(&sdlEvent)) {

			if (sdlEvent.type == SDL_QUIT) {
				// TODO: 中止程序
				done = false;
				return;
			}
			else {
				float cameraSpeed = 1;

				if (sdlEvent.type == SDL_KEYDOWN) {
					// SDL事件: 键盘输入
					// Key 1-6: 切换场景
					// Key ESC: 关闭应用
					// Key WASD QE: 控制视角移动旋转
					// Key R: 重置摄像机
					// Key Tab: 切换相机orbit模式

					switch (sdlEvent.key.keysym.sym) {
						// 移动视角
					case SDLK_a:
						std::cout << "按下了SDLK a" << std::endl;
						break;
					case SDLK_s:
						std::cout << "按下了SDLK s" << std::endl;
						break;
					case SDLK_d:
						std::cout << "按下了SDLK d" << std::endl;
						break;
					case SDLK_w:
						std::cout << "按下了SDLK w" << std::endl;
						break;

						// 旋转视角
					case SDLK_q:
						std::cout << "按下了SDLK q" << std::endl;
						break;
					case SDLK_e:
						std::cout << "按下了SDLK e" << std::endl;
						break;

						// reset
					case SDLK_r:
						break;

						// 切换场景
					case SDLK_1:
						std::cout << "按下了SDLK 1" << std::endl;
						break;
					case SDLK_2:
						std::cout << "按下了SDLK 2" << std::endl;
						break;
					case SDLK_3:
						std::cout << "按下了SDLK 3" << std::endl;
						break;

						// 退出程序
					case SDLK_ESCAPE:
						done = true;
						break;
					}

				}
				else if (sdlEvent.type == SDL_MOUSEMOTION) {
					// SDL事件: 鼠标移动

				}
				else if (sdlEvent.type == SDL_MOUSEWHEEL) {
					// SDL事件: 鼠标滚轮滚动

				}
			}
		}
	}


	SDL_Window* WindowSystem::getWindow() const {
		return window;
	}

	std::array<int, 2> WindowSystem::getWindowSize() const {
		std::array<int, 2> widthAndHeight{ windowInfo.width, windowInfo .height};
		return widthAndHeight;
	}

}