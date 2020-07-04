CC="g++"
FLAG="-O0 -mavx -fopenmp -ftree-vectorize -Wall -std=c++17"
BIN="bin"

rm -f $BIN/point-wise
rm -f $BIN/jacobi-tiling

# 核绑定
export OMP_PROC_BIND=true

$CC point-wise.cpp -o $BIN/point-wise $FLAG
$CC jacobi-tiling.cpp -o $BIN/jacobi-tiling $FLAG