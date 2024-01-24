#pragma once
#include <memory>
#include <type_traits>
#include <graphic/validator/ComponentConcept.hpp>

namespace cenpy::graphic::opengl::validator
{
    using cenpy::graphic::validator::HasComponent;
    using cenpy::graphic::validator::HasOnMethod;

    template <typename API, auto PROFILE>
    concept OpenGLPipelineFlow = requires {
        requires HasComponent<typename API::PipelineContext::Resetter<PROFILE>>;
        requires HasComponent<typename API::PipelineContext::User<PROFILE>>;

        requires HasOnMethod<typename API::PipelineContext::Resetter<PROFILE>, typename API::PipelineContext>;
        requires HasOnMethod<typename API::PipelineContext::User<PROFILE>, typename API::PipelineContext>;
    };
}