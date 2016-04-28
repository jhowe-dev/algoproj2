#include <string>
#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <vector>
using namespace std;

//reads a single line from the file and returns true if the line contains a stop word?
bool isStopWord(string s){
	
	return false;
	
}//TODO:

string stem(string s){
	
	return s;
	
}//TODO

int main(){
	
	ofstream outFile;
	string res;
	string line;
	int switch_val;
	
	string input = "";
	cout << "Welcome to our Project 2 interface: " << endl;
	cout << "Type 1 if you want to clean your data and 'q' to exit" << endl;
	cin >> input;
	
	if(input == "1"){
		switch_val = 1;
	}
	else if (input == "q"){
		switch_val = 2;
	}
	
	switch(switch_val){
		
		case 1:{
			// loop over all 40 of the files
			for(int i = 0; i < 40; i++){
				string file_path = "";
				string index_to_str = boost::lexical_cast<string>(i);
				file_path = "./Original_Files/txt" + index_to_str + ".txt";
				ifstream inFile(file_path.c_str());
				if(inFile.is_open()){// false
					while(getline (inFile, line)){
					//	istringstream iss(line);
						if(!isStopWord(line)){
							res = res + line;
							cout << res;	
						}//if
					}//while
					inFile.close();
					outFile.open("testDump.txt");
					outFile << res << endl;
				}//if
				else{
					 cout << "Can't open that" << endl;
				}
			}
			break;
		}
		case 2:{
			cout << "Exiting..." << endl;
			break;
		}
		default:{
			cout << "Not a valid input." << endl;
		}
	}
	return 0;
}//main
