#pragma once

#include <memory>
#include <graphic/pipeline/component/attribute/Binder.hpp>
#include <graphic/pipeline/component/attribute/Setter.hpp>
#include <graphic/pipeline/component/attribute/Unbinder.hpp>

namespace cenpy::graphic::pipeline
{

    template <typename API>
    class Attribute
    {
    public:
        // Constructor
        Attribute(std::shared_ptr<typename API::AttributeContext::Binder> binder,
                  std::shared_ptr<typename API::AttributeContext::Setter> setter,
                  std::shared_ptr<typename API::AttributeContext::Unbinder> unbinder,
                  std::shared_ptr<typename API::AttributeContext> context)
            : m_binder(binder), m_setter(setter), m_unbinder(unbinder), m_context(context) {}

        Attribute() : Attribute(std::make_shared<typename API::AttributeContext::Binder>(),
                                std::make_shared<typename API::AttributeContext::Setter>(),
                                std::make_shared<typename API::AttributeContext::Unbinder>(),
                                std::make_shared<typename API::AttributeContext>())
        {
        }

        void bind()
        {
            if (m_binder)
            {
                m_binder->bind();
            }
        }

        void set()
        {
            if (m_setter)
            {
                m_setter->set();
            }
        }

        void unbind()
        {
            if (m_unbinder)
            {
                m_unbinder->unbind();
            }
        }

        [[nodiscard]] virtual std::shared_ptr<typename API::AttributeContext> getContext() const
        {
            return m_context;
        }

    protected:
        [[nodiscard]] virtual std::shared_ptr<typename API::AttributeContext::Binder> getBinder() const
        {
            return m_binder;
        }

        [[nodiscard]] virtual std::shared_ptr<typename API::AttributeContext::Setter> getSetter() const
        {
            return m_setter;
        }

        [[nodiscard]] virtual std::shared_ptr<typename API::AttributeContext::Unbinder> getUnbinder() const
        {
            return m_unbinder;
        }

    private:
        std::shared_ptr<typename API::AttributeContext::Binder> m_binder;
        std::shared_ptr<typename API::AttributeContext::Setter> m_setter;
        std::shared_ptr<typename API::AttributeContext::Unbinder> m_unbinder;
        std::shared_ptr<typename API::AttributeContext> m_context;
    };
}
