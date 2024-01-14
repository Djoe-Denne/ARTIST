#pragma once

#include <memory>
#include <graphic/MockApi.hpp>
#include <graphic/context/PipelineContext.hpp>
#include <gmock/gmock.h>
#include <graphic/pipeline/component/pipeline/User.hpp>

namespace cenpy::mock::graphic::pipeline::opengl::component::pipeline
{
    template <typename API>
    class MockUser : public cenpy::graphic::pipeline::component::pipeline::IPipelineUser<API>
    {
    public:
        MOCK_METHOD(void, usePipeline, (std::shared_ptr<typename API::PipelineContext> context), (override));
    };
}
