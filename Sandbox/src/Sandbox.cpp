#include <Stellar.h>

#include "ExampleLayer.h"

class Sandbox: public Stellar::Application {
    public:
        Sandbox() {
            pushLayer(new ExampleLayer());
        }
        ~Sandbox() {}
};

Stellar::Application* Stellar::CreateApplication() {
	return new Sandbox();
}