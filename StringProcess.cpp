#include <string>
#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
using namespace boost;
 	
 	
set<string> stop_words;	
 	
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
			 cout << "Can't open the stop words file" << endl;
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

string getModifiedWords(string line){
	string modified_line = "";
    regex rgExpression("[a-zA-Z][a-zA-Z]+");

    for(sregex_iterator it(line.begin(), line.end(), rgExpression), it_end; it != it_end; ++it ){
    	string word = (*it)[0];
    	transform(word.begin(), word.end(), word.begin(), ::tolower);
    	if(!isStopWord(stop_words, word)){ //if its not a stop word, then add it
    		modified_line += word + "\n";
    	}
    }
    
    return modified_line;
}

int main(){
	
	hashStopWords(stop_words);
	ofstream outFile;
	string modified_words = "";
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
			for(int i = 1; i < 41; i++){
				string file_path = "";
				string index_to_str = boost::lexical_cast<string>(i);
				file_path = "./Original_Files/txt" + index_to_str + ".txt";
				//ifstream inFile(file_path.c_str());
				ifstream inFile;
				inFile.open(file_path);
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
						modified_words += getModifiedWords(line);
						
					}//while
					inFile.close();
					outFile.open("./corpus/txt" + index_to_str + "_cleaned.txt");
					outFile << modified_words << endl;
					outFile.close();
					modified_words = "";
				}//if
				else{
					 cout << "Can't open the main files" << endl;
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
