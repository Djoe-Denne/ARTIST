#pragma once

#include <memory>
#include <graphic/MockApi.hpp>
#include <gmock/gmock.h>
#include <graphic/shader/component/pass/ShaderAttacher.hpp>

namespace cenpy::mock::graphic::shader::opengl::component::pass
{
    template <typename API>
    class MockShaderAttacher : public cenpy::graphic::shader::component::pass::IShaderAttacher<API>
    {
    public:
        MOCK_METHOD(void, attachShaders, (std::shared_ptr<typename API::PassContext> openglContext), (override));
    };

}
