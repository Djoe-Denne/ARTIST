#pragma once

#include <memory>
#include <graphic/Api.hpp>
#include <GL/glew.h>
#include <iostream>
#include <graphic/context/PassContext.hpp>
#include <graphic/context/ShaderContext.hpp>
#include <common/exception/TraceableException.hpp>

namespace cenpy::graphic::pipeline
{
    namespace pipeline = cenpy::graphic::pipeline;
    namespace component::pass
    {
        /**
         * @interface IPassFreer
         * @brief Interface for freeing resources of shader passes.
         *
         * This interface defines a method for freeing resources associated with a shader pass,
         * such as detaching shaders and deleting pipelines.
         */
        template <typename API>
        class IPassFreer
        {
        public:
            virtual ~IPassFreer() = default;

            /**
             * @brief Free resources and state for a shader pass.
             * @param context PassContext for managing pass-specific details.
             *
             * Implementations of this method should handle the cleanup and resource release
             * for a shader pass.
             */
            virtual void freePass(std::shared_ptr<typename API::PassContext> context) = 0;
        };
    }

    namespace opengl::component::pass
    {
        /**
         * @class OpenGLPassFreer
         * @brief OpenGL implementation of IPassFreer.
         *
         * Handles the freeing of resources for an OpenGL shader pass, including detaching shaders
         * and deleting the OpenGL pipeline.
         */
        class OpenGLPassFreer : public graphic::pipeline::component::pass::IPassFreer<graphic::api::OpenGL>
        {
        public:
            void freePass(std::shared_ptr<typename graphic::api::OpenGL::PassContext> openglContext) override
            {
                if (!openglContext)
                {
                    throw common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::NON_OPENGL_CONTEXT");
                }

                GLuint passID = openglContext->getPassID();
                if (passID != 0)
                {
                    // Optionally detach shaders before deleting the pipeline
                    for (const auto &shader : openglContext->getShaders())
                    {
                        if (auto oglShaderContext = shader->getContext())
                        {
                            glDetachShader(passID, oglShaderContext->getShaderID());
                        }
                    }

                    // Delete the OpenGL pipeline
                    glDeleteProgram(passID);
                    openglContext->setPassID(0); // Reset the pipeline ID in the context
                }
            }
        };
    }
}
