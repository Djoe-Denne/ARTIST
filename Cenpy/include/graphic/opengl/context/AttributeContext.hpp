// AttributeContext.hpp

#pragma once
#include <GL/glew.h>
#include <graphic/Api.hpp>
#include <graphic/context/AttributeContext.hpp>

namespace cenpy::graphic
{
    namespace opengl::pipeline::component::attribute
    {
        template <auto PROFILE>
        class OpenGLBinder;
        template <typename A>
        class OpenGLSetter;
        template <auto PROFILE>
        class OpenGLUnbinder;
    }

    namespace opengl::context
    {
        class OpenGLAttributeContext : public graphic::context::AttributeContext<graphic::api::OpenGL>
        {
        public:
            template <auto PROFILE>
            using Binder = opengl::pipeline::component::attribute::OpenGLBinder<PROFILE>;
            template <typename A>
            using Setter = opengl::pipeline::component::attribute::OpenGLSetter<A>;
            template <auto PROFILE>
            using Unbinder = opengl::pipeline::component::attribute::OpenGLUnbinder<PROFILE>;

            void setAttributeID(GLuint attributeId)
            {
                m_attributeId = attributeId;
            }

            GLuint getAttributeID() const
            {
                return m_attributeId;
            }

            GLuint getBufferID() const
            {
                return m_bufferId;
            }

            void setBufferID(GLuint bufferId)
            {
                m_bufferId = bufferId;
            }

            void setSize(GLuint size)
            {
                m_size = size;
            }

            GLuint getGLSize() const
            {
                return m_size;
            }

            GLenum getGLType() const
            {
                return m_type;
            }

            void setGLType(GLenum type)
            {
                m_type = type;
            }

            void setGLUsage(GLenum usage)
            {
                if (usage != GL_STREAM_DRAW && usage != GL_STATIC_DRAW && usage != GL_DYNAMIC_DRAW)
                {
                    throw cenpy::common::exception::TraceableException<std::runtime_error>(std::format("ERROR::ATTRIBUTE::SET::DRAWING_MODE_NOT_SUPPORTED: The drawing mode ({}) is not supported", usage));
                }
                m_usage = usage;
            }

            GLenum getGLUsage() const
            {
                return m_usage;
            }

        private:
            GLuint m_attributeId; ///< OpenGL attribute ID
            GLuint m_size;        ///< The size of the attribute variable.
            GLenum m_type;        ///< The type of the attribute variable.
            GLuint m_bufferId;    ///< OpenGL VBO buffer ID
            GLenum m_usage;       ///< The drawing mode of the attribute variable.
        };
    }
}