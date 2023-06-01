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
./svm.inj ./SVM-RFE/outData.txt 253 15154 20
```
