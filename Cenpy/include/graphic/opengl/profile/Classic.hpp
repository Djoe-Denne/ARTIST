#pragma once

#include <graphic/opengl/profile/Pipeline.hpp>
#include <graphic/opengl/profile/Pass.hpp>
#include <graphic/opengl/profile/Shader.hpp>
#include <graphic/opengl/profile/Attribute.hpp>


namespace cenpy::graphic::opengl::profile
{
    class Classic
    {
    public:
        using Pipeline = Pipeline::Classic;
        using IPass = IPass::Classic;
        using Shader = Shader::Classic;
        using Attribute = Attribute::Classic;
        using Uniform = Uniform::Classic;
    }
}
