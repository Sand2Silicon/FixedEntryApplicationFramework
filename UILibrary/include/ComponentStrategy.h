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
    virtual ftxui::Component UILIBRARY_EXPORT GenerateComponent() const = 0;
    virtual UILIBRARY_EXPORT ~ComponentStrategy() = default;
};


/**
 * @brief BOOL - strategy
 */
class BoolComponentStrategy : public ComponentStrategy {
public:
    UILIBRARY_EXPORT BoolComponentStrategy(bool &value);

    ftxui::Component UILIBRARY_EXPORT GenerateComponent() const override;

private:
    bool &value;            // Reference or pointer to the argument's value
};


/**
 * @brief STRING - strategy
 */
class StringComponentStrategy : public ComponentStrategy {
public:
    UILIBRARY_EXPORT StringComponentStrategy(std::string &value);

    ftxui::Component UILIBRARY_EXPORT GenerateComponent() const override;

private:
    std::string &value;     // Reference or pointer to the argument's value
};

#endif //DYNAMICLIBRARYCLIENT_COMPONENTSTRATEGY_H
