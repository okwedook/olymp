#include "base_template.h"
#include "custom_io.h"
#include "debugger.h"

signed main() {
    initIO();

    #ifdef DEBUG
        cerr << "Runtime is: " << clock() * 1.0 / CLOCKS_PER_SEC << endl;
    #endif
    return 0;
}
