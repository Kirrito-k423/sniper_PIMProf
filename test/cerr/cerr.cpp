// test.cpp
#include <iostream>
using namespace std;
int main()
{
	
    cout << "hello world---cout" << endl ;
	#if VERBOSE > 0
    cerr << "hello world---cerr" << endl ;
	#endif
    return 0;
}


// # shaojiemike @ snode6 in ~/github/sniper_PIMProf/test/cerr on git:dev x [16:13:30] 
// $ g++ cerr.cpp 

// # shaojiemike @ snode6 in ~/github/sniper_PIMProf/test/cerr on git:dev x [16:13:37] 
// $ ./a.out               
// hello world---cout

// # shaojiemike @ snode6 in ~/github/sniper_PIMProf/test/cerr on git:dev x [16:13:40] 
// $ g++ -DVERBOSE cerr.cpp

// # shaojiemike @ snode6 in ~/github/sniper_PIMProf/test/cerr on git:dev x [16:13:51] 
// $ ./a.out               
// hello world---cout
// hello world---cerr