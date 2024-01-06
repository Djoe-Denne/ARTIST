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
    class MockLoader : public cenpy::graphic::shader::component::shader::IShaderLoader<graphic::api::MockOpenGL>
    {
    public:
        MOCK_METHOD(void, loadShader, (std::shared_ptr<typename graphic::api::MockOpenGL::ShaderContext>), (override));
    };
}