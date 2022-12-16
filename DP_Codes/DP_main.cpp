#include "DP_codes.h"

/*

"A code of integers into binary sequences is called a 
difference-preserving code (DP code) if it has the following two properties: 1) if the absolute value of the difference between two integers is less
than or equal to a certain threshold, the Hamming distance between their
codewords is equal to this value and 2) if the absolute value of the difference between two integers exceeds the threshold, then the Hamming
distance between their codewords also exceeds this threshold. Such codes
(or slight modifications thereof) have also been called path codes, circuit
codes, or snake-in-the-box codes." 
                                    (c) F. Preparata and J. Nievergelt, “Difference-preserving codes,” IEEE Transactions on Information Theory, vol. 20, no. 5, pp. 643–649, 1974. 

*/

int main(int argc, char** argv)
{
    std::fstream f;
    f.open(argv[4], std::ofstream::out);
    f.close();
    int N = atoi(argv[1]);
    int n = atoi(argv[2]);
    int t = atoi(argv[3]);
    if(n > 6){
       DPcodes cds(n, t, argv[4]);
       cds.CodesSet();
       cds.DPrint();
       return 0;
    }
    DPcodes cds(N, n, t, argv[4]);
    cds.CodesSet();
    cds.DPrint();
    return 0;
}