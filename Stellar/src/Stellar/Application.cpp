#include "Application.h"
#include <iostream>

namespace Stellar {
    Application::Application() {}

    Application::~Application() {}

    void Application::run() {
        std::cout << "Hello wor" << std::endl;
    }
}