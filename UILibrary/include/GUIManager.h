#ifndef DYNAMICLIBRARYCLIENT_GUIMANAGER_H
#define DYNAMICLIBRARYCLIENT_GUIMANAGER_H

/**
 * Created by Steven Peterson on 3/1/2024.
 * 
 * Purpose: Manage the FTXUI GUI elements (config panel generation from arguments) separate
 *          of any other concerns.
 * Summary Description:
 */

#include "ExProgramArgs.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

class GUIManager {
public:
    explicit GUIManager(const ExProgramArgs& args) : args_{args}{};

    ftxui::Component UILIBRARY_EXPORT GenerateConfigScreen(ftxui::ScreenInteractive* screen) const;

    // Additional methods to handle UI-specific logic
    // ...

private:
    const ExProgramArgs& args_;
    // Helper functions to generate components for each argument type.
    ftxui::Component GenerateComponent(const TypedArgument<bool>& arg) const;
    ftxui::Component GenerateComponent(const TypedArgument<std::string>& arg) const;
};

// Declare the explicit specializations
//template <>
//ftxui::Component UILIBRARY_EXPORT TypedArgument<std::string>::GenerateComponent();
//
//template <>
//ftxui::Component UILIBRARY_EXPORT TypedArgument<bool>::GenerateComponent();




#endif //DYNAMICLIBRARYCLIENT_GUIMANAGER_H
