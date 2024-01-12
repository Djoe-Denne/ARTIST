#pragma once

#include <memory>
#include <graphic/MockApi.hpp>
#include <gmock/gmock.h>
#include <graphic/shader/component/pass/UniformReader.hpp>

namespace cenpy::mock::graphic::shader::opengl::component::pass
{
    template <typename API>
    class MockUniformReader : public cenpy::graphic::shader::component::pass::IPassUniformReader<API>
    {
    public:
        MOCK_METHOD(void, readUniforms, (std::shared_ptr<typename API::PassContext> openglContext), (override));
    };
}
