/**
 * Created by Steven Peterson on 2/19/2024.
 * 
 * Purpose:
 * Summary Description:
 */

#include "ExProgramArgs.h"
#include "ExDriver.h"
#include "CLI11.hpp"
#include <ftxui/component/component.hpp> // for the FTXUI library
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/screen_interactive.hpp>

using namespace ftxui;


Component GenerateConfigScreen(ExProgramArgs& args) {
    // Create input fields for the parameters
    auto files_input = Input(&args.files, "path/to/file");
    auto use_gpu_checkbox = Checkbox("Use GPU", &args.useGPU);

    // Convert maxIterations to string for the Input component
    args.maxIterationsStr = std::to_string(args.maxIterations);
    auto max_iterations_input = Input(&args.maxIterationsStr, "");

    // Convert variance to string for the Input component
    args.varianceStr = std::to_string(args.variance);
    auto variance_input = Input(&args.varianceStr, "");


    // Create a 'Done' button
    auto done_button = Button("Done", [&] {
        // Convert the string input back to the appropriate data types
        std::stringstream ss;

        ss.str(args.maxIterationsStr);
        ss >> args.maxIterations;
        ss.clear(); // Clear state flags

        ss.str(args.varianceStr);
        ss >> args.variance;
        // Add any additional logic you need to handle the 'Done' action
    });

    // Create a container to hold all components
    // Create a container to hold all components
    auto container = Container::Vertical({
        Container::Horizontal({
            Renderer([] { return text("Files: "); }),
            files_input
        }),
        Container::Horizontal({
            Renderer([] { return text("Use GPU: "); }),
            use_gpu_checkbox
        }),
        Container::Horizontal({
            Renderer([] { return text("Max Iterations: "); }),
            max_iterations_input
        }),
        Container::Horizontal({
            Renderer([] { return text("Variance: "); }),
            variance_input
        }),
        done_button,
    });

    // Add additional styling if desired
//    files_input->SetBorder(true);
//    max_iterations_input->SetBorder(true);
//    variance_input->SetBorder(true);

    // Return the container as a Component
    return container;
}

int main(int argc, char** argv) {
    // -- CLI --
    CLI::App app{"FooExDemo With CLI-Parsing"};
    argv = app.ensure_utf8(argv);

    // Setup CLI parameters
    ExProgramArgs args;
    args.setupCLI(app);

    // Parse command line arguments
    CLI11_PARSE(app, argc, argv);

    // Check if --interactive flag is passed and display the configuration screen.
    if (app["--interactive"]->as<bool>()) {
        auto screen = ftxui::ScreenInteractive::TerminalOutput();
        ftxui::Component config_screen = GenerateConfigScreen(args);
        screen.Loop(config_screen);
    }

//    for(const auto& opt : app.get_options()) {
//        std::cout << "Option: " << opt->get_name() << ", type: " << opt->get_type_name() << ", description: " << opt->get_description() << std::endl;
//    }

//    for(const auto& opt2 : app.get_options()) {
//        std::cout << "Option: " << opt2->get_name()
//                  << ", description: " << opt2->get_description()
//                  << ", type: " << option_types[opt2->get_name()] << std::endl;
//    }

    // -- end CLI --

    Rubix::helloRubix();
    return 0;
}