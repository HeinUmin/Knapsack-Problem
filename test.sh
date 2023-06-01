# 规模较少，数值不大的0/1背包问题
echo "Test Dataset A: f1_l-d_kp_10_269 (simple)"
./bin/bb -q test/low-dimensional/f1_l-d_kp_10_269 -o test/low-dimensional-optimum/f1_l-d_kp_10_269
./bin/bt -q test/low-dimensional/f1_l-d_kp_10_269 -o test/low-dimensional-optimum/f1_l-d_kp_10_269
./bin/dp -q test/low-dimensional/f1_l-d_kp_10_269 -o test/low-dimensional-optimum/f1_l-d_kp_10_269
./bin/dp_tuple -q test/low-dimensional/f1_l-d_kp_10_269 -o test/low-dimensional-optimum/f1_l-d_kp_10_269
# 规模较少，数值较大的0/1背包问题
echo "Test Dataset B: p08 (large capacity)"
./bin/bb -n 24 -c test/FSU/p08_c.txt -v test/FSU/p08_p.txt -w test/FSU/p08_w.txt -s test/FSU/p08_s.txt
./bin/bt -n 24 -c test/FSU/p08_c.txt -v test/FSU/p08_p.txt -w test/FSU/p08_w.txt -s test/FSU/p08_s.txt
./bin/dp -n 24 -c test/FSU/p08_c.txt -v test/FSU/p08_p.txt -w test/FSU/p08_w.txt -s test/FSU/p08_s.txt
./bin/dp_tuple -n 24 -c test/FSU/p08_c.txt -v test/FSU/p08_p.txt -w test/FSU/p08_w.txt -s test/FSU/p08_s.txt
# 规模较大的0/1背包问题
echo "Test Dataset A: knapPI_3_100_1000_1 (large scale)"
./bin/bt -q test/large_scale/knapPI_3_100_1000_1 -o test/large_scale-optimum/knapPI_3_100_1000_1
./bin/dp -q test/large_scale/knapPI_3_100_1000_1 -o test/large_scale-optimum/knapPI_3_100_1000_1
./bin/dp_tuple -q test/large_scale/knapPI_3_100_1000_1 -o test/large_scale-optimum/knapPI_3_100_1000_1
# 规模极大的0/1背包问题
echo "Test Dataset A: knapPI_1_10000_1000_1 (extremely large scale)"
./bin/bt -q test/large_scale/knapPI_1_10000_1000_1 -o test/large_scale-optimum/knapPI_1_10000_1000_1
./bin/dp -q test/large_scale/knapPI_1_10000_1000_1 -o test/large_scale-optimum/knapPI_1_10000_1000_1
# 数值不为整数的0/1背包问题
echo "Test Dataset A: f5_l-d_kp_15_375 (non-integer)"
./bin/bb_double -q test/low-dimensional/f5_l-d_kp_15_375 -o test/low-dimensional-optimum/f5_l-d_kp_15_375
./bin/bt_double -q test/low-dimensional/f5_l-d_kp_15_375 -o test/low-dimensional-optimum/f5_l-d_kp_15_375
./bin/dp_tuple_double -q test/low-dimensional/f5_l-d_kp_15_375 -o test/low-dimensional-optimum/f5_l-d_kp_15_375
