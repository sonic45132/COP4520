all: primes primes-nlck primes-cnt primes-seq

primes:
	g++ -std=c++11 -pthread primes.cpp -o bin/primes

primes-nlck:
	g++ -std=c++11 -pthread primes-no-locks.cpp -o bin/primes-nlcks

primes-cnt:
	g++ -std=c++11 -pthread primes-cnt.cpp -o bin/primes-cnt

primes-seq:
	g++ -std=c++11 primes_seq.cpp -o bin/primes-seq