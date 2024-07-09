#include "Headers/FrameRate.h"
#include <iostream>

FrameRate::FrameRate() : timer(0) {}

FrameRate::~FrameRate()
{
}

void FrameRate::Initialize()
{
}

void FrameRate::Load()
{
    if (font.loadFromFile("Assets/Fonts/arial.ttf"))
    {
        std::cout << "Arial.ttf font in Assets has been loaded SUCCESSFULLY" << std::endl;
        frameRateText.setFont(font);
    }
    else
    {
        std::cout << "Failed to load Arial.ttf font in Assets" << std::endl;
    }
}

void FrameRate::Update(double deltaTime, double fps)
{
    timer += deltaTime;
    if (timer >= 150.0f) {
        //std::string frameRateString = "FPS: " + std::to_string((int)(1000 / deltaTime)) + "  " + "frame time: " + std::to_string(static_cast<int>(deltaTime));
        std::string frameRateString = "FPS: " + std::to_string((int)fps);
        frameRateText.setString(frameRateString);
        timer = 0;
    }
}

void FrameRate::Draw(sf::RenderWindow& window)
{
    window.draw(frameRateText);
}
