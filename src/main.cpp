/**
 * Created by Steven Peterson on 2/19/2024.
 * 
 * Purpose:
 * Summary Description:
 */

#include "ExDriver.h"
#include "CLI11.hpp"

struct Options
{
    std::string files {};
    bool        useGPU{false};
    int         maxIterations{3};
    float       variance{0.2f};
};

int main(int argc, char** argv) {
    // -- CLI --
    CLI::App app{"FooExDemo With CLI-Parsing"};
    argv = app.ensure_utf8(argv);

//    std::string filename = "default";
//    app.add_option("-f,--file", filename, "A help string");

    // Define a map to store the type of each option
    std::map<std::string, std::string> option_types;

    Options commonOptions{};
    auto opt = app.add_option("-f, --file", commonOptions.files, "path to input file or directory of files");
    option_types[opt->get_name()] = typeid(commonOptions.files).name();

    opt = app.add_flag  ("-g,--gpu", commonOptions.useGPU, "Use the GPU, if available");
    option_types[opt->get_name()] = typeid(commonOptions.useGPU).name();

    opt = app.add_option("-i,--max-iterations", commonOptions.maxIterations, "max iterations to run");
    option_types[opt->get_name()] = typeid(commonOptions.maxIterations).name();

    opt = app.add_option("-v,--variance", commonOptions.variance, "max floating-point variance");
    option_types[opt->get_name()] = typeid(commonOptions.variance).name();



    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        return app.exit(e);
    }

//    for(const auto& opt : app.get_options()) {
//        std::cout << "Option: " << opt->get_name() << ", type: " << opt->get_type_name() << ", description: " << opt->get_description() << std::endl;
//    }

    for(const auto& opt2 : app.get_options()) {
        std::cout << "Option: " << opt2->get_name()
                  << ", description: " << opt2->get_description()
                  << ", type: " << option_types[opt2->get_name()] << std::endl;
    }

    // -- end CLI --

    Rubix::helloRubix();
    return 0;
}