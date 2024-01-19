// file: Binder

#pragma once

#include <memory>
#include <graphic/shader/component/attribute/Binder.hpp>

namespace cenpy::mock::graphic::pipeline::opengl::component::attribute
{
    template <typename API, typename A>
    class MockBinder : public cenpy::graphic::pipeline::component::attribute::IBinder<API, A>
    {
    public:
        MOCK_METHOD(void, bindAttribute, (std::shared_ptr<typename API::AttributeContext> attribute), (override));
    };

}