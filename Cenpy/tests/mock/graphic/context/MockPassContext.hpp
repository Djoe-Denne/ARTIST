// PassContext.hpp

#pragma once

#include <graphic/MockApi.hpp>
#include <graphic/context/PassContext.hpp>
#include <graphic/pipeline/component/pass/MockLoader.hpp>
#include <graphic/pipeline/component/pass/MockFreer.hpp>
#include <graphic/pipeline/component/pass/MockShaderAttacher.hpp>
#include <graphic/pipeline/component/pass/MockUniformReader.hpp>
#include <graphic/pipeline/component/pass/MockAttributeReader.hpp>
#include <graphic/pipeline/component/pass/MockUser.hpp>

namespace cenpy::mock::graphic::opengl::context
{
    template <typename API>
    class MockPassContext : public cenpy::graphic::context::PassContext<API>
    {
    public:
        using Loader = pipeline::opengl::component::pass::MockLoader<API>;
        using Freer = pipeline::opengl::component::pass::MockFreer<API>;
        using ShaderAttacher = pipeline::opengl::component::pass::MockShaderAttacher<API>;
        using UniformReader = pipeline::opengl::component::pass::MockUniformReader<API>;
        using AttributeReader = pipeline::opengl::component::pass::MockAttributeReader<API>;
        using User = pipeline::opengl::component::pass::MockUser<API>;
    };
}
