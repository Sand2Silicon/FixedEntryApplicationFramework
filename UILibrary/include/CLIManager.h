#ifndef DYNAMICLIBRARYCLIENT_CLIMANAGER_H
#define DYNAMICLIBRARYCLIENT_CLIMANAGER_H

/**
 * Created by Steven Peterson on 2/23/2024.
 * 
 * Purpose:
 * Summary Description:
 */

#include "CLI11.hpp"
#include "ExProgramArgs.h"

class CLIManager {
public:
    CLIManager(CLI::App& app, ExProgramArgs& args) : app_(app), args_(args) {}

    void SetupCLI() {
        for (auto& arg : args_.arguments) {
            arg->AddToCLI(app_);
        }
    //     args_.setupCLI(app_);
    }

    inline int ParseCLI(int argc, char** argv) {
        CLI11_PARSE(app_, argc, argv);
        return 0;
    }

private:
    CLI::App& app_;
    ExProgramArgs& args_;
};
#endif //DYNAMICLIBRARYCLIENT_CLIMANAGER_H
