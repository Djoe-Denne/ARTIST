#pragma once

#include <memory>
#include <gmock/gmock.h>
#include <graphic/MockApi.hpp>
#include <graphic/pipeline/component/pass/Freer.hpp>

namespace cenpy::mock::graphic::pipeline::opengl::component::pass
{
    namespace pipeline = cenpy::graphic::pipeline;
    template <typename API>
    class MockFreer : public cenpy::graphic::pipeline::component::pass::IPassFreer<API>
    {
    public:
        MOCK_METHOD(void, freePass, (std::shared_ptr<typename API::PassContext>), (override));
    };

}