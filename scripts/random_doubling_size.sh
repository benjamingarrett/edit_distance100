b=../dist/Debug/GNU-Linux
input_directory=../../misc_phd/input/lcss_instances
key_len=8
val_len=8
cuckooK=4
size=170
original_size=65536
prt=51200

#strategy=non_memo
#strategy=cuckoo_hashing
#strategy=linear_probe_hashing
first=$input_directory/p_0010_001
second=$input_directory/p_0010_001
#$b/edit_distance100 --first_pattern $first --second_pattern $second --caching_strategy $strategy --key_length $key_len --value_length $val_len

strategies=(
linear_probe_hashing
cuckoo_hashing
lru
nri_clock
nri_d_drunken
nru_clock_absolute
nru_d_drunken_absolute
nru_clock_relative
nru_d_drunken_relative
)

fname_list=(
$input_directory/r/10/random-10-0.lcss
$input_directory/r/20/random-20-0.lcss
$input_directory/r/40/random-40-0.lcss
$input_directory/r/80/random-80-0.lcss
$input_directory/r/160/random-160-0.lcss
$input_directory/r/320/random-320-0.lcss
$input_directory/r/640/random-640-0.lcss
$input_directory/r/1280/random-1280-0.lcss
)
#$input_directory/r/2560/random-2560-0.lcss
#$input_directory/r/5120/random-5120-0.lcss
#)

strategies=(${strategies[2]})

while [ 10 -lt $size ]
do

#echo $size
for strategy in  ${strategies[@]}
do
  #echo $strategy
  for pair in ${fname_list[3]}
  do
    #echo $pair
    $b/edit_distance100 --pattern_pair $pair --caching_strategy $strategy --cuckoo_k $cuckooK --key_length $key_len --value_length $val_len --cache_size $original_size --lru_queue_size $size --pattern_reference_threshold $prt
  done
done
size=$(( $size - 1 ))

done
