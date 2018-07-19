
#include <unordered_map>
#include <mutex>

#include "../os.h"
#include "../../runpath/init.h"
#include "test_lib.h"
#include "../../../intercom-cpp/src/cominterop.h"
#include "../../../intercom-cpp/src/activator.h"

using intercom::Activator;


void InitializeRuntime()
{
    // Ensure the library "runpath" won't get optimized away.
    init_runpath();
}

void UninitializeRuntime()
{
}
