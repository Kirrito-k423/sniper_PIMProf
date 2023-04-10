SOLVER=/staff/shaojiemike/github/PIMProf/debug/PIMProfSolver/Solver.exe

export OMP_NUM_THREADS=1 && ../../run-sniper --roi -n 1 -c pimprof_cpu -d inj_cpu -- ./test.inj
export OMP_NUM_THREADS=4 && ../../run-sniper --roi -n 4 -c pimprof_pim -d inj_pim -- ./test.inj
${SOLVER} mpki -c inj_cpu/pimprofstats.out -p inj_pim/pimprofstats.out -r inj_cpu/pimprofreuse.out -o mpkidecision.out
${SOLVER} reuse -c inj_cpu/pimprofstats.out -p inj_pim/pimprofstats.out -r inj_cpu/pimprofreuse.out -o reusedecision.out
