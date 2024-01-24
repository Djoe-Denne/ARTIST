// PipelineContext.hpp

#pragma once

#include <graphic/Api.hpp>
#include <graphic/context/PipelineContext.hpp>

namespace cenpy::graphic
{
    namespace opengl::pipeline::component::pipeline
    {
        template <auto PROFILE>
        class OpenGLPipelineUser;
        template <auto PROFILE>
        class OpenGLPipelineResetter;
    }
    namespace opengl::context
    {
        class OpenGLPipelineContext : public graphic::context::PipelineContext<graphic::api::OpenGL>
        {
        public:
            template <auto PROFILE>
            using User = opengl::pipeline::component::pipeline::OpenGLPipelineUser<PROFILE>;
            template <auto PROFILE>
            using Resetter = opengl::pipeline::component::pipeline::OpenGLPipelineResetter<PROFILE>;
        };
    }
}