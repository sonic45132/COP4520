#include <mutex>
#include <cmath>
#include <atomic>
#include <thread>
#include <vector>
#include <iostream>

#define MAX 100000000

char* nums;
std::atomic_char mux[MAX] = {};
//std::atomic<char> test = 0;
//std::atomic<char> taken = 1;

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
  char expected = (char)0;
  //std::cout << "Hi!" << std::endl;
  for(int i = 3; i < MAX; i++)
  {
    if(i%2==0)
      continue;

    if(mux[i].compare_exchange_strong(expected,(char)1))
    {
      //std::cout << "Thread " << id << ": working on " << i << std::endl;
      //std::cout << "Thread " << id << " got lock on " << i << std::endl;
      if(nums[i] != 2) 
      {
        //std::cout << "Thread " << id << ": " << i << " taken" << std::endl;
        continue;
      }

      nums[i] = isPrime(i);
      expected = (char)0;
      // for(int  j = 0; j < MAX/i; j++) {
      //   int mult = j*i;
      //   std::unique_lock<std::mutex> lck(mux[mult],std::defer_lock);
      //   if(lck.try_lock())
      //   {
      //     nums[mult] = 0;
      //     lck.unlock();
      //   }
      //   else
      //   {
      //     //std::cout <<"Thread " << id << ": Lock 2 failed" << std::endl;
      //     continue;
      //   }
      // }
    }
  }
}

const char* BoolToString(bool b)
{
  return b ? "true" : "false";
}

void print_results() 
{
  std::cout << "1" << std::endl;
  std::cout << "2" << std::endl;
  for(int i=3;i<MAX;i++)
  {
    if(nums[i])
      std::cout << i << std::endl;
  }
}

void print_mux()
{
  for(int i=0;i<MAX;i++)
  {
    std::cout << i << " : " << (int)mux[i] << std::endl;
  }
}

int main(int argc, char* argv[]) 
{
  nums = new char[MAX];
  std::fill_n(nums, MAX, 2);

  int num_threads;
  if(argc < 2)
    num_threads = 4;
  else
    num_threads = atoi(argv[1]);

  std::cout << num_threads << " threads" << std::endl;
  std::cout << "Finding primes <= " << MAX << std::endl;

  std::vector<std::thread> threads;
  for (int i = 0; i < num_threads; i++) {
      threads.emplace_back(calc_primes, i);
  }

  for (auto &thread : threads) thread.join();

  //print_mux();
  //print_results();

  return 0;
}