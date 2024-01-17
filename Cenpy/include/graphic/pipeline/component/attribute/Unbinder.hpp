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
        template <typename API, typename A>
        class IAttributeUnbinder
        {
        public:
            virtual ~IAttributeUnbinder() = default;

            virtual void unbindAttribute(const typename API::AttributeContext &attribute) = 0;
        };
    }

    namespace opengl::component::attribute
    {
        template <typename A>
        class OpenGLAttributeUnbinder : public graphic::pipeline::component::attribute::baseUnbinder<graphic::api::OpenGL, A>
        {
        public:
            void unbindAttribute(const typename graphic::api::OpenGL::AttributeContext &attribute) override
            {
                if (!attribute)
                {
                    throw cenpy::common::exception::TraceableException<std::runtime_error>(std::format("ERROR::ATTRIBUTE::SET::NON_OPENGL_CONTEXT"));
                }
                std::shared_ptr<A> attrValue = attribute.getValue<A>();
                if (attribute.getBufferId() == -1)
                {
                    throw cenpy::common::exception::TraceableException<std::runtime_error>(std::format("ERROR::ATTRIBUTE::SET::BUFFER_NOT_SET"));
                }
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }
        };
    }
}