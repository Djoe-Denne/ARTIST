
#pragma once

#include <gmock/gmock.h>
#include <graphic/pipeline/Uniform.hpp>
#include <graphic/opengl/context/MockUniformContext.hpp>

namespace cenpy::mock::graphic::pipeline
{

    template <typename API>
    class MockUniform : public cenpy::graphic::pipeline::Uniform<API>
    {
    public:
        MockUniform() : cenpy::graphic::pipeline::Uniform<API>()
        {
        }
    };

} // namespace cenpy::graphic::pipeline
