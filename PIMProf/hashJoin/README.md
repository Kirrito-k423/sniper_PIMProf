# Database-Relation-Join-Algorithms

Sort Merge Join and Hash Join algorithm for natural join of two database relations

## run

```bash
./hashjoin.inj checker/R.file checker/S.file hash 40
```

### problem

原本的程序不支持并行加速，不是并行的代码

```bash
# shaojiemike @ snode6 in ~/github/sniper_PIMProf/PIMProf/hashJoin on git:dev x [14:44:58]
$ export OMP_NUM_THREADS=1 && time ./hashjoin.inj checker/R.file checker/S.file hash 40


MM : 40
TB : 100
R.T : 10000
R.B : 100
S.T : 10000
S.B : 100
out_hash.txt
done
./hashjoin.inj checker/R.file checker/S.file hash 40  0.11s user 0.03s system 55% cpu 0.250 total

# shaojiemike @ snode6 in ~/github/sniper_PIMProf/PIMProf/hashJoin on git:dev x [15:17:00]
$ export OMP_NUM_THREADS=32 && time ./hashjoin.inj checker/R.file checker/S.file hash 40
MM : 40
TB : 100
R.T : 10000
R.B : 100
S.T : 10000
S.B : 100
out_hash.txt
done
./hashjoin.inj checker/R.file checker/S.file hash 40  0.13s user 0.01s system 66% cpu 0.208 total
```