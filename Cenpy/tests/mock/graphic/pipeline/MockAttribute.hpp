
#pragma once

#include <gmock/gmock.h>
#include <graphic/pipeline/Attribute.hpp>
#include <graphic/opengl/context/MockAttributeContext.hpp>

namespace cenpy::mock::graphic::pipeline
{
    template <typename API>
    class MockAttribute : public cenpy::graphic::pipeline::IAttribute<API>
    {
    public:
        MockAttribute() : cenpy::graphic::pipeline::IAttribute<API>()
        {
        }

    protected:
        MOCK_METHOD(void, bind, (std::shared_ptr<typename API::AttributeContext> context), (override));
        MOCK_METHOD(void, unbind, (std::shared_ptr<typename API::AttributeContext> context), (override));
    };

} // namespace cenpy::graphic::pipeline
