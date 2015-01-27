#include <cmath>
#include <iostream>

#define MAX 100000000

const char* BoolToString(bool b)
{
  return b ? "true" : "false";
}

int calc_primes(char* nums)
{
  for(int i = 3; i < MAX; i++)
  {
    if(i%2==0)
      continue;

    bool isPrime = true;
    for(int j = 3; j < sqrt(i); j+=2)
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

void print_results(char* nums) 
{
  std::cout << "1 : true" << std::endl;
  std::cout << "2 : true" << std::endl;
  for(int i=3;i<MAX;i++)
  {
    std::cout << i << " : " << BoolToString(nums[i]) << std::endl;
  }
}

void print_primes(char* nums)
{
  for(int i=0;i<MAX;i++)
  {
    if(nums[i])
    {
      std::cout << i << std::endl;
    }
  }
}

int main() 
{
  std::cout << "Finding primes <= " << MAX << std::endl;
  char* nums = new char[MAX];
  calc_primes(nums);
  print_primes(nums);
  //print_results(nums);
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