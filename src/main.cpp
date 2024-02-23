/**
 * Created by Steven Peterson on 2/19/2024.
 * 
 * Purpose:
 * Summary Description:
 */

#include "../UILibrary/include/ExProgramArgs.h"
#include "ExDriver.h"
#include "CLIManager.h"
#include "CLI11.hpp"
#include <ftxui/component/component.hpp> // for the FTXUI library
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <memory>

using namespace ftxui;


int main(int argc, char** argv) {
    // -- CLI --
    CLI::App app{"FooExDemo With CLI-Parsing"};
    argv = app.ensure_utf8(argv);

    // Setup CLI parameters
    ExProgramArgs args;

    // Add arguments to args.arguments here, for example:
    args.arguments.push_back(std::make_shared<TypedArgument<bool>>("interactive", false, "Use interactive config screen."));
    args.arguments.push_back(std::make_shared<TypedArgument<std::string>>("files", "", "File paths to process"));
    args.arguments.push_back(std::make_shared<TypedArgument<bool>>("useGPU", false, "Use GPU for processing if available"));
    // ... Add other arguments ...

    CLIManager cli_manager(app, args);
    cli_manager.SetupCLI();
    cli_manager.ParseCLI(argc, argv);

    // Parse command line arguments
//    CLI11_PARSE(app, argc, argv);

    // Check if --interactive flag is passed and display the configuration screen.
    if (app["--interactive"]->as<bool>()) {
        auto screen = ftxui::ScreenInteractive::TerminalOutput();
        ftxui::Component config_screen = args.GenerateConfigScreen( &screen);
        screen.Loop(config_screen);
    }

    Rubix::helloRubix();
    return 0;
}