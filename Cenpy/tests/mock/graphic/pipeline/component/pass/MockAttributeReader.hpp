#pragma once

#include <memory>
#include <graphic/MockApi.hpp>
#include <gmock/gmock.h>
#include <graphic/pipeline/component/pass/AttributeReader.hpp>

namespace cenpy::mock::graphic::pipeline::opengl::component::pass
{
    template <typename API>
    class MockAttributeReader : public cenpy::graphic::pipeline::component::pass::IPassAttributeReader<API>
    {
    public:
        MOCK_METHOD(void, readAttributes, (std::shared_ptr<typename API::PassContext> openglContext), (override));
    };
}
