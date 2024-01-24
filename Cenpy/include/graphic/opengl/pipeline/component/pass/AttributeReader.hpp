#pragma once

#include <GL/glew.h>
#include <memory>
#include <graphic/Api.hpp>
#include <graphic/opengl/context/PassContext.hpp>
#include <common/exception/TraceableException.hpp>
#include <graphic/pipeline/Attribute.hpp>
#include <graphic/opengl/profile/Pass.hpp>
#include <graphic/opengl/profile/Attribute.hpp>

namespace cenpy::graphic::opengl::pipeline::component::pass
{
    /**
     * @class OpenGLAttributeReader
     *
     * This class specializes in reading uniform variables from an OpenGL shader pipeline.
     * It extracts the details of each uniform and populates them into the provided map.
     */
    template <auto PROFILE>
    class OpenGLPassAttributeReader
    {
    };

    template <>
    class OpenGLPassAttributeReader<graphic::opengl::profile::Pass::Classic>
    {
    public:
        static void on(std::shared_ptr<typename graphic::api::OpenGL::PassContext> openglContext)
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
                // Known limitation of OpenGL: Attributes profile are driven by Pass profile
                auto attribute = std::make_shared<graphic::pipeline::Attribute<graphic::api::OpenGL, graphic::opengl::profile::Attribute::Classic>>(attributeContext);
                openglContext->addAttribute(std::string(attributeName), attribute);
            }
        }
    };
}
