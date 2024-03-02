/**
 * Created by Steven Peterson on 3/2/2024.
 * 
 * Purpose:
 * Summary Description:
 */

#include <ftxui/component/component.hpp>
#include "ComponentStrategy.h"

// BOOL - strategy
BoolComponentStrategy::BoolComponentStrategy(bool& value) : value(value) {}

ftxui::Component BoolComponentStrategy::GenerateComponent() const {
    return ftxui::Checkbox("", &value);
}


// STRING - strategy
StringComponentStrategy::StringComponentStrategy(std::string& value) : value(value) {}

ftxui::Component StringComponentStrategy::GenerateComponent() const {
    return ftxui::Input("", &value);
}