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
    using namespace std;

    void setupProgramArgs(ExProgramArgs &args) {
        // Add arguments to args.arguments here, for example:
   
        args.addArgument("files", std::string{}, "File paths to process.", false);
        args.addArgument("useGPU", false, "Use GPU for processing if available", false);
    }

    void helloRubix(const ExProgramArgs& args) {
        std::cout << "Hello, Foo-Rubix World!" << std::endl;

        for (const auto& baseArg : args.arguments) {
            // Use dynamic_cast to check and cast to the specific TypedArgument type
            if (auto arg = dynamic_cast<TypedArgument<std::string> *>(baseArg.get())) {
                std::cout << "Option: " << arg->name
                          << "\tValue: " << arg->value
                          << "\n";
            } else if (auto arg = dynamic_cast<TypedArgument<bool> *>(baseArg.get())) {
                std::cout << "Option: " << arg->name
                          << "\tValue: " << std::boolalpha << arg->value
                          << "\n";
            }
        }
    }

} // Rubix