#include "DP_codes.h"

    DPcodes::DPcodes(int N_in, int n_in, int t_in, char* fname_in) : N(N_in), n(n_in), t(t_in), fname(fname_in) {
        f.open(fname, std::ofstream::app);
        dpc.resize(N);
        codes.resize(pow(2, n));
    }
    DPcodes::DPcodes(int n_in, int t_in, char* fname_in) : n(n_in), t(t_in), fname(fname_in) {
        f.open(fname, std::ofstream::app);
        codes.resize(pow(2, n));
    }
    DPcodes::DPcodes(const DPcodes& dc){
        f.open(fname, std::ofstream::app);
        N = dc.N;
        n = dc.n;
        t = dc.t;
        dpc.resize(N);
        dpc = dc.dpc;
    }
    DPcodes::~DPcodes() {
        f.close();
    }

    inline int DPcodes::HammingDistance(std::vector<bool> codef, std::vector<bool> codesec)
    {
        int cnt = 0;
        for(int i = 0; i < n; i++){
            if(codef[i] != codesec[i]){
                cnt++;
            }
        }
        return cnt;
    }

    inline bool DPcodes::HammAllPrev(int pos, std::vector<bool> code)
    {
        for(int i = pos-1; i >= 0; i--){
            if(!(HammingDistance(code, dpc[i]) == abs(i-pos) && abs(i-pos) <= t || abs(i-pos) > t && HammingDistance(code, dpc[i]) > t)){
                return false;
            }
        }
        return true;
    }

    inline std::vector<bool> DPcodes::DecToBin(int num)
    {
        std::vector<bool> binvec(n);
        for(int i = 0; i < n; i++){
            binvec[n-1-i] = num & 1;
            num = num >> 1;
        }
        return binvec;
    }

    inline std::vector<bool> DPcodes::IncBin(const std::vector<bool> code)
    {
        std::vector<bool> coderes = code;
        int s = 0;
        for(auto i = coderes.end(); i != coderes.begin(); i--){
            if(*i == 1){
                s++;
            }
        }
        if(s == n){
            return coderes;
        }
        for(auto i = coderes.end(); i != coderes.begin(); i--){
            if(*i == 0){
                *i = (*i + 1);
                break;
            }
            if(*i == 1){
                *i = 0;
            }
        }
        return coderes;
    }

    void DPcodes::FillTheCodeset()
    {
        for(int i = 0; i < pow(2, n); i++){
            codes[i] = DecToBin(i);
        }
    }

    void DPcodes::Compose(DPcodes cd1, DPcodes cd2)
    {
        if(n > 12 || t > n){
            f << "Can't find codes for these parameters" << std::endl;
            return;
        }
        if(floor(((cd2.N)-1)/cd2.t) >= floor(((cd1.N)-1)/cd1.t)){
            N = cd1.N + floor(((cd1.N)-1)/cd1.t)*cd2.t;
        }
        else{
            N = cd2.N + cd1.t + floor(((cd2.N)-1)/cd2.t) * cd1.t;
        }
        dpc.resize(N);
        int D, E;
        D = 0;
        E = 0;
        int diff = 0;
        for(int i = 0; i < 9; i++){
            int r = 0;
            dpc[i].resize(cd1.dpc[D].size() + cd2.dpc[E].size());
            for(int j = 0; j < cd1.dpc[D].size(); j++){
                dpc[i][j] = cd1.dpc[D][j];
                r = j;
            }
            r++;
            for(int j = 0; j < cd2.dpc[E].size(); j++){
                dpc[i][r] = cd2.dpc[E][j];
                r++;
            }
            if(E-D >= diff){
                D++;
                diff++;
            }
            else{
                E++;
            }
        }
    }

    void DPcodes::CodesSet()
    {
        if(n > 12){
            f << "Can't find codes for these parameters" << std::endl;
            dpc.clear();
            return;
        }
        if(n > 6){
            int N1, N2, n1, n2, t1, t2;
            std::cout << "It's a big code. Please, enter the parameters for codes to compose." << std::endl;
            std::cout << "Enter parameters for the first code: " << std::endl;
            std::cin >> N1;
            std::cin >> n1;
            std::cin >> t1;
            std::cout << "Enter parameters for the second code: " << std::endl;
            std::cin >> N2;
            std::cin >> n2;
            std::cin >> t2;
            DPcodes cd1(N1, n1, t1, fname);
            cd1.CodesSet();
            DPcodes cd2(N2, n2, t2, fname);
            cd2.CodesSet();
            Compose(cd1, cd2);
            return;
        }
        int maxpow = pow(2, n);
        FillTheCodeset();
        bool flag = false;
        for(int i = 0; i < N; i++){
            if(flag && i == 1){
                f << "Can't find codes for these parameters" << std::endl;
                dpc.clear();
                return;
            }
            for(int j = 0; j < maxpow; j++){
                dpc[i] = codes[j];
                if(flag){
                    if(j == maxpow-1){
                        i -= 2;
                    }
                    if(HammAllPrev(i, codes[j])){
                        flag = false;
                        continue;
                    }
                }
                if(HammAllPrev(i, codes[j])){
                    flag = false;
                    break;
                }
                if(j == maxpow-1){
                    flag = true;
                }
            }
            if(flag){
                i -= 2;
            }
        }
    }

    void DPcodes::DPrint()
    {
        for(int i = 0; i != dpc.size(); i++){
            for(int j = 0; j < dpc[i].size(); j++){
                f << dpc[i][j];
            }
            f << std::endl;
        }
    }