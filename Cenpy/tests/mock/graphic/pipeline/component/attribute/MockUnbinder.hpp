// file: Binder

#pragma once

#include <memory>
#include <graphic/shader/component/attribute/Unbinder.hpp>

namespace cenpy::mock::graphic::pipeline::opengl::component::attribute
{
    template <typename API, typename A>
    class MockUnbinder : public cenpy::graphic::pipeline::component::attribute::IUnbinder<API, A>
    {
    public:
        MOCK_METHOD(void, unbindAttribute, (std::shared_ptr<typename API::AttributeContext> attribute), (override));
    };

}