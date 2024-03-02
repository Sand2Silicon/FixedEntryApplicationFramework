/**
 * Created by Steven Peterson on 2/19/2024.
 * 
 * Purpose:
 * Summary Description:
 */

#include "ExProgramArgs.h"
#include "ExDriver.h"
#include "CLIManager.h"
#include "CLI11.hpp"
#include "GUIManager.h"
//#include <ftxui/component/component.hpp> // for the FTXUI library
//#include <ftxui/dom/elements.hpp>
//#include <ftxui/screen/screen.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <memory>

using namespace ftxui;

int main(int argc, char** argv) {
    // -- CLI --
    CLI::App app{"FooExDemo With CLI-Parsing"};
    argv = app.ensure_utf8(argv);

    // Setup CLI parameters
    ExProgramArgs args;

    // Add universal arguments to args.arguments here:
    args.arguments.emplace_back(std::make_unique<TypedArgument<bool>>
            ("interactive", false, "Use interactive config screen.")
            )->setRequired();

    // Add program specific arguments
    Rubix::setupProgramArgs(args);

    try {
        CLIManager cliManager(app, args);
        cliManager.SetupCLI();
        cliManager.ParseCLI(argc, argv);

        // Check if --interactive flag is passed and display the configuration screen.
        if (app["--interactive"]->as<bool>()) {
            auto screen = ftxui::ScreenInteractive::TerminalOutput();
            GUIManager guiManager(args);

            ftxui::Component config_screen = guiManager.GenerateConfigScreen(&screen);            //args.GenerateConfigScreen(&screen);
            screen.Loop(config_screen);
        }

        // Do the program's real work!
        // Call library function with error handling.
        try {
            Rubix::helloRubix(args);
        } catch (const std::exception& e)
        {
            std::cerr << "Error calling hellRubix(): " << e.what() <<std::endl;
            return EXIT_FAILURE;
        }

    } catch (const CLI::ParseError& e) {
        return app.exit(e);     // CLI11 provides app.exit() to handle exceptions nicely
    } catch (const std::exception& e) {
        std::cerr << "Error: " <<e.what() << std::endl;
        return EXIT_FAILURE;
    }

    system("pause");
    return EXIT_SUCCESS;
}