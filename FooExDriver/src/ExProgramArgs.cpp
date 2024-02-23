/**
 * Created by Steven Peterson on 2/23/2024.
 * 
 * Purpose:
 * Summary Description:
 */

#include "ExProgramArgs.h"
#include <ftxui/component/component.hpp> // for Component
#include <ftxui/dom/elements.hpp>        // for text
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/screen/screen.hpp>

ftxui::Component ExProgramArgs::GenerateConfigScreen(ftxui::ScreenInteractive* screen) const {
    std::vector<ftxui::Component> components;

    for (const auto& arg : arguments) {
        components.push_back(arg->GenerateComponent()) ;
    }

    auto container = ftxui::Container::Vertical({});
    for (const auto& component : components) {
        container->Add(component)  ;
    }

    auto done_button = ftxui::Button("Done", screen->ExitLoopClosure());
    container->Add(done_button);

    return container;
}
