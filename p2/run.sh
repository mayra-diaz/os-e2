gcc generate_test.c
a.out
rm a.out
#make fifo
#make scan
#make cscan
./fifo test.txt > result_fifo_test.txt
./scan test.txt > result_scan_test.txt
./cscan test.txt > result_cscan_test.txt
