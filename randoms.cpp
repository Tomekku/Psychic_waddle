#include "randoms.h"

Randoms::Randoms()
{

}

Randoms::Randoms(int i)
{
   for(int k = 0; k < i; ++k) {
       nums.push_back(k);
       std::cerr << "added " << k << std::endl;
   }
}

int Randoms::getNum(){
    if(nums.size() >0) {
        int pos = rand()%nums.size();
        int ret = nums[pos];
        nums.erase(nums.begin()+pos);
    std::cerr << "number returned " << ret << std::endl;
        return ret;
    }
    std::cerr << "no numbers YO " << std::endl;
    return MazeGenerator::dir_none;
}

bool Randoms::haveNumbers()
{
    std::cerr << "checked " << (nums.size() > 0) << std::endl;
    return (nums.size() > 0);
}
