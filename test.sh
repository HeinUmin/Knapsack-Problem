# 物品数规模较小，背包容量数值不大的0/1背包问题
echo "Test Dataset A: f1_l-d_kp_10_269 (simple)"
./bin/bb -q data/low-dimensional/f1_l-d_kp_10_269 -o data/low-dimensional-optimum/f1_l-d_kp_10_269
./bin/bt -q data/low-dimensional/f1_l-d_kp_10_269 -o data/low-dimensional-optimum/f1_l-d_kp_10_269
./bin/dp -q data/low-dimensional/f1_l-d_kp_10_269 -o data/low-dimensional-optimum/f1_l-d_kp_10_269
./bin/dp_tuple -q data/low-dimensional/f1_l-d_kp_10_269 -o data/low-dimensional-optimum/f1_l-d_kp_10_269
# 物品数规模较小，背包容量数值较大的0/1背包问题
echo "Test Dataset B: p08 (large capacity)"
./bin/bb -n 24 -c data/FSU/p08_c.txt -v data/FSU/p08_p.txt -w data/FSU/p08_w.txt -s data/FSU/p08_s.txt
./bin/bt -n 24 -c data/FSU/p08_c.txt -v data/FSU/p08_p.txt -w data/FSU/p08_w.txt -s data/FSU/p08_s.txt
./bin/dp -n 24 -c data/FSU/p08_c.txt -v data/FSU/p08_p.txt -w data/FSU/p08_w.txt -s data/FSU/p08_s.txt
./bin/dp_tuple -n 24 -c data/FSU/p08_c.txt -v data/FSU/p08_p.txt -w data/FSU/p08_w.txt -s data/FSU/p08_s.txt
# 物品数规模较大的0/1背包问题
echo "Test Dataset A: knapPI_3_100_1000_1 (large scale)"
./bin/bt -q data/large_scale/knapPI_3_100_1000_1 -o data/large_scale-optimum/knapPI_3_100_1000_1
./bin/dp -q data/large_scale/knapPI_3_100_1000_1 -o data/large_scale-optimum/knapPI_3_100_1000_1
./bin/dp_tuple -q data/large_scale/knapPI_3_100_1000_1 -o data/large_scale-optimum/knapPI_3_100_1000_1
# 物品数规模极大的0/1背包问题
echo "Test Dataset A: knapPI_1_10000_1000_1 (extremely large scale)"
./bin/bt -q data/large_scale/knapPI_1_10000_1000_1 -o data/large_scale-optimum/knapPI_1_10000_1000_1
./bin/dp -q data/large_scale/knapPI_1_10000_1000_1 -o data/large_scale-optimum/knapPI_1_10000_1000_1
# 数值不为整数的0/1背包问题
echo "Test Dataset A: f5_l-d_kp_15_375 (non-integer)"
./bin/bb_double -q data/low-dimensional/f5_l-d_kp_15_375 -o data/low-dimensional-optimum/f5_l-d_kp_15_375
./bin/bt_double -q data/low-dimensional/f5_l-d_kp_15_375 -o data/low-dimensional-optimum/f5_l-d_kp_15_375
./bin/dp_tuple_double -q data/low-dimensional/f5_l-d_kp_15_375 -o data/low-dimensional-optimum/f5_l-d_kp_15_375
