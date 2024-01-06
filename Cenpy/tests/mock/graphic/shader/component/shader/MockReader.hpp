// file: Reader.hpp

#pragma once

#include <graphic/MockApi.hpp>
#include <graphic/context/ShaderContext.hpp>
#include <graphic/shader/component/shader/Reader.hpp>
#include <gmock/gmock.h>

namespace cenpy::mock::graphic::shader::opengl::component::shader
{
    class MockReader : public cenpy::graphic::shader::component::shader::IShaderReader<graphic::api::MockOpenGL>
    {
    public:
        MOCK_METHOD(void, readShader, (std::shared_ptr<typename graphic::api::MockOpenGL::ShaderContext>), (override));
    };
}