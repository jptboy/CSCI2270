#include <iostream>

class Primes
{
    public:

        Primes(){};
        static bool isPrime(int num)
        {
            if (num==0 || num==1)
                return false;//0 and 1 are not prime numbers
            for(int i=2; i<num; i++)
            {
                if(num%i==0)
                {
                    return false;
                }
            }

            return true;//return true if 0 not achieved when iterating through num%i
        }
};

int main()
{
    std::cout << "Enter a number!" << std::endl;
    int x = 0;
    std::cin >> x;
    
    Primes newPrimeChecker;
    
    if(newPrimeChecker.isPrime(x)==true)
        std::cout << x << " is a prime number."  << std::endl;
    else
        std::cout << x << " is not a prime number."  << std::endl;
    return 0;
}