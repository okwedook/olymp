#include "base_template.hpp"
#include "custom_io.hpp"
#include "debugger.hpp"

signed main() {
    initIO();

    #ifdef DEBUG
        cerr << "Runtime is: " << clock() * 1.0 / CLOCKS_PER_SEC << endl;
    #endif
    return 0;
}
