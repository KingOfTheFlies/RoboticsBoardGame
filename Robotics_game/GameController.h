#pragma once

#include "Application.h"

class GameController {
public:
    GameController(Application* app) : app_(app) {};
    void Run();
    void Run(const TimeSpan& max_app_time);
protected:
    Application* app_;
};

