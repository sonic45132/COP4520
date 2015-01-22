#include <mutex>
#include <thread>
#include <iostream>

const char* BoolToString(bool b)
{
  return b ? "true" : "false";
}

int calc_primes(bool* nums)
{
  for(int i = 3; i < 50001; i++)
  {
    bool isPrime = true;
    for(int j = 2; j < i; j++)
    {
      if(i%j == 0)
      {
        isPrime = false;
        break;
      }
    }
    nums[i] = isPrime;
  }
}

void print_results(bool* nums) 
{
  std::cout << "1 : true" << std::endl;
  std::cout << "2 : true" << std::endl;
  for(int i=3;i<50001;i++)
  {
    std::cout << i << " : " << BoolToString(nums[i]) << std::endl;
  }
}

int main() 
{
  bool nums[50000] = {0};
  calc_primes(nums);
  print_results(nums);
  //std::mutex mutexs[5000];

  // std::thread t[4];
  // for (int i = 0; i < 1; i++) {
  //     t[i] = std::thread(calc_primes, nums);
  // }

  // for (int i = 0; i < 4; i++) 
  // {
  //   t[i].join();
  // }

  return 0;
}