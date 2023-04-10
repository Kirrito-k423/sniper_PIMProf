include ../buildconf.makefile

CXX = /usr/bin/clang++-10
PIMPROF_ROOT = /staff/shaojiemike/github/PIMProf

#ifndef PIMPROF_DIR
#$(error PIMPROF_DIR is not set in Makefile.config)
#endif

DECISION            := decision.out
TEST_OBJ            := test.o # print4.o pthreads.o
TEST_SO             := libtest.so
TEST_EXE            := test.exe
TEST_PY             := test.py

TEST_OBJ_2          := test.o.2 print4.o.2 pthreads.o.2
TEST_EXE_2          := test.exe.2

CXXFLAGS := -fPIC -std=c++11 -g -O3 -fopenmp -I$(PIMPROF_ROOT)/LLVMAnalysis
# CXX_INJ_FLAGS = $(CXXFLAGS) $(SNIPER_CFLAGS) -Xclang -load -Xclang $(PIMPROF_ROOT)/build/LLVMAnalysis/libAnnotationInjection.so
# CXX_OFF_FLAGS += $(CXXFLAGS) $(SNIPER_CFLAGS) -Xclang -load -Xclang $(PIMPROF_ROOT)/build/LLVMAnalysis/libOffloaderInjection.so 

CXX_INJ_FLAGS = $(CXXFLAGS) $(SNIPER_CFLAGS) -Xclang -load -Xclang $(PIMPROF_ROOT)/debug/LLVMAnalysis/libAnnotationInjection.so
CXX_OFF_FLAGS += $(CXXFLAGS) $(SNIPER_CFLAGS) -Xclang -load -Xclang $(PIMPROF_ROOT)/debug/LLVMAnalysis/libOffloaderInjection.so 

test.inj: test.cpp # print4.cpp pthreads.cpp
	export PIMPROFINJECTMODE=SNIPER && $(CXX) $(CXX_INJ_FLAGS) -o $@ $^ -pthread

test.inj2: test.cpp # print4.cpp pthreads.cpp
	export PIMPROFINJECTMODE=SNIPER2 && $(CXX) $(CXX_INJ_FLAGS) -o $@ $^ -pthread

test.pim: test.cpp # print4.cpp pthreads.cpp
	export PIMPROFDECISION=mpkidecision.out && export PIMPROFROI=PIMONLY && export PIMPROFINJECTMODE=SNIPER && clang++-7 $(CXX_OFF_FLAGS) -o $@ $^ -pthread > test.dump

clean:
	rm -rf *.inj *.pim inj_cpu inj_pim off_cpu off_pim mpkidecision.out reusedecision.out

.PHONY: all offload clean
