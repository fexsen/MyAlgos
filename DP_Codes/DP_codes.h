#ifndef DP_CODES_H
#define DP_CODES_H
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

class DPcodes 
{

private:
    std::ofstream f;
    char* fname; 
    int N;
    int n;
    int t;
    std::vector<std::vector<bool>> codes;
    std::vector<std::vector<bool>> dpc; 
public:
    DPcodes(int N_in, int n_in, int t_in, char* fname_in);
    DPcodes(int n_in, int t_in, char* fname_in);
    DPcodes(const DPcodes& dc);
    ~DPcodes();
    inline int HammingDistance(std::vector<bool> codef, std::vector<bool> codesec);
    inline bool HammAllPrev(int pos, std::vector<bool> code);
    inline std::vector<bool> DecToBin(int num);
    inline std::vector<bool> IncBin(const std::vector<bool> code);
    void FillTheCodeset();
    void Compose(DPcodes cd1, DPcodes cd2);
    void CodesSet();
    void DPrint();

};

#endif // DP_CODES_H