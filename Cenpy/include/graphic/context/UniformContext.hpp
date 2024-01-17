// UniformContext.hpp

#pragma once
#include <GL/glew.h>
#include <string>
#include <format>
#include <any>
#include <stdexcept>
#include <EnumClass.hpp>
#include <common/exception/TraceableException.hpp>

namespace cenpy::graphic
{

    namespace pipeline::opengl::component::uniform
    {
        template <typename U>
        class OpenGLUniformSetter;
    }
    namespace context
    {
        template <typename API>
        class UniformContext
        {
        public:
            virtual ~UniformContext() = default;

            template <typename T>
            const T &getValue() const
            {
                if (m_value.has_value())
                {
                    try
                    {
                        std::any_cast<T>(&m_value);
                    }
                    catch (const std::bad_any_cast &)
                    {
                        throw cenpy::common::exception::TraceableException<std::runtime_error>(std::format("ERROR::UNIFORM::SET::TYPE_MISMATCH: The type of the value ({}) does not match the type of the uniform variable ({})", typeid(T).name(), typeid(m_value).name()));
                    }
                }
                return *std::any_cast<T>(&m_value);
            }

            template <typename T>
            void setValue(const T &value)
            {
                try
                {
                    std::any_cast<T>(&m_value);
                }
                catch (const std::bad_any_cast &)
                {
                    throw cenpy::common::exception::TraceableException<std::runtime_error>(std::format("ERROR::UNIFORM::SET::TYPE_MISMATCH: The type of the value ({}) does not match the type of the uniform variable ({})", typeid(value).name(), typeid(m_value).name()));
                }
                m_value = value;
            }

        private:
            std::any m_value; ///< The value of the uniform variable.
        };
    }

    namespace opengl::context
    {
        class OpenGLUniformContext : public graphic::context::UniformContext<graphic::api::OpenGL>
        {
        public:
            template <typename T>
            using Setter = pipeline::opengl::component::uniform::OpenGLUniformSetter<T>;

            void setUniformID(GLuint uniformId)
            {
                m_uniformId = uniformId;
            }

            GLuint getUniformID() const
            {
                return m_uniformId;
            }

            void setGLType(GLenum type)
            {
                m_type = type;
            }

            GLenum getGLType() const
            {
                return m_type;
            }

            void setSize(GLuint size)
            {
                m_size = size;
            }

            GLuint getGLSize() const
            {
                return m_size;
            }

        private:
            GLuint m_uniformId; ///< OpenGL shader ID
            GLuint m_size;      ///< The size of the uniform variable.
            GLenum m_type;      ///< The type of the uniform variable.
        };
    }
}