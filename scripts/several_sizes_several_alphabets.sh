b=../dist/Debug/GNU-Linux
input_directory=../../misc_phd/input/lcs_instances
fname=edit_distance_aggregate_results.csv
key_len=8
val_len=8
cuckooK=4
original_size=65536
prt=51200

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

types=(
test-000-111
test-012-210
test-0101-1010
test-111-111
random-0-1
random-0-9
random-0-19
test-000111-111000
test-001122-221100
test-001122-112200
)

sizes=(
40
80
)

k=0
for (( i=0; i<${#sizes[@]}; i++ ));
do
  for (( j=0; j<${#types[@]}; j++ ));
  do
    instances[k]=${sizes[i]}-${types[j]}
    k=$(( $k + 1 ))
  done
done
k=0
for (( i=0; i<${#instances[@]}; i++ ));
do
  fnames[k]=$input_directory/${instances[i]}.lcs
  k=$(( $k + 1 ))
done
strategies=(${strategies[2]})

type=0
while [ $type -le 9 ]
do
  pair=${fnames[type]}
  instance=${instances[type]}

done


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
