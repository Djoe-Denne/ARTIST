#pragma once

#include <memory>
#include <gmock/gmock.h>
#include <graphic/MockApi.hpp>
#include <graphic/shader/component/pass/Loader.hpp>
#include <graphic/shader/component/pass/MockShaderAttacher.hpp>

namespace cenpy::mock::graphic::shader::opengl::component::pass
{

    class MockLoader : public cenpy::graphic::shader::component::pass::IPassLoader<graphic::api::MockOpenGL>
    {
    public:
        MOCK_METHOD(void, loadPass, (std::shared_ptr<typename graphic::api::MockOpenGL::PassContext>), (override));
        MOCK_METHOD(void, setAttacher, (const std::shared_ptr<cenpy::mock::graphic::shader::opengl::component::pass::MockShaderAttacher>), ());
    };
}
