#pragma once

#include <memory>
#include <graphic/MockApi.hpp>
#include <gmock/gmock.h>
#include <graphic/shader/component/pass/UniformReader.hpp>

namespace cenpy::mock::graphic::shader::opengl::component::pass
{
    class MockUniformReader : public cenpy::graphic::shader::component::pass::IPassUniformReader<graphic::api::MockOpenGL>
    {
    public:
        MOCK_METHOD(void, readUniforms, (std::shared_ptr<typename graphic::api::MockOpenGL::PassContext> openglContext), (override));
    };
}
