#include <string>
#include <iostream>
#include <fstream>
using namespace std;

bool isStopWord(string s){return false;}//TODO
string stem(string s){return s;}//TODO

int main()
{
	ifstream inFile("test.txt");
	ofstream outFile;
	string res;
	string line;
	if(inFile.is_open()){
		while(getline (inFile, line))
		{
			if(!isStopWord(line)){
				res = res + line;
				cout << res;	
			}//if
		}//while
		inFile.close();
		outFile.open("testDump.txt");
		outFile << res;
	}//if
	else cout<< "Can't open that";
	
	
	return 0;
}//main
