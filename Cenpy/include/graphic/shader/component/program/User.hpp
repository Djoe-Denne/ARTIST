#pragma once

#include <memory>
#include <graphic/Api.hpp>
#include <graphic/context/ProgramContext.hpp>

namespace cenpy::graphic::shader
{
    namespace component::program
    {
        template <typename API>
        class IProgramUser
        {
        public:
            virtual ~IProgramUser() = default;

            virtual void useProgram(std::shared_ptr<typename API::ProgramContext> context)
            {
                context->getPass(context->getCurrentPass())->use();
            }
        };
    }

    namespace opengl::component::program
    {
        class OpenGLProgramUser : public graphic::shader::component::program::IProgramUser<graphic::api::OpenGL>
        {
        };
    }
}