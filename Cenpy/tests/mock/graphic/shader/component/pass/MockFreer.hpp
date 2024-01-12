#pragma once

#include <memory>
#include <gmock/gmock.h>
#include <graphic/MockApi.hpp>
#include <graphic/shader/component/pass/Freer.hpp>

namespace cenpy::mock::graphic::shader::opengl::component::pass
{
    namespace shader = cenpy::graphic::shader;
    template <typename API>
    class MockFreer : public cenpy::graphic::shader::component::pass::IPassFreer<API>
    {
    public:
        MOCK_METHOD(void, freePass, (std::shared_ptr<typename API::PassContext>), (override));
    };

}