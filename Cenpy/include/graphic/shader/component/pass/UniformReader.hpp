#pragma once

#include <memory>
#include <graphic/Api.hpp>

namespace cenpy::graphic::shader
{
    template <typename API>
    class Uniform;

    namespace component::pass
    {
        /**
         * @interface IPassUniformReader
         * @brief Interface for reading uniforms in a shader pass.
         *
         * This interface provides a method for reading uniform variables from a shader program.
         * Implementations should handle the specifics of extracting uniform details such as
         * type, name, and location within the context of a particular graphics API.
         */
        template <typename API>
        class IPassUniformReader
        {
        public:
            virtual ~IPassUniformReader() = default;

            /**
             * @brief Read uniforms from the shader program.
             * @param context Shared pointer to PassContext containing details of the shader pass.
             * @param uniforms Reference to an unordered_map to store the extracted uniforms.
             *
             * This method should query the shader program for its uniform variables and store
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
         * This class specializes in reading uniform variables from an OpenGL shader program.
         * It extracts the details of each uniform and populates them into the provided map.
         */
        class OpenGLPassUniformReader : public graphic::shader::component::pass::IPassUniformReader<graphic::api::OpenGL>
        {
        public:
            void readUniforms(std::shared_ptr<typename graphic::api::OpenGL::PassContext> openglContext) override;
        };
    }
}