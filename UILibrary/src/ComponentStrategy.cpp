/**
 * Created by Steven Peterson on 3/2/2024.
 * 
 * Purpose:
 * Summary Description:
 */

#include <ftxui/component/component.hpp>
#include "ComponentStrategy.h"

// BOOL - strategy
BoolComponentStrategy::BoolComponentStrategy(std::string name, bool& value, std::string description, bool required) :
ComponentStrategy(std::move(name), std::move(description), required), value{value} {}

ftxui::Component BoolComponentStrategy::GenerateComponent() const {
    return ftxui::Checkbox(name, &value);
}


// STRING - strategy
StringComponentStrategy::StringComponentStrategy(std::string name, std::string& value, std::string description, bool required)
        : ComponentStrategy(std::move(name), std::move(description), required), value{value} {}

ftxui::Component StringComponentStrategy::GenerateComponent() const {
    return ftxui::Input(&value, name);

}
