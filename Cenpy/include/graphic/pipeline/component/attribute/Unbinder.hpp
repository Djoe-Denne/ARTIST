// file: Unbinder

#pragma once

#include <GL/glew.h>
#include <string>
#include <memory>
#include <any>
#include <graphic/context/AttributeContext.hpp>
#include <graphic/Api.hpp>

namespace cenpy::graphic::pipeline
{
    namespace component::attribute
    {
        template <typename API>
        class IUnbinder
        {
        public:
            virtual ~IUnbinder() = default;

            virtual void unbindAttribute(std::shared_ptr<typename graphic::api::OpenGL::AttributeContext> attribute) = 0;
        };
    }

    namespace opengl::component::attribute
    {
        class OpenGLUnbinder : public graphic::pipeline::component::attribute::IUnbinder<graphic::api::OpenGL>
        {
        public:
            void unbindAttribute(std::shared_ptr<typename graphic::api::OpenGL::AttributeContext> attribute) override
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
}