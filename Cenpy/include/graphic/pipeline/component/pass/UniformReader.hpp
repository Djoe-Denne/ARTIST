#pragma once

#include <GL/glew.h>
#include <memory>
#include <graphic/Api.hpp>
#include <graphic/context/PassContext.hpp>
#include <common/exception/TraceableException.hpp>
#include <graphic/pipeline/Uniform.hpp>

namespace cenpy::graphic::pipeline
{
    template <typename API>
    class Uniform;

    namespace component::pass
    {
        /**
         * @interface IPassUniformReader
         * @brief Interface for reading uniforms in a shader pass.
         *
         * This interface provides a method for reading uniform variables from a shader pipeline.
         * Implementations should handle the specifics of extracting uniform details such as
         * type, name, and location within the context of a particular graphics API.
         */
        template <typename API>
        class IPassUniformReader
        {
        public:
            virtual ~IPassUniformReader() = default;

            /**
             * @brief Read uniforms from the shader pipeline.
             * @param context Shared pointer to PassContext containing details of the shader pass.
             * @param uniforms Reference to an unordered_map to store the extracted uniforms.
             *
             * This method should query the shader pipeline for its uniform variables and store
             * the relevant details (like name, type, and location) in the provided map.
             */
            virtual void readUniforms(std::shared_ptr<typename API::PassContext> context) = 0;
        };
    }

    namespace opengl::component::pass
    {
        /**
         * @class OpenGLUniformReader
         * @brief OpenGL implementation of the IPassUniformReader interface.
         *
         * This class specializes in reading uniform variables from an OpenGL shader pipeline.
         * It extracts the details of each uniform and populates them into the provided map.
         */
        class OpenGLPassUniformReader : public graphic::pipeline::component::pass::IPassUniformReader<graphic::api::OpenGL>
        {
        public:
            void readUniforms(std::shared_ptr<typename graphic::api::OpenGL::PassContext> openglContext) override
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

                GLint numUniforms = 0;
                glGetProgramiv(passID, GL_ACTIVE_UNIFORMS, &numUniforms);

                for (GLint i = 0; i < numUniforms; ++i)
                {
                    char uniformName[256];
                    GLsizei nameLength = 0;
                    GLsizei size = 0;
                    GLenum type = 0;
                    glGetActiveUniform(passID, i, sizeof(uniformName), &nameLength, &size, &type, uniformName);

                    GLuint location = glGetUniformLocation(passID, uniformName);

                    // Create a Uniform object and store it in the map
                    auto uniformContext = std::make_shared<graphic::api::OpenGL::UniformContext>();
                    uniformContext->setUniformID(location);
                    uniformContext->setGLType(type);
                    auto uniform = std::make_shared<graphic::pipeline::Uniform<graphic::api::OpenGL>>(uniformContext);
                    openglContext->addUniform(std::string(uniformName), uniform);
                }
            }
        };
    }
}