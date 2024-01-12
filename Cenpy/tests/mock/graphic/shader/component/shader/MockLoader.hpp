// file: Loader.hpp

#pragma once

#include <string>
#include <memory>
#include <gmock/gmock.h>
#include <graphic/MockApi.hpp>
#include <graphic/context/ShaderContext.hpp>
#include <graphic/shader/component/shader/Loader.hpp>

namespace cenpy::mock::graphic::shader::opengl::component::shader
{
    template <typename API>
    class MockLoader : public cenpy::graphic::shader::component::shader::IShaderLoader<API>
    {
    public:
        MOCK_METHOD(void, loadShader, (std::shared_ptr<typename API::ShaderContext>), (override));
    };
}