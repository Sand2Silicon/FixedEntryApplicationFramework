#ifndef DYNAMICLIBRARYCLIENT_CLIMANAGER_H
#define DYNAMICLIBRARYCLIENT_CLIMANAGER_H

/**
 * Created by Steven Peterson on 2/23/2024.
 * 
 * Purpose:
 * Summary Description:
 */

#include "..\include\CLI11.hpp"
#include "../../UILibrary/include/ExProgramArgs.h"

class CLIManager {
public:
    CLIManager(CLI::App& app, ExProgramArgs& args) : app_(app), args_(args) {}

    void SetupCLI() {
        args_.setupCLI(app_);
    }

    int ParseCLI(int argc, char** argv) {
        CLI11_PARSE(app_, argc, argv);
        return 0;
    }

private:
    CLI::App& app_;
    ExProgramArgs& args_;
};
#endif //DYNAMICLIBRARYCLIENT_CLIMANAGER_H
