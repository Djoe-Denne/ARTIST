#pragma once

#include <component/gui/desktop/WindowComponent.hpp>
#include <entity/Entity.hpp>

namespace cenpy::entity::gui::desktop
{
    class Window : public Entity
    {
    public:
        Window() : Entity("Window", "Main window", {std::make_shared<component::gui::desktop::WindowComponent>()}) {}
    };
} // namespace cenpy::gui::desktop