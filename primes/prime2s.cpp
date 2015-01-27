#include <cmath>
#include <ctime>
#include <atomic>
#include <thread>
#include <vector>
#include <iostream>

#define MAX 100000000

char* nums;
std::atomic<int> counter;

int isPrime(int num) 
{
  int prime = 1;
  for(int i = 3; i < sqrt(num); i+=2)
  {
    if(num%i == 0)
    {
      prime = 0;
      break;
    }
  } 
  return prime;
}

void calc_primes(int id)
{
  //std::cout << "Hi!" << std::endl;
  int i = 0;
  while(i < MAX)
  {
    i = counter.fetch_add(1);
    if(i%2==0)
      continue;
      
    if(nums[i] != 2) 
    {
      continue;
    }

    nums[i] = isPrime(i);
  }
}

void print_results() 
{
  int counter = 0, sum = 3;
  for(int i = 0; i < MAX; i++)
  {
    if(nums[i] == 1)
      counter++;
  }
  std::cout << counter << std::endl;
  for(int i = 3; i < MAX; i+=2)
  {
    if(nums[i] == 1)
      sum += i;
  }
  std::cout << sum << std::endl;

  std::vector<int> top;
  int num = 0;

  for(int i = MAX-1; num < 10; i--)
  {
    if(nums[i] == 1)
    {
      //std::cout << "Is prime :" << i << std::endl;
      top.insert(top.begin(),i);
      num++;
    }
  }

  for (std::vector<int>::iterator it = top.begin(); it != top.end(); ++it)
  {
    std::cout << *it << std::endl;
  }

}

int main(int argc, char* argv[]) 
{
  clock_t start = clock();
  
  nums = new char[MAX];
  std::fill_n(nums, MAX, 2);
  
  int num_threads;
  if(argc < 2)
    num_threads = 4;
  else
    num_threads = atoi(argv[1]);

  std::vector<std::thread> threads;
  for (int i = 0; i < num_threads; i++) {
      threads.emplace_back(calc_primes, i);
  }

  for (auto &thread : threads) thread.join();

  clock_t stop = clock();
  std::cout << (stop - start)/(double)CLOCKS_PER_SEC << std::endl;
  print_results();
  return 0;
}