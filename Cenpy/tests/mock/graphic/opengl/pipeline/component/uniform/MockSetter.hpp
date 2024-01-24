#pragma once

#include <GL/glew.h>
#include <memory>
#include <gmock/gmock.h>
#include <graphic/MockApi.hpp>

namespace cenpy::mock::graphic::opengl
{
    namespace context
    {

        class MockUniformContext;
    }
    namespace pipeline::component::uniform
    {

        template <typename U>
        struct MockSetter
        {
            static constexpr GLenum glType = GL_INVALID_ENUM;
        };
        /**
         * @brief Specialization for GLfloat with corresponding setter
         */
        template <>
        struct MockSetter<GLfloat>
        {
            static void on(std::shared_ptr<graphic::api::MockOpenGL::UniformContext> uniform)
            {
                glUniform1f(1, 3.14f);
            }

            static constexpr GLenum glType = GL_FLOAT;
        };

        /**
         * @brief Specialization for GLfloat with corresponding setter
         */
        template <>
        struct MockSetter<GLint>
        {
            static void on(std::shared_ptr<graphic::api::MockOpenGL::UniformContext> uniform)
            {
                glUniform1i(1, 1);
            }

            static constexpr GLenum glType = GL_INT;
        };

    }
}
