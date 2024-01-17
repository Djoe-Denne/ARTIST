// AttributeContext.hpp

#pragma once
#include <GL/glew.h>
#include <string>
#include <format>
#include <any>
#include <memory>
#include <optional>
#include <common/exception/TraceableException.hpp>

namespace cenpy::graphic
{
    namespace pipeline::opengl::component::attribute
    {
        template <typename T>
        class OpenGLAttributeSetter<T>;
    }
    namespace context
    {
        template <typename API>
        class AttributeContext
        {
        public:
            virtual ~AttributeContext() = default;

            template <typename T>
            std::shared_ptr<T> getValue() const
            {
                if (m_value.has_value())
                {
                    try
                    {
                        std::any_cast<T>(&m_value);
                    }
                    catch (const std::bad_any_cast &)
                    {
                        throw cenpy::common::exception::TraceableException<std::runtime_error>(std::format("ERROR::UNIFORM::SET::TYPE_MISMATCH: The type of the value ({}) does not match the type of the attribute variable ({})", typeid(T).name(), typeid(m_value).name()));
                    }
                }
                return *std::any_cast<T>(&m_value);
            }

            template <typename T>
            void setValue(std::shared_ptr<T> value)
            {
                try
                {
                    std::any_cast<T>(&m_value);
                }
                catch (const std::bad_any_cast &)
                {
                    throw cenpy::common::exception::TraceableException<std::runtime_error>(std::format("ERROR::UNIFORM::SET::TYPE_MISMATCH: The type of the value ({}) does not match the type of the attribute variable ({})", typeid(value).name(), typeid(m_value).name()));
                }
                m_value = value;
            }

        private:
            std::any m_value; ///< The value of the attribute variable.
        };
    }

    namespace opengl::context
    {
        class OpenGLAttributeContext : public graphic::context::AttributeContext<graphic::api::OpenGL>
        {
        public:
            template <typename T>
            using Setter = pipeline::opengl::component::attribute::OpenGLAttributeSetter<T>;

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
                return m_bufferId.or_else(-1);
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

            void setDrawingUsage(GLenum drawingUsage)
            {
                if(drawingUsage != GL_STREAM_DRAW && drawingUsage != GL_STATIC_DRAW && drawingUsage != GL_DYNAMIC_DRAW)
                {
                    throw cenpy::common::exception::TraceableException<std::runtime_error>(std::format("ERROR::ATTRIBUTE::SET::DRAWING_MODE_NOT_SUPPORTED: The drawing mode ({}) is not supported", drawingUsage));
                }
                m_drawingUsage = drawingUsage;
            }

            GLenum getDrawingUsage() const
            {
                return m_drawingUsage;
            }

        private:
            GLuint m_attributeId;             ///< OpenGL attribute ID
            GLuint m_size;                    ///< The size of the attribute variable.
            GLenum m_type;                    ///< The type of the attribute variable.
            std::optional<GLuint> m_bufferId; ///< OpenGL VBO buffer ID
            GLenum m_drawingUsage;             ///< The drawing mode of the attribute variable.
        };
    }
}