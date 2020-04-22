// ------------------------------------------------------------------------------
// dBase4Linux 1.0
// RDP - Rapid Database Programming
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
# include <vector>      // std::vector

enum math_ops : char {
    _add_ = '+',
    _sub_ = '-',
    _mul_ = '*',
    _div_ = '/'
};
math_ops math_op;

struct {
    std::string binary;
    std::string hexadec;
    std::string decimal;
    std::string octal;
} sw_system[] = {
    "0000", "0",  "0", "",
    "0001", "1",  "1", "",
    "0010", "2",  "2", "",
    "0011", "3",  "3", "",
    "0100", "4",  "4", "",
    "0101", "5",  "5", "",
    "0110", "6",  "6", "",
    "0111", "7",  "7", "",
    "1000", "8",  "8", "",
    "1001", "9",  "9", "",
    "1010", "a", "10", "",
    "1011", "b", "11", "",
    "1100", "c", "12", "",
    "1101", "d", "13", "",
    "1110", "e", "14", "",
    "1111", "f", "15", ""
};

std::string getBinaryNumber(std::string num)
{
    std::string tmp = "ssss";

    // binary ?
    if ((num.size() > 0) && (num.size() < 5)) {
        return num;
    }   else
    // dezimal ?
    if ((num.size() > 0) && (num.size() < 3)) {
        uint8_t idx = std::atoi(num.c_str());
        return sw_system[idx].binary;
    }   else {
        std::cout << "Format nicht erkannt !" << std::endl;
        return "";
    }
    
    return tmp;
}

std::string getHexNumber(std::string num)
{
    uint8_t idx = std::atoi(num.c_str());
    return sw_system[idx].hexadec;
}

int main(int argc, char **argv)
{
    std::cout << std::endl << "binäres rechnen (c) 2020 Jens Kallup";
    std::cout << std::endl << "Argumente:";
    std::cout << std::endl << "arg1: add | sub | mul | div";
    std::cout << std::endl << "arg2: nummer1";
    std::cout << std::endl << "arg3: nummer2";
    std::cout << std::endl << std::endl;
    
    if (argc < 3) {
        std::cout << "Argumentliste für Programmstart falsch !" << std::endl;
        std::cout << "Benutzung wie folgt:"    << std::endl;
        std::cout << "bin.exe <op> <Zahl1> <Zahl2>" << std::endl << std::endl;
        std::cout << "Programm wird beendet."  << std::endl;
        return 1;
    }
    
    if (!strcmp(argv[1],"add")) { math_op = math_ops::_add_; std::cout << "binäre Addition ";       } else
    if (!strcmp(argv[1],"sub")) { math_op = math_ops::_sub_; std::cout << "binäre Subtrahieren ";   } else
    if (!strcmp(argv[1],"mul")) { math_op = math_ops::_mul_; std::cout << "binäre Multiplizieren "; } else
    if (!strcmp(argv[1],"div")) { math_op = math_ops::_div_; std::cout << "binäre Dividieren ";     } else
    {
        std::cout << "Achtung: argument 1 wurde nicht erkannt !" << std::endl;
        std::cout << "Programm wird beendet.";
        return 1;
    }
    
    std::cout << "zweier _nicht_ negativen Zahlen:" << std::endl;
    
    std::vector<uint8_t> lhs(20);
    std::vector<uint8_t> rhs(20);
    
    std::fill(lhs.begin(),lhs.end(),'0');
    std::fill(rhs.begin(),rhs.end(),'0');

    std::cout << " A = " << argv[2] << std::endl;
    std::cout << " B = " << argv[3] << std::endl << std::endl;
    
    std::string lhs_a = getBinaryNumber(argv[2]);
    std::string rhs_b = getBinaryNumber(argv[3]);
    
    if (lhs_a.size() < 1) { std::cout << " Wert A ist falsch !" << std::endl; return 1; }
    if (rhs_b.size() < 1) { std::cout << " Wert B ist falsch !" << std::endl; return 1; }
    
    std::cout << " A (bin)  = " << lhs_a << std::endl;
    std::cout << " B (bin)  = " << rhs_b << std::endl;
    std::cout << std::endl;
    
    std::cout << " A (hex)  = " << getHexNumber(argv[2]) << " --> 0x" << getHexNumber(argv[2]) << std::endl;
    std::cout << " B (hex)  = " << getHexNumber(argv[3]) << " --> 0x" << getHexNumber(argv[3]) << std::endl;
    std::cout << std::endl;
    
    std::cout << "        A =";
    for (std::vector<uint8_t>::iterator it = lhs.begin(); it != lhs.end(); ++it)
    std::cout << " " << *it;
    std::cout << std::endl;
    
    std::cout << "        B =";
    for (std::vector<uint8_t>::iterator it = rhs.begin(); it != rhs.end(); ++it)
    std::cout << " " << *it;
    std::cout << std::endl << std::endl;
    
    std::cout << "   Merker =";
    for (int l = 0; l < 20; ++l);
    
    std::cout << std::endl << " ";
    for (int l = 0; l < 50; ++l)
    std::cout << "-";
    std::cout << std::endl;
    
    std::cout << " Ergebnis =";
    std::cout << std::endl << " ";
    
    for (int l = 0; l < 50; ++l)
    std::cout << "=";
    std::cout << std::endl;
    
    return 0;
}

