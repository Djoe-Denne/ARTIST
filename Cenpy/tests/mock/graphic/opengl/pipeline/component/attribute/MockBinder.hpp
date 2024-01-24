// file: Binder

#pragma once

#include <memory>
#include <gmock/gmock.h>
#include <graphic/MockApi.hpp>
#include <graphic/opengl/profile/Attribute.hpp>

namespace cenpy::mock::graphic::opengl::pipeline::component::attribute
{
    template <auto PROFILE>
    class MockBinder
    {
    public:
        static std::shared_ptr<MockBinder<PROFILE>> instance()
        {
            static auto instance = std::make_shared<MockBinder<PROFILE>>();
            return instance;
        }

        static void reset()
        {
            ::testing::Mock::VerifyAndClearExpectations(instance().get());
        }

        static void on(std::shared_ptr<graphic::api::MockOpenGL::AttributeContext> openglContext)
        {
            instance()->mockOn(openglContext);
        }

        MOCK_METHOD(void, mockOn, (std::shared_ptr<graphic::api::MockOpenGL::AttributeContext> attribute), ());
    };

}