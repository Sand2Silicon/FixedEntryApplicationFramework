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
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
// #include "fooexdriver_export.h"
#include "uilibrary_export.h"

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
    virtual ftxui::Component GenerateComponent() = 0;

    virtual ArgumentVariant GetValue() const = 0;
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

    ftxui::Component GenerateComponent() override;

    ArgumentVariant GetValue() const override {
        return value;
    }

};

using ArgumentList = std::vector<std::shared_ptr<ArgumentBase>>;

struct ExProgramArgs {
    ArgumentList arguments;

    void setupCLI(CLI::App& app) {
        for (auto& arg : arguments) {
            arg->AddToCLI(app);
        }
    }

    ftxui::Component UILIBRARY_EXPORT GenerateConfigScreen(ftxui::ScreenInteractive* screen) const;
};

// Declare the explicit specializations
template <>
ftxui::Component UILIBRARY_EXPORT TypedArgument<std::string>::GenerateComponent();

template <>
ftxui::Component UILIBRARY_EXPORT TypedArgument<bool>::GenerateComponent();



#endif //DYNAMICLIBRARYCLIENT_EXPROGRAMARGS_H
