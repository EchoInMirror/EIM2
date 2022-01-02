#pragma once

#include "Main.h"
#include "MainComponent.h"

MainComponent::MainComponent() {
    setSize(600, 400);
}

void MainComponent::paint(juce::Graphics& g) {
}

void MainComponent::resized() {
#ifndef OS_WIN
    return;
#endif
    auto app = ((GuiAppApplication*)juce::JUCEApplication::getInstance())->getBrowserApp().get();
    if (!app) return;
    auto root = app->getInstance().get()->GetRootBrowser().get();
    if (root) MoveWindow(root->GetHost().get()->GetWindowHandle(), 0, 0, getWidth(), getHeight(), TRUE);
}
