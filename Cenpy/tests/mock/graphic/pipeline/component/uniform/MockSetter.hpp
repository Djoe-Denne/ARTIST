#pragma once

#include <gmock/gmock.h>
#include <graphic/MockApi.hpp>
#include <graphic/pipeline/component/uniform/Setter.hpp>
#include <graphic/context/MockUniformContext.hpp>

namespace cenpy::mock::graphic
{
    namespace opengl::context
    {
        template <typename API>
        class MockUniformContext;
    }
    namespace pipeline::opengl::component::uniform
    {

        template <typename U>
        struct mockSetter : cenpy::graphic::pipeline::component::uniform::baseSetter<graphic::api::MockOpenGL, U>
        {
            static constexpr GLenum type = GL_INVALID_ENUM;
        };

        /**
         * @brief Specialization for GLfloat with corresponding setter
         */
        template <>
        struct mockSetter<float> : std::true_type
        {
            static constexpr auto set =
                [](const cenpy::mock::graphic::opengl::context::MockUniformContext<graphic::api::MockOpenGL> &uniform)
            { glUniform1f(1, 3.14f); };
        };
    }
}
