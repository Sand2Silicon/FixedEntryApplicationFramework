/**
 * Created by Steven Peterson on 2/23/2024.
 * 
 * Purpose:
 * Summary Description:
 */

#include "../include/ExProgramArgs.h"
//#include <ftxui/component/component.hpp> // for Component
//#include <ftxui/dom/elements.hpp>        // for text
//#include <ftxui/component/screen_interactive.hpp>
//#include <ftxui/screen/screen.hpp>

/** Moved to GUIManager
ftxui::Component ExProgramArgs::GenerateConfigScreen(ftxui::ScreenInteractive* screen) const {
    std::vector<ftxui::Component> components;

    for (const auto& arg : arguments) {
        components.push_back(arg->GenerateComponent()) ;
    }

    auto container = ftxui::Container::Vertical({});
    for (const auto& component : components) {
        container->Add(component);
    }

    auto done_button = ftxui::Button("Done", screen->ExitLoopClosure());
    container->Add(done_button);

    return container;
}
// */

/** Moved to GUIManager
template <>
ftxui::Component TypedArgument<std::string>::GenerateComponent() {
    return ftxui::Input(&(value), defaultValue);
}

template <>
ftxui::Component TypedArgument<bool>::GenerateComponent() {
    return ftxui::Checkbox(description, &(value));
}
// */

//template <>
//ftxui::Component TypedArgument<std::string>::GenerateComponent() const {
//    return ftxui::Input(&const_cast<std::string&>(value), defaultValue);
//}
//
//template <>
//ftxui::Component TypedArgument<bool>::GenerateComponent() const {
//    return ftxui::Checkbox(description, &const_cast<bool&>(value));
//}