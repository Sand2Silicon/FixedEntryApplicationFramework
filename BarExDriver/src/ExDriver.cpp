/**
 * Created by Steven Peterson on 2/19/2024.
 * 
 * Purpose:
 * Summary Description:
 */

#include <iostream>
#include "ExDriver.h"
#include "ExProgramArgs.h"

namespace Rubix {
    void setupProgramArgs(ExProgramArgs &args) {
        // Add arguments to args.arguments here, for example:
        args.arguments.push_back(std::make_shared<TypedArgument<std::string>>("models", "", "Model path to load"));
        args.arguments.push_back(std::make_shared<TypedArgument<bool>>("useGPU", false, "Use GPU for processing if available"));
    }

    void helloRubix() {
        std::cout << "Hello, Bar-Rubix World!" << std::endl;
    }


} // Rubix