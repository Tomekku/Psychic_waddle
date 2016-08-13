#include "randoms.h"

Randoms::Randoms()
{

}

Randoms::Randoms(int i)
{
   for(int k = 0; k < i; ++k) {
       _numbers.push_back(k);
       std::cerr << "added " << k << std::endl;
   }
}

int Randoms::getNum(){
    if(_numbers.size() >0) {
        int position = rand()%_numbers.size();
        int result = _numbers[position];
        _numbers.erase(_numbers.begin()+position);
    std::cerr << "number returned " << result << std::endl;
        return result;
    }
    std::cerr << "no numbers " << std::endl;
    return MazeGenerator::NONE;
}

bool Randoms::haveNumbers()
{
    std::cerr << "checked " << (_numbers.size() > 0) << std::endl;
    return (_numbers.size() > 0);
}
