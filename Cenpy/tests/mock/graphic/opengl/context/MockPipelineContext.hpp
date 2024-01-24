// PipelineContext.hpp

#pragma once

#include <graphic/MockApi.hpp>
#include <graphic/opengl/context/PipelineContext.hpp>
#include <graphic/opengl/pipeline/component/pipeline/MockUser.hpp>
#include <graphic/opengl/pipeline/component/pipeline/MockResetter.hpp>

namespace cenpy::mock::graphic::opengl::context
{

    class MockPipelineContext : public cenpy::graphic::context::PipelineContext<graphic::api::MockOpenGL>
    {
    public:
        template <auto PROFILE>
        using User = opengl::pipeline::component::pipeline::MockUser<PROFILE>;
        template <auto PROFILE>
        using Resetter = opengl::pipeline::component::pipeline::MockResetter<PROFILE>;
    };
}
