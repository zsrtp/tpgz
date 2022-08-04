#include <main.h>
#include "libtp_c/include/patch.h"
#include "libtp_c/include/addrs.h"

namespace mod
{
    void main()
    {
        /**
         * Old way of printing to the console
         * Kept for reference as its still being used by the new console class.
         *
         * libtp::display::setConsole(true, 25);
         * libtp::display::print(1, "Hello World!");
         */

        // Technically I prefer to do the function hooks at the very top but since this is a template I'll do it here so we can
        // have hello world at the top

        // Hook the function that runs each frame
        
        return_fapGm_Execute = hookFunction( *(void(*)())tp_fapGm_Execute_addr, storage, procNewFrame );
        return;
    }

    void exit() {}

    void procNewFrame()
    {
        // This runs BEFORE the original (hooked) function (fapGm_Execute)

        // we can do whatever stuff we like... counting for example:
        i++;

        // return what our original function would've returned (in this case the return is obsolete since it is a void func)
        // And most importantly, since this is related to the frame output, call the original function at all because it may do
        // important stuff that would otherwise be skipped!

        return return_fapGm_Execute();     // hookFunction replaced this return_ function with a branch back to the original
                                           // function so that we can use it now
    }
}     // namespace mod