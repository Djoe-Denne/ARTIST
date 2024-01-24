#pragma once
#include <memory>
#include <type_traits>
#include <graphic/validator/ComponentConcept.hpp>

namespace cenpy::graphic::opengl::validator
{

    using cenpy::graphic::validator::HasComponent;
    using cenpy::graphic::validator::HasOnMethod;

    template <typename API, auto PROFILE>
    concept OpenGLPassFlow = requires {
        requires HasComponent<typename API::PassContext::Loader<PROFILE>>;
        requires HasComponent<typename API::PassContext::Freer<PROFILE>>;
        requires HasComponent<typename API::PassContext::ShaderAttacher<PROFILE>>;
        requires HasComponent<typename API::PassContext::AttributeReader<PROFILE>>;
        requires HasComponent<typename API::PassContext::User<PROFILE>>;

        requires HasOnMethod<typename API::PassContext::Loader<PROFILE>, typename API::PassContext>;
        requires HasOnMethod<typename API::PassContext::Freer<PROFILE>, typename API::PassContext>;
        requires HasOnMethod<typename API::PassContext::ShaderAttacher<PROFILE>, typename API::PassContext>;
        requires HasOnMethod<typename API::PassContext::AttributeReader<PROFILE>, typename API::PassContext>;
        requires HasOnMethod<typename API::PassContext::User<PROFILE>, typename API::PassContext>;
    };
}