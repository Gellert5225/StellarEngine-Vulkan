#include <Stellar.h>

class ExampleLayer: public Stellar::Layer {
public: 
    ExampleLayer()
        : Layer("Example") {}

    void onUpdate() override {
        // STLR_INFO("ExampleLayer::Update");
    }

    void onEvent(Stellar::Event& event) override {
        STLR_TRACE("{0}", event);
    }
};