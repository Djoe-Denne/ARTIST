#pragma once
#include <iostream>
#include <graphic/scene/SceneGraph.hpp>

// Simple Drawable
class Drawable : public SceneNode
{
public:
    void draw() const override
    {
        // Implement drawing logic for the Drawable
        std::cout << "Drawing a Drawable\n";
    }
};