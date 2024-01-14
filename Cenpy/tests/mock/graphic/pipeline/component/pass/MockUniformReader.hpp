#pragma once

#include <memory>
#include <graphic/MockApi.hpp>
#include <gmock/gmock.h>
#include <graphic/pipeline/component/pass/UniformReader.hpp>

namespace cenpy::mock::graphic::pipeline::opengl::component::pass
{
    template <typename API>
    class MockUniformReader : public cenpy::graphic::pipeline::component::pass::IPassUniformReader<API>
    {
    public:
        MOCK_METHOD(void, readUniforms, (std::shared_ptr<typename API::PassContext> openglContext), (override));
    };
}
