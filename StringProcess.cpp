#include <string>
#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <vector>
#include <set>
using namespace std;
using namespace boost;
 	
 	void hashStopWords(set<string>& stop_words){
 		string file_path = "./stop_words.txt";
	 	ifstream inFile(file_path.c_str());
	 	string word;
	 	if(inFile.is_open()){
			while(getline (inFile, word)){
				stop_words.insert(word);
				word = ""; // clear it
			}
			inFile.close();
		}
		else{
			 cout << "Can't open that" << endl;
		}
 		
 	} 
 	
 	bool isStopWord(set<string>& stop_words, string word){
 		if (stop_words.find(word) != stop_words.end()){//if it has the word is in the hash_set, then it is a stop word
 			return true;
 		}
 		else {//otherwise it is not a stop word
 			return false;
 		}
 	}

string stem(string s){
	
	return s;
	
}//TODO

int main(){
	set<string> stop_words;
	hashStopWords(stop_words);
	string seq = "Some words. And... some punctuation.";
    regex rgExpression("[a-zA-Z][a-zA-Z]+");

    for(sregex_iterator it(seq.begin(), seq.end(), rgExpression), it_end; it != it_end; ++it ){
        cout << (*it)[0] << "\n";
    }
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
					// call a helper function here that reads each word in a line
					// and calls stop word function and stemmer funciton
						//addWordsFromLine(line);
						// if(!isStopWord(line)){
						// 	res = res + line;
						// 	cout << res;	
						// }
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



// void addWordsFromLine(string line){
// 		istringstream iss(line);
// 		string word = "";
// 		while(iss){ // while there is still more to read from the line
//  		word = "";
//  		if(getline(ss, word, " ")){ // gets the species name basically and store in s
//  			s = editFormat(s); // properly formats it
// 	 		species = s; // sets to species
// 	 		s = "" ; // clears s for later use
//  		}
//  		while(true){
// 	 		if(!getline(ss, s, ',')) break; // if there is no more to read from the file exit the loop	
// 	 		s = s.substr(1); // strips begining whitespace so " apples" becomes "apples"
// 	 		s = editFormat(s);
// 		 	subtypes.push_back(s); // adds a subtype of the species is added to this list 
// 		 	s = "";
//  		}
//  	}
// }


	// while(ss){ // while there is still more to read from the line
 //		string s = "";
 		
 //		if(getline(ss, s, ':')){ // gets the species name basically and store in s
 //			s = editFormat(s); // properly formats it
	//  		species = s; // sets to species
	//  		s = "" ; // clears s for later use
 //		}
 //		while(true){
	//  		if(!getline(ss, s, ',')) break; // if there is no more to read from the file exit the loop	
	//  		s = s.substr(1); // strips begining whitespace so " apples" becomes "apples"
	//  		s = editFormat(s);
	// 	 	subtypes.push_back(s); // adds a subtype of the species is added to this list 
	// 	 	s = "";
 //		}
 //	}
