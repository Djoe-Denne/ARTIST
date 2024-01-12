// PassContext.hpp

#pragma once

#include <graphic/MockApi.hpp>
#include <graphic/context/PassContext.hpp>
#include <graphic/shader/component/pass/MockLoader.hpp>
#include <graphic/shader/component/pass/MockFreer.hpp>
#include <graphic/shader/component/pass/MockShaderAttacher.hpp>
#include <graphic/shader/component/pass/MockUniformReader.hpp>
#include <graphic/shader/component/pass/MockUser.hpp>

namespace cenpy::mock::graphic::opengl::context
{
    template <typename API>
    class MockPassContext : public cenpy::graphic::context::PassContext<API>
    {
    public:
        using Loader = shader::opengl::component::pass::MockLoader<API>;
        using Freer = shader::opengl::component::pass::MockFreer<API>;
        using ShaderAttacher = shader::opengl::component::pass::MockShaderAttacher<API>;
        using UniformReader = shader::opengl::component::pass::MockUniformReader<API>;
        using User = shader::opengl::component::pass::MockUser<API>;
    };
}
