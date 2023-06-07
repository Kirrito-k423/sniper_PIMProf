# SVM-RFE - Support Vector Machine based gene classification application

from NU-MineBench

## File Structure

* src - containing all the source files of the applications
* datasets - contains all the data sets for each application                                   (subdirectory structure is the same as src)

### SVM-RFE

SVM-RFE [12], or Support Vector Machines - Recursive
Feature Elimination, is a feature selection method. SVMRFE is used extensively in disease finding (gene expression
problem). The selection is obtained by a recursive feature elimination process - at each RFE step, a gene is discarded from the
active variables of a SVM classification model, according to
some support criteria. Vector multiplication is the computation
intensive kernel of SVM-RFE, and data parallelism, using
OpenMP, is utilized to parallelize the algorithm

uses a benchmark microarray data set on ovarian cancer.
This dataset contains 253 (tissue samples) x 15154 (genes)
expression values, including 91 control and 162 ovarian cancer
tissues with early stage cancer samples

## Installation

```bash
SVM-RFE:                                                                                      
cd $DMHOME/src/SVM-RFE/svm_rfe                                                                
make -f makefile.omp     
```

## Run

dataset from http://cucis.ece.northwestern.edu/projects/DMS/DATASETS/SVM-RFE.tar.gz

```bash
./svm.inj ./SVM-RFE/outData.txt 253 15154 4

# shaojiemike @ snode6 in ~/github/sniper_PIMProf/PIMProf/svm on git:dev x [16:02:26]
$ export OMP_NUM_THREADS=32 && time ./svm.inj ./SVM-RFE/outData.txt 253 15154 4
Reading data set time: 1.18s
Remains(15154), time(0.24s), Deleted(4011)
Remains(15153), time(0.20s), Deleted(14260)
Remains(15152), time(0.15s), Deleted(5080)
Remains(15151), time(0.14s), Deleted(8490)
SVM Training time: 0.861605s
Data prepare + SVM Training time: 1.12s
./svm.inj ./SVM-RFE/outData.txt 253 15154 4  28.42s user 0.28s system 1239% cpu 2.316 total

# shaojiemike @ snode6 in ~/github/sniper_PIMProf/PIMProf/svm on git:dev x [16:02:43]
$ export OMP_NUM_THREADS=1 && time ./svm.inj ./SVM-RFE/outData.txt 253 15154 4
Reading data set time: 1.17s
Remains(15154), time(0.65s), Deleted(4011)
Remains(15153), time(0.58s), Deleted(14260)
Remains(15152), time(0.58s), Deleted(5080)
Remains(15151), time(0.58s), Deleted(8490)
SVM Training time: 2.98766s
Data prepare + SVM Training time: 3.25s
./svm.inj ./SVM-RFE/outData.txt 253 15154 4  4.39s user 0.04s system 99% cpu 4.436 total
```
