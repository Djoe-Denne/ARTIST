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
        template <typename API, typename A>
        class IAttributeBinder
        {
        public:
            virtual ~IAttributeBinder() = default;

            virtual void bindAttribute(const typename API::AttributeContext &attribute) = 0;
        };
    }

    namespace opengl::component::attribute
    {
        template <typename A>
        class OpenGLAttributeBinder : public graphic::pipeline::component::attribute::baseBinder<graphic::api::OpenGL, A>
        {
        public:
            void bindAttribute(const typename graphic::api::OpenGL::AttributeContext &attribute) override
            {
                if (!attribute)
                {
                    throw cenpy::common::exception::TraceableException<std::runtime_error>(std::format("ERROR::ATTRIBUTE::SET::NON_OPENGL_CONTEXT"));
                }
                std::shared_ptr<A> attrValue = attribute.getValue<A>();
                if (attribute.getBufferId() == -1)
                {
                    unsigned int VBO;
                    glGenBuffers(1, &VBO);
                    attribute.setBufferId(VBO);
                }
                glBindBuffer(GL_ARRAY_BUFFER, attribute.getBufferId());
            }
        };
    }
}