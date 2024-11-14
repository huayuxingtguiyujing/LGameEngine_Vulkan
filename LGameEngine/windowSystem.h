#pragma once

#include <SDL.h>

#include <array>


// NOTE: WindowSystem ����ʵ����Ϸ����Ĵ��ڹ�����
// viewportHandler ��Ϊ��Ⱦ������Ⱦ�������

namespace GameEngine {

	struct WindowCreateInfo
	{
		int         width{ 800 };
		int         height{ 600 };
		const char* title{ "no name ..." };
		bool        is_fullscreen{ false };
	};

	class WindowSystem
	{
	public:
		WindowSystem();
		~WindowSystem();

		bool initWindow(WindowCreateInfo info);
		void update(bool& done, unsigned int deltaT);
		void endWindow();

		void handleEvent(bool& done, unsigned int deltaT);

		SDL_Window* getWindow() const;
		std::array<int, 2> getWindowSize() const;

	private:

		WindowCreateInfo windowInfo;

		// window
		SDL_Window* window;


	};

}

