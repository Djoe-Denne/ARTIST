// PassContext.hpp

#pragma once

#include <graphic/MockApi.hpp>
#include <graphic/opengl/context/PassContext.hpp>
#include <graphic/opengl/context/MockAttributeContext.hpp>
#include <graphic/opengl/context/MockUniformContext.hpp>
#include <graphic/opengl/pipeline/component/pass/MockLoader.hpp>
#include <graphic/opengl/pipeline/component/pass/MockFreer.hpp>
#include <graphic/opengl/pipeline/component/pass/MockShaderAttacher.hpp>
#include <graphic/opengl/pipeline/component/pass/MockUniformReader.hpp>
#include <graphic/opengl/pipeline/component/pass/MockAttributeReader.hpp>
#include <graphic/opengl/pipeline/component/pass/MockUser.hpp>

namespace cenpy::mock::graphic::opengl::context
{

    class MockPassContext : public cenpy::graphic::context::PassContext<graphic::api::MockOpenGL>
    {
    public:
        template <auto PROFILE>
        using Loader = opengl::pipeline::component::pass::MockLoader<PROFILE>;
        template <auto PROFILE>
        using Freer = opengl::pipeline::component::pass::MockFreer<PROFILE>;
        template <auto PROFILE>
        using ShaderAttacher = opengl::pipeline::component::pass::MockShaderAttacher<PROFILE>;
        template <auto PROFILE>
        using UniformReader = opengl::pipeline::component::pass::MockUniformReader<PROFILE>;
        template <auto PROFILE>
        using AttributeReader = opengl::pipeline::component::pass::MockAttributeReader<PROFILE>;
        template <auto PROFILE>
        using User = opengl::pipeline::component::pass::MockUser<PROFILE>;
    };
}
