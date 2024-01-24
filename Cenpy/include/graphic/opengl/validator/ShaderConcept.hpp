#pragma once
#include <memory>
#include <type_traits>
#include <graphic/validator/ComponentConcept.hpp>

namespace cenpy::graphic::opengl::validator
{
    using cenpy::graphic::validator::HasComponent;
    using cenpy::graphic::validator::HasOnMethod;

    template <typename API, auto PROFILE>
    concept OpenGLShaderFlow = requires {
        requires HasComponent<typename API::ShaderContext::Loader<PROFILE>>;
        requires HasComponent<typename API::ShaderContext::Freer<PROFILE>>;
        requires HasComponent<typename API::ShaderContext::Reader<PROFILE>>;

        requires HasOnMethod<typename API::ShaderContext::Loader<PROFILE>, typename API::ShaderContext>;
        requires HasOnMethod<typename API::ShaderContext::Freer<PROFILE>, typename API::ShaderContext>;
        requires HasOnMethod<typename API::ShaderContext::Reader<PROFILE>, typename API::ShaderContext>;
    };
}