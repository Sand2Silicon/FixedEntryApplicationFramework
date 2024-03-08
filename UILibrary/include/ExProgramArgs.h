/**
 * Created by Steven Peterson on 2/22/2024.
 * 
 * Purpose:
 * Summary Description:
 */

#ifndef DYNAMICLIBRARYCLIENT_EXPROGRAMARGS_H
#define DYNAMICLIBRARYCLIENT_EXPROGRAMARGS_H

#include "../../include/CLI11.hpp"
#include <string>
#include <stdexcept>    // for std::invlaid_argument
#include <sstream>      // for std::stringstream
#include <unordered_map>

//#include <ftxui/component/component.hpp>
//#include <ftxui/dom/elements.hpp>
//#include <ftxui/screen/screen.hpp>
#include "uilibrary_export.h"
#include "ComponentStrategy.h"

#include <variant>

// Variant to hold different types of argument values.
using ArgumentVariant = std::variant<bool, int, float, std::string>;

struct ArgumentBase {
    ArgumentBase(const std::string& name, const std::string& description) :
            name(name), description(description) {}

    std::string name;
    std::string description;
    virtual ~ArgumentBase() = default;
    virtual void AddToCLI(CLI::App& app) = 0;

    virtual ArgumentVariant GetValue() const = 0;

    // TODO: Add setRequired() setMutuallyExclusive()
    ArgumentBase& setRequired() {
        std::cout << "option required\n";
        return *this;
    }
};

template <typename T>
struct TypedArgument : ArgumentBase {
    T value;
    T defaultValue;
    std::function<void()> on_change;

    TypedArgument(std::string name, T defaultValue, std::string description)
            : ArgumentBase(std::move(name), std::move(description)),
              value(defaultValue),
              defaultValue(defaultValue) {}

    void AddToCLI(CLI::App& app) override {
        app.add_option("--" + name, value, description)->default_val(defaultValue);
    }

    [[nodiscard]] ArgumentVariant GetValue() const override {
        return value;
    }

    /**
     * @brief Function to handle value changes, converting strings to the correct type
     * @param input
     */
    void SetValueFromString(const std::string& input) {
        std::stringstream ss(input);
        T newValue;
        if (*!(ss >> newValue)) {
            throw std::invalid_argument("Invalid input for argument: " + name);
        }
        value = newValue;
    }

};

using ArgumentList = std::vector<std::unique_ptr<ArgumentBase>>;
using StrategyList = std::map<std::string, std::shared_ptr<ComponentStrategy>>;

struct ExProgramArgs {
    ArgumentList arguments;
    StrategyList componentStrategies;

    template<typename T>
    void addArgument(std::string name, T defaultValue, std::string description = "", bool required = false) {
        
        auto argument = std::make_unique<TypedArgument<T>> (name, defaultValue, description);       
        addStrategy(argument->name, argument->value, description, required);
        arguments.push_back(std::move(argument));
    }

    /** // My Version 
    void addStrategy(std::string name, ArgumentVariant &value, std::string description, bool required) {
        if (holds_alternative<bool>(value)) {
            addStrategy(name, std::make_shared<BoolComponentStrategy>(name, get<bool>(value), description, false));
        } else if (holds_alternative<std::string>(value)) {
            addStrategy(name, std::make_shared<StringComponentStrategy>(name, get<std::string>(value), description, false));
        }
    }   // */

    template<typename T>    
    void addStrategy(std::string name, T& value, std::string description, bool required) {
        if constexpr (std::is_same_v<T, bool>) {
            addStrategy(name, std::make_shared<BoolComponentStrategy>(name, value, description, false));
        }
        else if constexpr (std::is_same_v<T, std::string>) {
            addStrategy(name, std::make_shared<StringComponentStrategy>(name, value, description, false));
        }
    }

    // Method to add strategies for arguments
    void addStrategy(const std::string &argumentName, std::shared_ptr<ComponentStrategy> strategy) {
        componentStrategies[argumentName] = strategy;
    }
};



    /*
    void setupCLI(CLI::App& app) {
        for (auto& arg : arguments) {
            arg->AddToCLI(app);
        }
    }
    // */
//};


#endif //DYNAMICLIBRARYCLIENT_EXPROGRAMARGS_H
