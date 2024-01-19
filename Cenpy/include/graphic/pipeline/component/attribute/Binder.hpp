// file: Binder

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
        class IBinder
        {
        public:
            virtual ~IBinder() = default;

            virtual void bindAttribute(std::shared_ptr<typename graphic::api::OpenGL::AttributeContext> attribute) = 0;
        };
    }

    namespace opengl::component::attribute
    {
        class OpenGLBinder : public graphic::pipeline::component::attribute::IBinder<graphic::api::OpenGL>
        {
        public:
            void bindAttribute(std::shared_ptr<typename graphic::api::OpenGL::AttributeContext> attribute) override
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
}