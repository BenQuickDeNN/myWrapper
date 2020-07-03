CC="g++"
FLAG="-O0 -mavx -fopenmp -ftree-vectorize -Wall -std=c++17"
BIN="bin"

rm -f $BIN/point-wise
$CC point-wise.cpp -o $BIN/point-wise $FLAG