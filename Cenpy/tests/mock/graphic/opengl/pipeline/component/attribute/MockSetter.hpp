// file: Setter

#pragma once

#include <memory>
#include <gmock/gmock.h>
#include <graphic/MockApi.hpp>
#include <graphic/opengl/profile/Attribute.hpp>

namespace cenpy::mock::graphic::opengl::pipeline::component::attribute
{
    template <typename A>
    class MockSetter
    {
    public:
        static std::shared_ptr<MockSetter> instance()
        {
            static auto instance = std::make_shared<MockSetter>();
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