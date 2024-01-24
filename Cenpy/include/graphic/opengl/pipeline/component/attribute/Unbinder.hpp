// file: Unbinder

#pragma once

#include <GL/glew.h>
#include <string>
#include <memory>
#include <any>
#include <graphic/opengl/context/AttributeContext.hpp>
#include <graphic/Api.hpp>
#include <graphic/opengl/profile/Attribute.hpp>

namespace cenpy::graphic::opengl::pipeline::component::attribute
{
    template <auto PROFILE>
    class OpenGLUnbinder
    {
    };

    template <>
    class OpenGLUnbinder<graphic::opengl::profile::Attribute::Classic>
    {
    public:
        static void on(std::shared_ptr<typename graphic::api::OpenGL::AttributeContext> attribute)
        {
            if (!attribute)
            {
                throw cenpy::common::exception::TraceableException<std::runtime_error>(std::format("ERROR::ATTRIBUTE::SET::NON_OPENGL_CONTEXT"));
            }
            if (attribute->getBufferID() == 0)
            {
                throw cenpy::common::exception::TraceableException<std::runtime_error>(std::format("ERROR::ATTRIBUTE::SET::BUFFER_NOT_SET"));
            }
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    };
}
