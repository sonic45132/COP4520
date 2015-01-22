start_time=`date +%s`
./primes 4
end_time=`date +%s`
echo execution time was `expr $end_time - $start_time` s.