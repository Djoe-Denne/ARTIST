// file: Reader.hpp

#pragma once

#include <memory>
#include <gmock/gmock.h>
#include <graphic/MockApi.hpp>
#include <graphic/opengl/profile/Shader.hpp>

namespace cenpy::mock::graphic::opengl::pipeline::component::shader
{
    template <auto PROFILE>
    class MockReader
    {
    public:
        static std::shared_ptr<MockReader<PROFILE>> instance()
        {
            static auto instance = std::make_shared<MockReader<PROFILE>>();
            return instance;
        }

        static void reset()
        {
            ::testing::Mock::VerifyAndClearExpectations(instance().get());
        }

        static void on(std::shared_ptr<graphic::api::MockOpenGL::ShaderContext> openglContext)
        {
            instance()->mockOn(openglContext);
        }

        MOCK_METHOD(void, mockOn, (std::shared_ptr<graphic::api::MockOpenGL::ShaderContext>), ());
    };
}