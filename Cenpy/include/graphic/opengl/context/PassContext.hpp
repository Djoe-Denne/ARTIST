// PassContext.hpp

#pragma once

#include <GL/glew.h>
#include <graphic/Api.hpp>
#include <graphic/context/PassContext.hpp>

namespace cenpy::graphic
{
    namespace opengl::pipeline::component::pass
    {
        template <auto PROFILE>
        class OpenGLLoader;
        template <auto PROFILE>
        class OpenGLPassFreer;
        template <auto PROFILE>
        class OpenGLShaderAttacher;
        template <auto PROFILE>
        class OpenGLPassUniformReader;
        template <auto PROFILE>
        class OpenGLPassAttributeReader;
        template <auto PROFILE>
        class OpenGLPassUser;
    }

    namespace opengl::context
    {
        /**
         * @class OpenGLPassContext
         * @brief OpenGL-specific implementation of PassContext.
         *
         * OpenGLPassContext manages the details and state of a shader pass for OpenGL.
         * This includes handling of OpenGL-specific data such as pipeline IDs, as well
         * as the list of shaders and uniform variables.
         */
        class OpenGLPassContext : public graphic::context::PassContext<graphic::api::OpenGL>
        {
        public:
            template <auto PROFILE>
            using Loader = opengl::pipeline::component::pass::OpenGLLoader<PROFILE>;
            template <auto PROFILE>
            using Freer = opengl::pipeline::component::pass::OpenGLPassFreer<PROFILE>;
            template <auto PROFILE>
            using ShaderAttacher = opengl::pipeline::component::pass::OpenGLShaderAttacher<PROFILE>;
            template <auto PROFILE>
            using UniformReader = opengl::pipeline::component::pass::OpenGLPassUniformReader<PROFILE>;
            template <auto PROFILE>
            using AttributeReader = opengl::pipeline::component::pass::OpenGLPassAttributeReader<PROFILE>;
            template <auto PROFILE>
            using User = opengl::pipeline::component::pass::OpenGLPassUser<PROFILE>;

            void setPassID(GLuint passID)
            {
                m_passID = passID;
            }

            GLuint getPassID() const
            {
                return m_passID;
            }

        private:
            GLuint m_passID; // OpenGL pipeline ID
        };
    }
}