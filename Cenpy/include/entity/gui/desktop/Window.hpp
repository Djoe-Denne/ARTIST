#pragma once

#include <component/gui/desktop/WindowComponent.hpp>
#include <entity/Entity.hpp>

namespace cenpy::entity::gui::desktop
{ /*
     template <typename T>
     concept WindowSettings = requires(T t, const Resolution &res) {
         {
             t.setResolution(res)
         } -> std::same_as<void>;
         {
             t.toggleFullscreen()
         } -> std::same_as<void>;
     };*/

    class Window : public Entity
    {
    public:
        Window() : Entity("Window", "Main window", {std::make_shared<component::gui::desktop::WindowComponent>()}) {}
    };
} // namespace cenpy::gui::desktop