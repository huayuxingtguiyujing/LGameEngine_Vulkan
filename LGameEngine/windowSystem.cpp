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

		std::cout << "windowSystem �ɹ���ʼ��" << std::endl;
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

	// �������е�ʱ�䣬�ŵ� mainloop ��ִ��
	void WindowSystem::handleEvent(bool& done, unsigned int deltaT) {
		SDL_Event sdlEvent;
		// ��ȡ��ǰ���¼�
		while (SDL_PollEvent(&sdlEvent)) {

			if (sdlEvent.type == SDL_QUIT) {
				// TODO: ��ֹ����
				done = false;
				return;
			}
			else {
				float cameraSpeed = 1;

				if (sdlEvent.type == SDL_KEYDOWN) {
					// SDL�¼�: ��������
					// Key 1-6: �л�����
					// Key ESC: �ر�Ӧ��
					// Key WASD QE: �����ӽ��ƶ���ת
					// Key R: ���������
					// Key Tab: �л����orbitģʽ

					switch (sdlEvent.key.keysym.sym) {
						// �ƶ��ӽ�
					case SDLK_a:
						std::cout << "������SDLK a" << std::endl;
						break;
					case SDLK_s:
						std::cout << "������SDLK s" << std::endl;
						break;
					case SDLK_d:
						std::cout << "������SDLK d" << std::endl;
						break;
					case SDLK_w:
						std::cout << "������SDLK w" << std::endl;
						break;

						// ��ת�ӽ�
					case SDLK_q:
						std::cout << "������SDLK q" << std::endl;
						break;
					case SDLK_e:
						std::cout << "������SDLK e" << std::endl;
						break;

						// reset
					case SDLK_r:
						break;

						// �л�����
					case SDLK_1:
						std::cout << "������SDLK 1" << std::endl;
						break;
					case SDLK_2:
						std::cout << "������SDLK 2" << std::endl;
						break;
					case SDLK_3:
						std::cout << "������SDLK 3" << std::endl;
						break;

						// �˳�����
					case SDLK_ESCAPE:
						done = true;
						break;
					}

				}
				else if (sdlEvent.type == SDL_MOUSEMOTION) {
					// SDL�¼�: ����ƶ�

				}
				else if (sdlEvent.type == SDL_MOUSEWHEEL) {
					// SDL�¼�: �����ֹ���

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