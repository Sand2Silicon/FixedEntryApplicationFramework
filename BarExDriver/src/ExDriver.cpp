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
        auto modelsArg = std::make_unique<TypedArgument<std::string>>("models", "DefaultValue", "Model path to load");
        args.addStrategy(modelsArg->name, std::make_shared<StringComponentStrategy>(modelsArg->name, modelsArg->value, "", false));
        args.arguments.push_back(std::move(modelsArg));
        
        auto gpuArg = std::make_unique<TypedArgument<bool>> ("useGPU", false, "Use GPU for processing if available");
        args.addStrategy(gpuArg->name, std::make_shared<BoolComponentStrategy>(gpuArg->name, gpuArg->value, "", false));
        args.arguments.push_back(std::move(gpuArg));

    }

    void helloRubix(const ExProgramArgs& args) {
        cout << "Hello, Bar-Rubix World!" << std::endl;

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