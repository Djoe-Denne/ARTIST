#pragma once

#include <memory>
#include <gmock/gmock.h>
#include <graphic/MockApi.hpp>
#include <graphic/opengl/profile/Pipeline.hpp>

namespace cenpy::mock::graphic::opengl::pipeline::component::pipeline
{
    template <auto PROFILE>
    class MockResetter
    {
    public:
        static std::shared_ptr<MockResetter<PROFILE>> instance()
        {
            static auto instance = std::make_shared<MockResetter<PROFILE>>();
            return instance;
        }

        static void reset()
        {
            ::testing::Mock::VerifyAndClearExpectations(instance().get());
        }

        static void on(std::shared_ptr<graphic::api::MockOpenGL::PipelineContext> openglContext)
        {
            instance()->mockOn(openglContext);
        }

        MOCK_METHOD(void, mockOn, (std::shared_ptr<graphic::api::MockOpenGL::PipelineContext> context), ());
    };
}