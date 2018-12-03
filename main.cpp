/*
 * main.cpp
 */

#include "tokens.h"
#include "parse.h"
#include <fstream>
using std::cin;
using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;

vector<string> Ident::identVec;

int
main(int argc, char *argv[])
{
	ifstream file;
	istream *in = &cin;
	int linenum = 0;
      
    for ( int i=1; i < argc; i++ ) {
        string arg( argv[i]);

        if ( in != &cin ) {
            cerr << "TOO MANY FILENAMES" << endl;
            return 0;
        }
        else {
            file.open(arg);
            if (file.is_open() == false) {
                cerr << "COULD NOT OPEN " << arg << endl;
                return 0;
            }
        }
        in = &file;
    }
        
    // Part 2
	ParseTree *prog = Prog(in, &linenum);
    
	if( prog == 0 )
		return 0; // quit on error
   
    
    // Generate Output
    cout << "LEAF COUNT: " << prog -> LeafCount() << endl;
    cout << "STRING COUNT: " << prog -> StringCount() << endl;
    if (prog->IdentCount() > 0)
    {
        cout << "IDENT COUNT: " << prog -> IdentCount() << endl;
        map<string,int> idCountMap;
        map<int, vector<string>> freqMap;
        for (string s : Ident::identVec)
        {
            idCountMap[s]++;
        }
        map<string,int>:: iterator it;
        for (it=idCountMap.begin(); it != idCountMap.end(); it++)
        {
            freqMap[it->second].push_back(it->first);
        }
        
        map<int,vector<string>>::iterator sit = freqMap.end();
        --sit;
        
        for (int i = 0; i < sit->second.size(); i++) {
            cout << sit->second[i];
            
            if (i == sit->second.size() - 1)
                cout << endl;
            else
                cout << ", ";
        }
    }
    
	return 0;
}