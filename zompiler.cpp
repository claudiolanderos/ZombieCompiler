// zompiler.cpp : Defines the entry point for the console application.
//

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include "node.h"
#include <fstream>

extern int g_LineNumber;
extern NBlock* g_MainBlock;

extern int zompilerparse();
extern FILE* zompilerin;

int main(int argc, char* argv[])
{
	// Read input from the first command line parameter
	zompilerin = fopen(argv[1], "r");
	
	// Start the parse
	zompilerparse();
	
    if (g_MainBlock != nullptr)
    {
        CodeContext c;
        g_MainBlock->CodeGen(c);
        
        std::ofstream file("out.zom");
        for (auto i = c.mOps.begin(); i != c.mOps.end(); ++i)
        {
            std::cout << *i << std::endl;
            file << *i << std::endl;
        }
    }
    
	// Close the file stream
	fclose(zompilerin);

	return 0;
}

void zompilererror(const char* s)
{
	std::cout << s << " on line " << g_LineNumber << std::endl;
}
