#include <iostream>
#include <ExcursionLibrary.h>

int main()
{
    const FCLayer layer1(2, 2);

    std::cout << "Layer 1 weights:" << std::endl << layer1.weights <<std::endl;
    std::cout << "Layer 1 biases:" << std::endl <<layer1.biases << std::endl;
    
    std::cout << "Press enter to exit..." << std::endl;
    std::cin.get();
    
    return 0;
}
