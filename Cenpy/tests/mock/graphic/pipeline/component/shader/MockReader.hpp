// file: Reader.hpp

#pragma once

#include <graphic/MockApi.hpp>
#include <graphic/context/ShaderContext.hpp>
#include <graphic/pipeline/component/shader/Reader.hpp>
#include <gmock/gmock.h>

namespace cenpy::mock::graphic::pipeline::opengl::component::shader
{
    template <typename API>
    class MockReader : public cenpy::graphic::pipeline::component::shader::IShaderReader<API>
    {
    public:
        MOCK_METHOD(void, readShader, (std::shared_ptr<typename API::ShaderContext>), (override));
    };
}