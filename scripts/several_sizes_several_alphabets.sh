b=../dist/Debug/GNU-Linux
input_directory=../../misc_phd/input/lcss_instances
key_len=8
val_len=8
cuckooK=4
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
#fname_list=(
#$input_directory/r/40/random-40-0.lcss
#$input_directory/r/40/random-40-1.lcss
#$input_directory/r/40/random-40-2.lcss
#)

#fname_list=(
#$input_directory/r/80/random-80-0.lcss
#$input_directory/r/80/random-80-1.lcss
#$input_directory/r/80/random-80-2.lcss
#)

#fname_list=(
#$input_directory/r/160/random-160-0.lcss
#$input_directory/r/160/random-160-1.lcss
#$input_directory/r/160/random-160-2.lcss
#)

#fname_list=(
#$input_directory/r/320/random-320-0.lcss
#$input_directory/r/320/random-320-1.lcss
#$input_directory/r/320/random-320-2.lcss
#)

#fname_list=(
#$input_directory/t/test-40-000-111.lcss
#$input_directory/t/test-80-000-111.lcss
#$input_directory/t/test-160-000-111.lcss
#$input_directory/t/test-40-111-111.lcss
#$input_directory/t/test-80-111-111.lcss
#$input_directory/t/test-160-111-111.lcss
#)

fname_list=(
$input_directory/t/test-40-012-210.lcss
$input_directory/t/test-80-012-210.lcss
$input_directory/t/test-160-012-210.lcss
)

#fname_list=(
#$input_directory/t/test-80-0101-1010.lcss
#)

strategies=(${strategies[2]})

size=163
j=1
while [ $j -lt 3 ]
do

  pair=${fname_list[$j]}
  echo $pair
  while [ 10 -lt $size ]
  do

    #echo $size
    for strategy in  ${strategies[@]}
    do
      #echo $strategy        
      $b/edit_distance100 --pattern_pair $pair --caching_strategy $strategy --cuckoo_k $cuckooK --key_length $key_len --value_length $val_len --cache_size $original_size --lru_queue_size $size --pattern_reference_threshold $prt
    done
    size=$(( $size - 1 ))
    #break

  done
  j=$(( $j + 1 ))

done
