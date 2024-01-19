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
        struct baseSetter
        {
            static const auto set = [](std::shared_ptr<typename graphic::api::OpenGL::AttributeContext> attribute)
            { static_assert(false, "Unsupported uniform type"); };
        };
    }

    namespace opengl::component::attribute
    {
        template <typename A>
        struct OpenGLSetter : graphic::pipeline::component::attribute::baseSetter<graphic::api::OpenGL, A>
        {
        };

        template <typename A>
            requires std::is_pointer_v<A>
        struct OpenGLSetter<A> : std::true_type
        {
            static constexpr auto set = [](std::shared_ptr<typename graphic::api::OpenGL::AttributeContext> attribute) -> void
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
            };
        };
    }
}