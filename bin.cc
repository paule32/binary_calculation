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
    
    template <typename T1, typename T2, uint32_t max = 10>
    class BinaryCalc {
    public:
        BinaryCalc();
        BinaryCalc(const T1 a, const T2 b);
        
        string add(const T1 a, const T2 b);
        string sub(const T1 a, const T2 b);
        string mul(const T1 a, const T2 b);
        string div(const T1 a, const T2 b);
        
        string getResult() const;
    };
}

namespace kallup {
    using namespace std;
    static bool  initialized = false;
    stringstream sum_bits,LHA,LHB;
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
        
        initialized = true;
    }
    template <typename T1, typename T2, uint32_t max>
    BinaryCalc<T1,T2,max>::BinaryCalc() {
        if (!initialized) {
            init();
            initialized = true;
            prec_len = max;
            sum_bits.clear();
        }
    }
    template <typename T1, typename T2, uint32_t max>
    string BinaryCalc<T1,T2,max>::getResult() const {
        if (sum_bits.str().size() < 1)
        return "0";  else
        return sum_bits.str();
    }
    
    
    int getBit(string s, int index)
    {
         if(index >= 0)   return (s[index] - '0');
         else             return 0;
    }

    string addBinary(string a, string b) 
    {
        if(a.size() > b.size())        while(a.size() > b.size()) b = "0" + b;
        else if(b.size() > a.size())   while(b.size() > a.size()) a = "0" + a;

        int l = max(a.size()-1, b.size() - 1);

        string result = ""; 
        int s=0;        

        while(l >= 0 || s == 1)
        {
            s      += getBit(a, l) + getBit(b, l);
            result  = char(s % 2 + '0') + result;
            s      /= 2;
            l--;
        }
        return result;
    }
    

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
        
        reverse(bin.begin(),bin.end());
        string bin_str;
        
        for (const auto &chr: bin)
        bin_str += chr;
        
        return bin_str;
    }
    
    template <typename T1, typename T2>
    string getAdd(
        const T1 ta,
        const T2 tb) {
        
        string lha,lhb;
        
        lha = str2bin(ta);
        lhb = str2bin(tb);
        
        return addBinary(lha,lhb);
    }

    template <typename T1, typename T2, uint32_t max>
    BinaryCalc<T1,T2,max>::BinaryCalc(const T1 a, const T2 b) {
        if (!initialized) {
            init();
            initialized = true;
            prec_len = max;
            sum_bits.clear();
        }
        sum_bits << getAdd(a,b);
    }

    template <class T1, typename T2, uint32_t max> string BinaryCalc<T1,T2,max>::add(const T1 a, const T2 b) { return getAdd(a,b); }
    template <class T1, typename T2, uint32_t max> string BinaryCalc<T1,T2,max>::sub(const T1 a, const T2 b) { return getSub(a,b); }
    template <class T1, typename T2, uint32_t max> string BinaryCalc<T1,T2,max>::mul(const T1 a, const T2 b) { return getMul(a,b); }
    template <class T1, typename T2, uint32_t max> string BinaryCalc<T1,T2,max>::div(const T1 a, const T2 b) { return getDiv(a,b); }    
}

static int prec_len = 20;

std::string addStr2Bin(std::string A, std::string B)
{
    using namespace kallup;
    using namespace std;
       
    BinaryCalc < string,string > calcu(A,B);
    
    stringstream tmp;
    tmp << calcu.getResult();
    return tmp.str();
}

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
    cout << endl << "binäres rechnen (c) 2020 Jens Kallup"
         << endl << "Argumente:"
         << endl << "arg1: add | sub | mul | div"
         << endl << "arg2: nummer1"
         << endl << "arg3: nummer2"
         << endl << endl;
    
    if (argc < 3) {
        cout << "Argumentliste für Programmstart falsch !"  << endl
             << "Benutzung wie folgt:"                      << endl
             << "bin.exe <op> <Zahl1> <Zahl2>"              << endl
                                                            << endl
             << "Programm wird beendet."                    << endl;
        return 1;
    }
    
    string arg1 = argv[1];
    
    if (arg1 == "add") { math_op = '+'; cout << "binäre Addition ";       } else
    if (arg1 == "sub") { math_op = '-'; cout << "binäre Subtrahieren ";   } else
    if (arg1 == "mul") { math_op = '*'; cout << "binäre Multiplizieren "; } else
    if (arg1 == "div") { math_op = '/'; cout << "binäre Dividieren ";     } else
    {
        cout << "Achtung: argument 1 wurde nicht erkannt !" << endl
             << "Programm wird beendet.";
        return 1;
    }
    
    cout << "zweier _nicht_ negativen Zahlen:" << endl;
    
    string bs_A = str2bin(argv[2]);
    string bs_B = str2bin(argv[3]);
   
    cout << " A (hex)  = " << hex << argv[2] << " --> 0x" << hex << argv[2] << std::endl
         << " B (hex)  = " << hex << argv[3] << " --> 0x" << hex << argv[3] << std::endl
         << std::endl;

    put_str1('A',bs_A);
    put_str1('B',bs_B);
    
    put_str2('-'); cout << " Ergebnis =";
    
    string bin_sum = addStr2Bin(argv[2],argv[3]);
    for (int s = 0; s < bin_sum.size(); ++s)
    cout << " " << bin_sum[s];
    cout << endl;
    
    put_str2('=');    
    
    return 0;
}

