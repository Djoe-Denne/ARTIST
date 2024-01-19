#pragma once

#include <GL/glew.h>
#include <memory>
#include <graphic/Api.hpp>
#include <graphic/context/PassContext.hpp>
#include <common/exception/TraceableException.hpp>
#include <graphic/pipeline/Attribute.hpp>

namespace cenpy::graphic::pipeline
{
    template <typename API>
    class Attribute;

    namespace component::pass
    {
        /**
         * @interface IPassAttributeReader
         * @brief Interface for reading uniforms in a shader pass.
         *
         * This interface provides a method for reading uniform variables from a shader pipeline.
         * Implementations should handle the specifics of extracting uniform details such as
         * type, name, and location within the context of a particular graphics API.
         */
        template <typename API>
        class IPassAttributeReader
        {
        public:
            virtual ~IPassAttributeReader() = default;

            /**
             * @brief Read uniforms from the shader pipeline.
             * @param context Shared pointer to PassContext containing details of the shader pass.
             * @param uniforms Reference to an unordered_map to store the extracted uniforms.
             *
             * This method should query the shader pipeline for its uniform variables and store
             * the relevant details (like name, type, and location) in the provided map.
             */
            virtual void readAttributes(std::shared_ptr<typename API::PassContext> context) = 0;
        };
    }

    namespace opengl::component::pass
    {
        /**
         * @class OpenGLAttributeReader
         * @brief OpenGL implementation of the IPassAttributeReader interface.
         *
         * This class specializes in reading uniform variables from an OpenGL shader pipeline.
         * It extracts the details of each uniform and populates them into the provided map.
         */
        class OpenGLPassAttributeReader : public graphic::pipeline::component::pass::IPassAttributeReader<graphic::api::OpenGL>
        {
        public:
            void readAttributes(std::shared_ptr<typename graphic::api::OpenGL::PassContext> openglContext) override
            {
                if (!openglContext)
                {
                    throw common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::NON_OPENGL_CONTEXT");
                }

                GLuint passID = openglContext->getPassID();
                if (passID == 0)
                {
                    throw common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::INVALID_PROGRAM_ID");
                }

                GLint numAttributes = 0;
                glGetProgramiv(passID, GL_ACTIVE_ATTRIBUTES, &numAttributes);

                for (GLint i = 0; i < numAttributes; ++i)
                {
                    char attributeName[256];
                    GLsizei nameLength = 0;
                    GLint size = 0;
                    GLenum type = 0;
                    glGetActiveAttrib(passID, i, sizeof(attributeName), &nameLength, &size, &type, attributeName);

                    GLuint location = glGetAttribLocation(passID, attributeName);

                    // Create an Attribute object and store it in the context
                    auto attributeContext = std::make_shared<graphic::api::OpenGL::AttributeContext>();
                    // Set necessary attribute context details
                    auto attribute = std::make_shared<graphic::pipeline::Attribute<graphic::api::OpenGL>>(attributeContext);
                    openglContext->addAttribute(std::string(attributeName), attribute);
                }
            }
        };
    }
}