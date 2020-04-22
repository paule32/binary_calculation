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

    std::cout << "A = " << argv[2] << std::endl;
    std::cout << "B = " << argv[3] << std::endl << std::endl;
    
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

