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

class ComponentStrategy {
public:
    virtual UILIBRARY_EXPORT ~ComponentStrategy() = default;
    virtual ftxui::Component UILIBRARY_EXPORT GenerateComponent() const = 0;
};

// BOOL - strategy
class BoolComponentStrategy : public ComponentStrategy {
    // Reference or pointer to the argument's value
    bool& value;

public:
    UILIBRARY_EXPORT BoolComponentStrategy(bool& value);

    ftxui::Component UILIBRARY_EXPORT GenerateComponent() const override;
};

// STRING - strategy
class StringComponentStrategy : public ComponentStrategy {
    // Reference or pointer to the argument's value
    std::string& value;

public:
    UILIBRARY_EXPORT StringComponentStrategy(std::string& value);

    ftxui::Component UILIBRARY_EXPORT GenerateComponent() const override;
};

#endif //DYNAMICLIBRARYCLIENT_COMPONENTSTRATEGY_H
