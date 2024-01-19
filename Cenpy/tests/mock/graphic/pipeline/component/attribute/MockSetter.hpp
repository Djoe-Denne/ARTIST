// file: Binder

#pragma once

#include <memory>
#include <graphic/shader/component/attribute/Setter.hpp>

namespace cenpy::mock::graphic::pipeline::opengl::component::attribute
{
    template <typename U>
    struct mockSetter : cenpy::graphic::pipeline::component::attribute::baseSetter<graphic::api::MockOpenGL, U>
    {
    };

    /**
     * @brief Specialization for GLfloat with corresponding setter
     */
    template <>
    struct mockSetter<float> : std::true_type
    {
        static constexpr auto set =
            [](const cenpy::mock::graphic::opengl::context::MockAttributeContext<graphic::api::MockOpenGL> &attribute)
        { glAttribute1f(1, 3.14f); };
    };

}