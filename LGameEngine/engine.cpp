#include "Engine.h"


namespace GameEngine {

    bool Engine::init() {

        WindowCreateInfo info = WindowCreateInfo();
        windowSystem.initWindow(info);

        renderSystem.initRender(&windowSystem);

        return true;
    }

    void Engine::tick() {
        bool stopFlag = false;

        // ����ʱ���
        float deltaTime = 1;
        float startTime;
        float endTime;

        while (!stopFlag) {
            startTime = SDL_GetTicks();

            // window ����¼�
            windowSystem.update(stopFlag, deltaTime);

            // ������Ⱦ �ײ���� vulkan
            //vulkanRHI.mainLoop();
            renderSystem.render();

            endTime = SDL_GetTicks();
            deltaTime = endTime - startTime;
        }

    }

    void Engine::end() {
        windowSystem.endWindow();
        renderSystem.endRender();
    }

}