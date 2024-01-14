#pragma once

#include <memory>
#include <graphic/MockApi.hpp>
#include <gmock/gmock.h>
#include <graphic/pipeline/component/pass/ShaderAttacher.hpp>

namespace cenpy::mock::graphic::pipeline::opengl::component::pass
{
    template <typename API>
    class MockShaderAttacher : public cenpy::graphic::pipeline::component::pass::IShaderAttacher<API>
    {
    public:
        MOCK_METHOD(void, attachShaders, (std::shared_ptr<typename API::PassContext> openglContext), (override));
    };

}
