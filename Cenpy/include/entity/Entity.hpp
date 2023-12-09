#pragma once

#include <string>
#include <memory>
#include <vector>
#include <initializer_list>
#include <component/Component.hpp>

namespace cenpy::entity
{
    /**
     * @brief Generates a random UUIDv4.
     *
     * @return The generated UUID.
     */
    std::string generateUUID();

    /**
     * @brief A base class for all entities of the ECS Entity
     *
     * This class represents a base entity in the Entity Component System (ECS) architecture.
     * It provides functionality to store and retrieve components associated with the entity.
     * Each entity has a type and an optional unique identifier.
     */
    class Entity
    {
    public:
        /**
         * @brief Constructs an Entity object with the specified type and optional identifier.
         *
         * @param type The type of the entity.
         * @param id The unique identifier of the entity. If empty, a random UUIDv4 will be generated.
         */
        Entity(const std::string &type = "default", const std::string &id = "", const std::initializer_list<std::shared_ptr<component::Component>> &components = {});

        /**
         * @brief Gets the type of the entity.
         *
         * @return The type of the entity.
         */
        [[nodiscard]] const std::string &getType() const;

        /**
         * @brief Gets the identifier of the entity.
         *
         * @return The identifier of the entity.
         */
        [[nodiscard]] const std::string &getId() const;

        /**
         * @brief Checks if the entity is of a specific type.
         *
         * @param type The type to check against.
         * @return true if the entity is of the specified type, false otherwise.
         */
        [[nodiscard]] bool isType(const std::string &type) const;

        /**
         * @brief Adds a component to the entity.
         *
         * @param component A unique pointer to the component to be added.
         */
        void addComponent(std::shared_ptr<component::Component> component);

        /**
         * @brief Gets the components associated with the entity.
         *
         * @return A vector of weak pointers to the components.
         */
        [[nodiscard]] std::vector<std::weak_ptr<component::Component>> getComponents() const;

    private:
        std::string m_type;                                              // The type of the entity.
        std::string m_id;                                                // The unique identifier of the entity.
        std::vector<std::shared_ptr<component::Component>> m_components; // The components associated with the entity.
    };
}
