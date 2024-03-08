#ifndef DYNAMICLIBRARYCLIENT_COMPONENTSTRATEGY_H
#define DYNAMICLIBRARYCLIENT_COMPONENTSTRATEGY_H

/**
 * Created by Steven Peterson on 3/2/2024.
 * 
 * Purpose:
 * Summary Description:
 */

#include "uilibrary_export.h"
#include <ftxui/component/component.hpp>

/**
 * @brief Base class - strategies for generating FTXUI components for the configuration screen.
 */
class ComponentStrategy {
public:
    ComponentStrategy(const std::string& name, const std::string& description, bool required) :
            name{std::move(name)}, description{std::move(description)}, required {required} {};
    virtual UILIBRARY_EXPORT ~ComponentStrategy() = default;

    virtual ftxui::Component UILIBRARY_EXPORT GenerateComponent() const = 0;

protected:
    std::string name;
    std::string description;
    bool required;
};


/**
 * @brief BOOL - strategy
 */
class BoolComponentStrategy : public ComponentStrategy {
public:
    UILIBRARY_EXPORT BoolComponentStrategy(std::string name, bool& value, std::string description="", bool required=false);

    ftxui::Component UILIBRARY_EXPORT GenerateComponent() const override;

private:
    bool& value;            // Reference or pointer to the argument's value
};


/**
 * @brief STRING - strategy
 */
class StringComponentStrategy : public ComponentStrategy {
public:
    UILIBRARY_EXPORT StringComponentStrategy(std::string name, std::string& value, std::string description="", bool required=false);

    ftxui::Component UILIBRARY_EXPORT GenerateComponent() const override;

private:
    std::string& value;     // Reference or pointer to the argument's value
};

#endif //DYNAMICLIBRARYCLIENT_COMPONENTSTRATEGY_H
