./bin/bb -q test/low-dimensional/f1_l-d_kp_10_269 -o test/low-dimensional-optimum/f1_l-d_kp_10_269
./bin/bt -q test/low-dimensional/f1_l-d_kp_10_269 -o test/low-dimensional-optimum/f1_l-d_kp_10_269
./bin/dp -q test/low-dimensional/f1_l-d_kp_10_269 -o test/low-dimensional-optimum/f1_l-d_kp_10_269
./bin/bb -n 10 -c test/FSU/p01_c.txt -v test/FSU/p01_p.txt -w test/FSU/p01_w.txt -s test/FSU/p01_s.txt
./bin/bt -n 10 -c test/FSU/p01_c.txt -v test/FSU/p01_p.txt -w test/FSU/p01_w.txt -s test/FSU/p01_s.txt
./bin/dp -n 10 -c test/FSU/p01_c.txt -v test/FSU/p01_p.txt -w test/FSU/p01_w.txt -s test/FSU/p01_s.txt