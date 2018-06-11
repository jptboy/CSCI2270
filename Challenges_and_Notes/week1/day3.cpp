#include <iostream>
#include <math.h>
int main(int argc, char const *argv[])
{

    /*
        argc is the number of arguments
        argv is the array of arguments
    */
    std::cout
        <<"Number of arguments: "
        << argc
        << std::endl;

    for(int i=0; i<argc;i++)
    {
        std::cout 
            << "Argument: "
            << argv[i]
            << std::endl;
    }
    
    int m=5;

    int *p = &m;
    std::cout
        << *p
        << std::endl;

    *p=6;

    std::cout
        << *p
        << std::endl;

    return 0;
}
