// ------------------------------------------------------------------------------
//
// (c) 2015-2020 Jens Kallup
// MIT License
//
// Copyright (c) 2020 Jens Kallup
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// --------------------------------------------------------------------------------

# include <cstdio>
# include <cstdlib>
# include <cstring>

# include <iostream>    // std::cout
# include <algorithm>   // std::fill
# include <iomanip>
# include <string>
# include <bitset>
# include <sstream>
# include <vector>      // std::vector
# include <unordered_map>
# include <map>
# include <typeindex>
# include <type_traits>

using namespace std;
static char math_op;

namespace kallup {
    using namespace std;
    unordered_map<type_index,string> types_map;

    class Integer {
    public:
        Integer(int) { }
    };
    class Float {
    public:
    };
    class String {
    public:
    };
    
    template <typename T1, typename T2, uint32_t max = 8>
    class BinaryCalc {
    public:
        BinaryCalc();
        BinaryCalc(const T1 a, const T2 b);
        
        string add(const T1 a, const T2 b);
        string sub(const T1 a, const T2 b);
        string mul(const T1 a, const T2 b);
        string div(const T1 a, const T2 b);
        
        string add();
        string sub();
        string mul();
        string div();
        
        string result() const;
    };
}

namespace kallup {
    using namespace std;
    static bool  initialized = false;
    stringstream sum_bits,LHA,LHB;
    char         _a[64],_b[64],_c[64];
    uint32_t     _m;
    uint8_t      _cary;
    
    uint32_t     prec_len = 20;
    
    void init()
    {
        #define TYPES_MAP(t) \
        types_map[typeid(t)] = #t
        
        TYPES_MAP(int  );
        TYPES_MAP(uint8_t );
        TYPES_MAP(uint16_t);
        TYPES_MAP(uint32_t);
        TYPES_MAP(uint64_t);

        TYPES_MAP(float);
        
        TYPES_MAP(Integer);
        TYPES_MAP(Float);
        TYPES_MAP(String);
        
        _cary = '0';
        for (int i = 0; i < prec_len; ++i) {
            _a[i] = '0';
            _b[i] = '0';
            _c[i] = '0';
        }
        
        initialized = true;
    }
    template <typename T1, typename T2, uint32_t max>
    BinaryCalc<T1,T2,max>::BinaryCalc() {
        if (!initialized) {
            init();
            initialized = true;
            prec_len = max;
            sum_bits.clear();
            LHA << "0";
            LHB << "0";
        }
    }
    template <typename T1, typename T2, uint32_t max>
    string BinaryCalc<T1,T2,max>::result() const { return _c; }

    string str2bin(string a)
    {
        vector<string> bin;
        string bis;
        for (int idx = a.size(); idx >= 0; --idx)     {
            switch (a[idx]) {
                case '0':           bis = "0000"; break;
                case '1':           bis = "0001"; break;
                case '2':           bis = "0010"; break;
                case '3':           bis = "0011"; break;
                case '4':           bis = "0100"; break;
                case '5':           bis = "0101"; break;
                case '6':           bis = "0110"; break;
                case '7':           bis = "0111"; break;
                case '8':           bis = "1000"; break;
                case '9':           bis = "1001"; break;

                case 'a': case 'A': bis = "1010"; break;
                case 'b': case 'B': bis = "1011"; break;
                case 'c': case 'C': bis = "1100"; break;
                case 'd': case 'D': bis = "1101"; break;
                case 'e': case 'E': bis = "1110"; break;
                case 'f': case 'F': bis = "1111"; break;
            }
            bin.push_back(bis);
        }
        
        string bin_str;
        for (const auto &chr: bin)
        bin_str += chr;
        
        return bin_str;
    }
    
    void _com();
    void _add();
    
    void _sub()
    {
        _m = 1;
        _com();
        _add();
    }
    void _com()
    {
        int count = 0;
        for (int i = prec_len; i >= 0; i--) {
            if (count > 0) {
                if (_b[i] == '1')
               _b[i] = '0'; else
               _b[i] = '1';
            }
            if (_b[i] == '1') {
                count++;
            }
        }
    }
    void _add()
    {
        for (int i = prec_len; i >= 0; i--) {
            if (_cary == '0' && _a[i] == '0' && _b[i] == '0') { _cary = '0'; _c[i] = '0'; } else
            if (_cary == '0' && _a[i] == '0' && _b[i] == '1') { _cary = '0'; _c[i] = '1'; } else
            if (_cary == '0' && _a[i] == '1' && _b[i] == '0') { _cary = '0'; _c[i] = '1'; } else
            if (_cary == '0' && _a[i] == '1' && _b[i] == '1') { _cary = '1'; _c[i] = '0'; } else
            if (_cary == '1' && _a[i] == '1' && _b[i] == '1') { _cary = '1'; _c[i] = '1'; } else
            if (_cary == '1' && _a[i] == '0' && _b[i] == '0') { _cary = '0'; _c[i] = '1'; } else
            if (_cary == '1' && _a[i] == '0' && _b[i] == '1') { _cary = '1'; _c[i] = '0'; } else
            if (_cary == '1' && _a[i] == '1' && _b[i] == '0') { _cary = '1'; _c[i] = '0'; } else
            if (_cary == '1' && _a[i] == '1' && _b[i] == '1') { _cary = '1'; _c[i] = '1'; }
        }
    }

    template <typename T1, typename T2>
    string getAdd(
        const T1 ta,
        const T2 tb) {

        string lha(ta);
        string lhb(tb);
        
        for (int i = 0; i < prec_len; ++i) {
            _a[i] = lha[i];
            _b[i] = lhb[i];
        }

        _add();
        return _c;
    }

    template <typename T1, typename T2>
    string getSub(
        const T1 ta,
        const T2 tb) {

        string lha(ta);
        string lhb(tb);
        
        for (int i = 0; i < prec_len; ++i) {
            _a[i] = lha[i];
            _b[i] = lhb[i];
        }
        
        _sub();
        return _c;
    }
    
    template <typename T1, typename T2>
    string getMul(
        const T1 ta,
        const T2 tb) {
        return "";
    }
    
    template <typename T1, typename T2>
    string getDiv(
        const T1 ta,
        const T2 tb) {
        return "";
    }    

    template <typename T1, typename T2, uint32_t max>
    BinaryCalc<T1,T2,max>::BinaryCalc(const T1 a, const T2 b) {
        if (!initialized) {
            init();
            initialized = true;
            prec_len = max;
            sum_bits.clear();
            LHA << a;
            LHB << b;
        }
    }

    template <class T1, typename T2, uint32_t max> string BinaryCalc<T1,T2,max>::add(const T1 a, const T2 b) { return getAdd(a,b); }
    template <class T1, typename T2, uint32_t max> string BinaryCalc<T1,T2,max>::sub(const T1 a, const T2 b) { return getSub(a,b); }
    template <class T1, typename T2, uint32_t max> string BinaryCalc<T1,T2,max>::mul(const T1 a, const T2 b) { return getMul(a,b); }
    template <class T1, typename T2, uint32_t max> string BinaryCalc<T1,T2,max>::div(const T1 a, const T2 b) { return getDiv(a,b); }
    
    template <class T1, typename T2, uint32_t max> string BinaryCalc<T1,T2,max>::add() { return getAdd(LHA.str(),LHB.str()); }
    template <class T1, typename T2, uint32_t max> string BinaryCalc<T1,T2,max>::sub() { return getSub(LHA.str(),LHB.str()); }
    template <class T1, typename T2, uint32_t max> string BinaryCalc<T1,T2,max>::mul() { return getMul(LHA.str(),LHB.str()); }
    template <class T1, typename T2, uint32_t max> string BinaryCalc<T1,T2,max>::div() { return getDiv(LHA.str(),LHB.str()); }
}

#ifdef TEST
// test funktion helper
inline void put_str1(char t1, std::string t2)
{
    using namespace std;
    cout << "        " << t1 << " =";
    for (size_t  l = 0; l <
        t2.size(); ++l)
        cout << " " << t2[l];
    cout << endl;
}

inline void put_str2(char t1)
{
    using namespace std;
    for (int l = 0; l < 50; ++l)
        cout << t1;
        cout << endl;
}

int main(int argc, char **argv)
{
    using namespace std;
    using namespace kallup;
    cout << endl << "binäres rechnen (c) 2020 Jens Kallup" << endl;
    
    if (argc < 3) {
        cout << "Argumentliste für Programmstart falsch !"  << endl
             << "Benutzung wie folgt:"                      << endl
             << "bin.exe <arg1> <arg2> <arg3>"              << endl
                                                            << endl
             << "Argumente:"                                << endl
             << "arg1: add | sub | mul | div"               << endl
             << "arg2: nummer1"
             << "arg3: nummer2"                             << endl
                                                            << endl                                                            
             << "Programm wird beendet."                    << endl;
        return 1;
    }
    
    string arg1 = argv[1];
    string _bs  = "binäres ";
    
    if (arg1 == "add") { math_op = '+'; cout << _bs << "addieren ";       } else
    if (arg1 == "sub") { math_op = '-'; cout << _bs << "subtrahieren ";   } else
    if (arg1 == "mul") { math_op = '*'; cout << _bs << "multiplizieren "; } else
    if (arg1 == "div") { math_op = '/'; cout << _bs << "dividieren ";     } else
    {
        cout << "Achtung: argument 1 wurde nicht erkannt !" << endl
             << "Programm wird beendet.";
        return 1;
    }
    
    cout << "zweier _nicht_ negativen Zahlen:" << endl;
    
    string bs_A = str2bin(argv[2]);
    string bs_B = str2bin(argv[3]);
    string bs_C ;
    
    BinaryCalc < string,string > calcu(bs_A,bs_B);
    switch (math_op) {
        case '+': bs_C = calcu.add(); break;
        case '-': bs_C = calcu.sub(); break;
        case '*': bs_C = calcu.mul(); break;
        case '/': bs_C = calcu.div(); break;
    }

    cout << " A (hex)  = " << hex << argv[2] << " --> 0x" << hex << argv[2] << endl
         << " B (hex)  = " << hex << argv[3] << " --> 0x" << hex << argv[3] << endl
         << std::endl;

    put_str1('A',bs_A);
    put_str1('B',bs_B);

    put_str2('-'); cout << " Ergebnis =";
    
    for (int s = 0; s < bs_C.size(); ++s)
    cout << " " << bs_C[s];
    cout << endl;
    
    put_str2('=');    
    
    return 0;
}
#endif  // TEST

