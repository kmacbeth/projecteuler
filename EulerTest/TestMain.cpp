/**
 * Test executable.
 */
#include "TestApp.h"

/**
 * Run tests on the libraries
 */
int main(int argc, char * argv[])
{
    TestApp::TCmdLine cmdline(argv, argv + argc);
    TestApp app;

    if (app.ParseArgs(cmdline))
    {
        return !app.Run();
    }

    return 1;
}