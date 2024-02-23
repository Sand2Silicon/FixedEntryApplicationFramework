#ifndef DYNAMICLIBRARYCLIENT_EXDRIVER_H
#define DYNAMICLIBRARYCLIENT_EXDRIVER_H
/**
 * Created by Steven Peterson on 2/19/2024.
 *
 * Purpose:
 * Summary Description:
 */

#include "fooexdriver_export.h"
struct ExProgramArgs;   // forward declaration

namespace Rubix {

    void FOOEXDRIVER_EXPORT setupProgramArgs(ExProgramArgs& args);
    void FOOEXDRIVER_EXPORT helloRubix();
    
    class ExDriver {
    };

} // Rubix

#endif //DYNAMICLIBRARYCLIENT_EXDRIVER_H
