#ifndef DYNAMICLIBRARYCLIENT_BarEXDRIVER_H
#define DYNAMICLIBRARYCLIENT_BarEXDRIVER_H
/**
 * Created by Steven Peterson on 2/19/2024.
 * 
 * Purpose:
 * Summary Description:
 */

#include "Barexdriver_export.h"
struct ExProgramArgs;   // forward declaration

namespace Rubix {

    void BAREXDRIVER_EXPORT setupProgramArgs(ExProgramArgs& args);
    void BAREXDRIVER_EXPORT helloRubix(const ExProgramArgs& args);
    
    class ExDriver {
    };

} // Rubix

#endif //DYNAMICLIBRARYCLIENT_BarEXDRIVER_H
