/**
 * Created by Steven Peterson on 2/22/2024.
 * 
 * Purpose:
 * Summary Description:
 */

#ifndef DYNAMICLIBRARYCLIENT_EXPROGRAMARGS_H
#define DYNAMICLIBRARYCLIENT_EXPROGRAMARGS_H

#include "..\include\CLI11.hpp"
#include <string>

//struct Options
//{
//    std::string files {};
//    bool        useGPU{false};
//    int         maxIterations{3};
//    float       variance{0.2f};
//};

struct ExProgramArgs {
public:
//    std::string files{};
//    bool useGPU{};
//    int maxIterations{};
//    float variance{};
//    bool interactive{};

    std::string files = "";
    bool useGPU = false;
    int maxIterations = 1000;
    float variance = 0.01f;
    bool interactive = false;  // Make sure to initialize the new flag.

    // todo find a home for these
    std::string maxIterationsStr;
    std::string varianceStr;


    void setupCLI(CLI::App& app) {
        app.add_option("--files", files, "File paths to process")->required();
        app.add_flag("--useGPU", useGPU, "Use GPU for processing if available");
        app.add_option("--maxIterations", maxIterations, "Maximum number of iterations")->default_val(1000);
        app.add_option("--variance", variance)->default_val(0.02f);
        app.add_flag("--interactive", interactive, "Use config screen");
    }
};
#endif //DYNAMICLIBRARYCLIENT_EXPROGRAMARGS_H
