#!/usr/bin/bash

set -e

# global variables
DEBUG=1
echo "PWD is ${PWD}"
graph_name=road
pre_graph=${PWD}/benchmark/$graph_name.sg
folder=('rawRun' $graph_name)
program_prefix=('bc' )
program_prefix=('bc' 'bfs' 'cc' 'pr')
# TIPS:  'sssp' need road.wsg file

suffix='.inj'

# general settings
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color
if [[ "$DEBUG" == '1' ]]; then
	MSG="echo -e "
else
	MSG='false'
fi

# generate folder we need
for i in "${folder[@]}"; do
    mkdir -p $i
done

# Run the benchmark raw time
for i in "${program_prefix[@]}"; do
    PROGRAM="${PWD}/${i}${suffix}"
	COMMAND="$PROGRAM -f ${pre_graph} -n1"
    echo -e "${YELLOW}COMMAND${NC} is \n$COMMAND"
    OUTPUT=`$COMMAND`
	echo "${OUTPUT}" > ./${graph_name}/${i}_rawTime.log
	$MSG "${GREEN}OUTPUT${NC} is \n$OUTPUT"
done

# Special for sssp
i=sssp
PROGRAM="${PWD}/${i}${suffix}"
COMMAND="$PROGRAM -f ${PWD}/benchmark/$graph_name.wsg -n1"
echo -e "${YELLOW}COMMAND${NC} is \n$COMMAND"
OUTPUT=`$COMMAND`
echo "${OUTPUT}" > ./${graph_name}/${i}_rawTime.log
$MSG "${GREEN}OUTPUT${NC} is \n$OUTPUT"

# Run run-sniper 
# export OMP_NUM_THREADS=32 && ../../run-sniper --roi -n 32 -c pimprof_pim -d bfs_pimprof_pim_32 -- ./bfs.inj -f ./benchmark/kron.sg -n1 &
# export OMP_NUM_THREADS=1 && ../../run-sniper --roi -n 1 -c pimprof_cpu -d bfs_pimprof_cpu_1 -- ./bfs.inj -f ./benchmark/kron.sg -n1
for i in "${program_prefix[@]}"; do
    PROGRAM="${PWD}/${i}${suffix}"
	export OMP_NUM_THREADS=32;
	COMMAND="time ../../run-sniper --roi -n 32 -c pimprof_pim -d ${graph_name}/${i}_pimprof_pim_32 -- $PROGRAM -f ${pre_graph} -n1 2>&1 "
	$MSG "OMP_NUM_THREADS = $OMP_NUM_THREADS"
    echo -e "${YELLOW}COMMAND${NC} is \n$COMMAND"
    OUTPUT=`${COMMAND}`
	echo "${OUTPUT}" > ./${graph_name}/${i}_pim_32.log
	$MSG "${GREEN}OUTPUT${NC} is \n$OUTPUT"

	export OMP_NUM_THREADS=1;
	COMMAND="time ../../run-sniper --roi -n 1 -c pimprof_cpu -d ${graph_name}/${i}_pimprof_cpu_1 -- $PROGRAM -f ${pre_graph} -n1 2>&1 "
	$MSG "OMP_NUM_THREADS = $OMP_NUM_THREADS"
    echo -e "${YELLOW}COMMAND${NC} is \n$COMMAND"
    OUTPUT=`$COMMAND`
	echo "${OUTPUT}" > ./${graph_name}/${i}_cpu_1.log
	$MSG "${GREEN}OUTPUT${NC} is \n$OUTPUT"
done

# Special for sssp
i=sssp
PROGRAM="${PWD}/${i}${suffix}"
export OMP_NUM_THREADS=32;
COMMAND="time ../../run-sniper --roi -n 32 -c pimprof_pim -d ${graph_name}/${i}_pimprof_pim_32 -- $PROGRAM -f ${PWD}/benchmark/$graph_name.wsg -n1 2>&1 "
$MSG "OMP_NUM_THREADS = $OMP_NUM_THREADS"
echo -e "${YELLOW}COMMAND${NC} is \n$COMMAND"
OUTPUT=`${COMMAND}`
echo "${OUTPUT}" > ./${graph_name}/${i}_pim_32.log
$MSG "${GREEN}OUTPUT${NC} is \n$OUTPUT"

export OMP_NUM_THREADS=1;
COMMAND="time ../../run-sniper --roi -n 1 -c pimprof_cpu -d ${graph_name}/${i}_pimprof_cpu_1 -- $PROGRAM -f ${PWD}/benchmark/$graph_name.wsg -n1 2>&1 "
$MSG "OMP_NUM_THREADS = $OMP_NUM_THREADS"
echo -e "${YELLOW}COMMAND${NC} is \n$COMMAND"
OUTPUT=`$COMMAND`
echo "${OUTPUT}" > ./${graph_name}/${i}_cpu_1.log
$MSG "${GREEN}OUTPUT${NC} is \n$OUTPUT"