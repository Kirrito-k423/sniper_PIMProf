include ../buildconf.makefile

CXX = /usr/bin/clang++-10
CC=/usr/bin/clang-10
PIMPROF_ROOT = /staff/shaojiemike/github/PIMProf
PIMPROF_MODE = debug
SNIPER_ROOT ?= /staff/shaojiemike/github/sniper_PIMProf/
SNIPER_CFLAGS:=-mno-sse4 -mno-sse4.1 -mno-sse4.2 -mno-sse4a -mno-avx -mno-avx2 -I${SNIPER_ROOT}/include

CXX_FLAGS = -std=c++14 -O3 -Wall -fopenmp -g -I$(PIMPROF_ROOT)/LLVMAnalysis
CC_FLAGS = -std=c99 -O3 -Wall -fopenmp -g -I$(PIMPROF_ROOT)/LLVMAnalysis
CXX_INJ_FLAGS = $(CXX_FLAGS) -Xclang -load -Xclang $(PIMPROF_ROOT)/$(PIMPROF_MODE)/LLVMAnalysis/libAnnotationInjection.so
CC_INJ_FLAGS = $(CC_FLAGS) -Xclang -load -Xclang $(PIMPROF_ROOT)/$(PIMPROF_MODE)/LLVMAnalysis/libAnnotationInjection.so

# SRC_DIR = src
SRCS = mlp_openmp.c
KERNELS = mlp

inj: $(KERNELS:=.inj)

%.inj: ${SRCS}
	export PIMPROFINJECTMODE=SNIPER && $(CC) $(CC_INJ_FLAGS) $(SNIPER_CFLAGS) -o $@ $^ $(LD_FLAGS) > $(@:.inj=.inj.dump) 2>&1

clean:
	rm -f $(KERNELS) *.inj *.inj2 *.pim *.pim.dump *.vtune *.vtune.dump *.ll

# all:
# 	gcc mlp_openmp.c -o mlp_openmp -fopenmp -std=c99
# run:
# 	./mlp_openmp
