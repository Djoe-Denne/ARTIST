// file: Setter

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
    template <typename A>
    class OpenGLSetter
    {
    public:
        static void on(std::shared_ptr<typename graphic::api::OpenGL::AttributeContext> attribute)
        {
            if (!attribute)
            {
                throw cenpy::common::exception::TraceableException<std::runtime_error>(std::format("ERROR::ATTRIBUTE::SET::NON_OPENGL_CONTEXT"));
            }
            std::shared_ptr<A> attrValue = attribute->getValue<A>();
            if (attribute->getBufferID() == 0)
            {
                throw cenpy::common::exception::TraceableException<std::runtime_error>(std::format("ERROR::ATTRIBUTE::SET::BUFFER_NOT_SET"));
            }
            glBufferData(GL_ARRAY_BUFFER, sizeof(attrValue.get()), attrValue.get(), attribute->getGLUsage());
            glVertexAttribPointer(attribute->getAttributeID(), attribute->getGLSize(), attribute->getGLType(), GL_FALSE, sizeof(attrValue.get()), (void *)0);
        }
    };
}
