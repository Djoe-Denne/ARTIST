#pragma once
#include <graphic/opengl/validator/PassConcept.hpp>
#include <graphic/opengl/validator/PipelineConcept.hpp>
#include <graphic/opengl/validator/ShaderConcept.hpp>
#include <graphic/opengl/validator/AttributeConcept.hpp>
#include <graphic/opengl/validator/UniformConcept.hpp>

namespace cenpy::graphic::opengl::validator
{

    struct Validator
    {
    public:
        template <typename API, auto PROFILE>
            requires OpenGLPassFlow<API, PROFILE>
        static constexpr bool validatePass()
        {
            return true;
        }

        template <typename API, auto PROFILE>
            requires OpenGLPipelineFlow<API, PROFILE>
        static constexpr bool validatePipeline()
        {
            return true;
        }
        template <typename API, auto PROFILE>
            requires OpenGLShaderFlow<API, PROFILE>
        static constexpr bool validateShader()
        {
            return true;
        }
        template <typename API, auto PROFILE>
            requires OpenGLAttributeFlow<API, PROFILE>
        static constexpr bool validateAttribute()
        {
            return true;
        }
        template <typename API>
            requires OpenGLUniformFlow<API>
        static constexpr bool validateUniform()
        {
            return true;
        }
    };
}