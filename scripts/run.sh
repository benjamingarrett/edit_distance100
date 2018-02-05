b=../dist/Debug/GNU-Linux
input_directory=../../misc_phd/input/lcss_instances
key_len=8
val_len=8
cuckooK=4
strategy=nri_clock
pair=$input_directory/r/40/random-40-0.lcss
$b/edit_distance100 --pattern_pair $pair --caching_strategy $strategy --cuckoo_k $cuckooK --key_length $key_len --value_length $val_len
gprof $b/edit_distance100 gmon.out > analysis.txt
