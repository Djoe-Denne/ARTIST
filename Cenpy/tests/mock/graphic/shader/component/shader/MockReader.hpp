// file: Reader.hpp

#pragma once

#include <graphic/MockApi.hpp>
#include <graphic/context/ShaderContext.hpp>
#include <graphic/shader/component/shader/Reader.hpp>
#include <gmock/gmock.h>

namespace cenpy::mock::graphic::shader::opengl::component::shader
{
    template <typename API>
    class MockReader : public cenpy::graphic::shader::component::shader::IShaderReader<API>
    {
    public:
        MOCK_METHOD(void, readShader, (std::shared_ptr<typename API::ShaderContext>), (override));
    };
}