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

        // 运行时间戳
        float deltaTime = 1;
        float startTime;
        float endTime;

        while (!stopFlag) {
            startTime = SDL_GetTicks();

            // window 相关事件
            windowSystem.update(stopFlag, deltaTime);

            // 进行渲染 底层基于 vulkan
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