// file: Setter

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
        class IAttributeSetter
        {
        public:
            virtual ~IAttributeSetter() = default;

            virtual void setAttribute(const typename API::AttributeContext &attribute) = 0;
        };
    }

    namespace opengl::component::attribute
    {
        template <typename A>
        class OpenGLAttributeSetter : public graphic::pipeline::component::attribute::baseSetter<graphic::api::OpenGL, A>
        {
        public:
            void setAttribute(const typename graphic::api::OpenGL::AttributeContext &attribute) override
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
                glBufferData(GL_ARRAY_BUFFER, sizeof(attrValue.get()), attrValue.get(), attribute.getGLUsage());
                glVertexAttribPointer(attribute.getAttributeID(), attribute->getGLSize(), attribute.getGLType(), GL_FALSE, sizeof(attrValue.get()), (void *)0);
            }
        };
    }
}