#pragma once

#include <memory>
#include <graphic/MockApi.hpp>
#include <graphic/context/PipelineContext.hpp>
#include <gmock/gmock.h>
#include <graphic/pipeline/component/pipeline/Resetter.hpp>

namespace cenpy::mock::graphic::pipeline::opengl::component::pipeline
{
    template <typename API>
    class MockResetter : public cenpy::graphic::pipeline::component::pipeline::IPipelineResetter<API>
    {
    public:
        MOCK_METHOD(void, resetPipeline, (std::shared_ptr<typename API::PipelineContext> context), (override));
    };
}
