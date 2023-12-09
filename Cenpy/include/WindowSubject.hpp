#pragma once

#include <gui/desktop/WindowComponent.hpp>
#include <common/pattern/observer/Subject.hpp>

namespace gui::desktop
{
    SUBJECT(WindowComponent, setResolution, toggleFullscreen)

}
