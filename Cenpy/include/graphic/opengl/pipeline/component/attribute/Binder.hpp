// file: Binder

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
    class OpenGLBinder
    {
    };

    template <>
    class OpenGLBinder<graphic::opengl::profile::Attribute::Classic>
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
                unsigned int VBO;
                glGenBuffers(1, &VBO);
                attribute->setBufferID(VBO);
            }
            glBindBuffer(GL_ARRAY_BUFFER, attribute->getBufferID());
        }
    };
}
