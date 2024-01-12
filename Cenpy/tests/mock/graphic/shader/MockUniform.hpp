
#pragma once

#include <gmock/gmock.h>
#include <graphic/shader/Uniform.hpp>
#include <graphic/shader/component/uniform/MockSetter.hpp>
#include <graphic/context/MockUniformContext.hpp>

namespace cenpy::mock::graphic::shader
{

    template <typename API>
    class MockUniform : public cenpy::graphic::shader::Uniform<API>
    {
    public:
        MockUniform() : cenpy::graphic::shader::Uniform<API>()
        {
        }
    };

} // namespace cenpy::graphic::shader
