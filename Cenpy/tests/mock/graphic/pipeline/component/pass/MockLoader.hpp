#pragma once

#include <memory>
#include <gmock/gmock.h>
#include <graphic/MockApi.hpp>
#include <graphic/pipeline/component/pass/Loader.hpp>
#include <graphic/pipeline/component/pass/MockShaderAttacher.hpp>

namespace cenpy::mock::graphic::pipeline::opengl::component::pass
{

    template <typename API>
    class MockLoader : public cenpy::graphic::pipeline::component::pass::ILoader<API>
    {
    public:
        MOCK_METHOD(void, loadPass, (std::shared_ptr<typename API::PassContext>), (override));
        MOCK_METHOD(void, setAttacher, (const std::shared_ptr<cenpy::mock::graphic::pipeline::opengl::component::pass::MockShaderAttacher<API>>), ());
    };
}
