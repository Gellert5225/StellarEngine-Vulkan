#include <Stellar.h>

class Sandbox: public Stellar::Application {
    public:
        Sandbox() {}
        ~Sandbox() {}
};

Stellar::Application* Stellar::CreateApplication() {
	return new Sandbox();
}