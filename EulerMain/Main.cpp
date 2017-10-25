#include "Solutions.h"
#include "Libs/Euler.h"
#include "Libs/Timer.h"

int main(int argc, char * argv[])
{
    Solutions solutions;
    Solutions::TCmdLine cmdLine(argv, argv + argc);

    if (solutions.ParseArgs(cmdLine))
    {
        // Run a solution
        solutions.Run();
    }

    return 0;
}