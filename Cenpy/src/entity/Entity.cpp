#include <random>
#include <ranges>
#include <entity/Entity.hpp>

namespace cenpy::entity
{

    /**
     * @brief Generates a random UUIDv4.
     *
     * @return The generated UUID.
     */
    std::string generateUUID()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution dis(0, 15);

        const std::string hexChars = "0123456789abcdef";
        std::string uuid = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";

        for (char &c : uuid)
        {
            if (c == 'x')
            {
                c = hexChars[dis(gen)];
            }
            else if (c == 'y')
            {
                c = hexChars[(dis(gen) & 0x3) | 0x8];
            }
        }

        return uuid;
    }

    Entity::Entity(const std::string &type, const std::string &id, const std::initializer_list<std::shared_ptr<component::Component>> &components)
        : m_type(type), m_id(id.empty() ? generateUUID() : id), m_components(components) {}

    const std::string &Entity::getType() const { return m_type; }

    const std::string &Entity::getId() const { return m_id; }

    bool Entity::isType(const std::string_view &type) const
    {
        return m_type == type;
    }

    void Entity::addComponent(std::shared_ptr<component::Component> component)
    {
        m_components.push_back(component);
    }

    std::vector<std::weak_ptr<component::Component>> Entity::getComponents() const
    {
        std::vector<std::weak_ptr<component::Component>> components;
        for (const auto &component : m_components)
        {
            components.push_back(component);
        }
        return components;
    }
}