// PipelineContext.hpp

#pragma once

#include <graphic/MockApi.hpp>
#include <graphic/context/PipelineContext.hpp>
#include <graphic/pipeline/component/pipeline/MockUser.hpp>
#include <graphic/pipeline/component/pipeline/MockResetter.hpp>

namespace cenpy::mock::graphic::opengl::context
{
    template <typename API>
    class MockPipelineContext : public cenpy::graphic::context::PipelineContext<API>
    {
    public:
        using User = pipeline::opengl::component::pipeline::MockUser<API>;
        using Resetter = pipeline::opengl::component::pipeline::MockResetter<API>;
    };
}
