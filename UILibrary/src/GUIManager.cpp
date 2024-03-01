/**
 * Created by Steven Peterson on 3/1/2024.
 * 
 * Purpose:
 * Summary Description:
 */

#include <ftxui/component/component.hpp> // for Component
#include <ftxui/dom/elements.hpp>        // for text
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/screen/screen.hpp>
#include "GUIManager.h"

ftxui::Component GUIManager::GenerateConfigScreen(ftxui::ScreenInteractive* screen) const {
    std::vector<ftxui::Component> components;

    // Original from ExProgramArgs
//    for (const auto& arg : args_.arguments) {
//        components.push_back(arg->GenerateComponent()) ;
//    }

    // "New" for GUIManager (we can do better!)
    for (const auto& arg_base : args_.arguments) {
        // Dynamically cast to known types and generate components.
        if (auto arg = dynamic_cast<const TypedArgument<bool>*>(arg_base.get())) {
            components.push_back(GenerateComponent(*arg));
        } else if (auto arg = dynamic_cast<const TypedArgument<std::string>*>(arg_base.get())) {
            components.push_back(GenerateComponent(*arg));
        }
        // Handle other types similarly...
    }


    auto container = ftxui::Container::Vertical({});
    for (const auto& component : components) {
        container->Add(component);
    }

    auto done_button = ftxui::Button("Done", screen->ExitLoopClosure());
    container->Add(done_button);

    return container;
}

ftxui::Component GUIManager::GenerateComponent(const TypedArgument<bool>& arg) const {
    return ftxui::Checkbox(arg.description, const_cast<bool*>(&arg.value));
}

ftxui::Component GUIManager::GenerateComponent(const TypedArgument<std::string>& arg) const {
    return ftxui::Input(const_cast<std::string*>(&arg.value), arg.defaultValue);
}

//template <>
//ftxui::Component GUIManager<std::string>::GenerateComponent() {
//    return ftxui::Input(&(value), defaultValue);
//}
//
//template <>
//ftxui::Component GUIManager<bool>::GenerateComponent() {
//    return ftxui::Checkbox(description, &(value));
//}

//template <>
//ftxui::Component TypedArgument<std::string>::GenerateComponent() const {
//    return ftxui::Input(&const_cast<std::string&>(value), defaultValue);
//}
//
//template <>
//ftxui::Component TypedArgument<bool>::GenerateComponent() const {
//    return ftxui::Checkbox(description, &const_cast<bool&>(value));
//}