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
 	
 	// store stop words in a hashset
 	// was void
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
 		//return stop_words;
 	} 
 	
 	// returns true if given word is a word contained in hashset
 	bool isStopWord(set<string>& stop_words, string word){
 		if (stop_words.find(word) != stop_words.end()){//if it has the word is in the hash_set, then it is a stop word
 			return true;
 		}
 		else {//otherwise it is not a stop word
 			return false;
 		}
 	}
	
	
	// string stem(string s){
		
	// 	return s;
		
	// }//TODO

	// creates cleaned words, stores them in cleaned txt files
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
	
	/* m() measures the number of consonant sequences between 0 and j. if c is
      a consonant sequence and v a vowel sequence, and <..> indicates arbitrary
      presence,

         <c><v>       gives 0
         <c>vc<v>     gives 1
         <c>vcvc<v>   gives 2
         <c>vcvcvc<v> gives 3
         ....
   */
	int m(string word){
		//so one or more vowels immediately paired with one or more consants
		regex VCExpression("[aeiouy]+[^aeiouy]+");
		int vc_count = 0;
	    for(sregex_iterator it(word.begin(), word.end(), VCExpression), it_end; it != it_end; ++it ){
	    	vc_count++
	    }
	    
	    return vc_count;
	}
	
	bool ends(string word, string ending){
		//regex pattern(ending + "$");
		regex pattern("[a-zA-z]+" + ending);
		return regex_match(word, pattern);
	}
	
	void step1a(string word){
// SSES		->		SS		    		caresses	->		caress
// IES		->		I		    		ponies		->		poni
//     									ties		->		ti
// SS		->		SS		    		caress		->		caress
// S		->				    		cats		->		cat

  	string newending = "";
  	if(ends(word, "sses")){
  		regex ending("sses");
  		newending = "ss";
  		string result = regex_replace(word, ending, newending);
  	}
  	else if(ends(word, "ies")){
  		regex ending("ies");
  		newending = "i";
  		string result = regex_replace(word, ending, newending);
  	}
  	else if(ends(word, "s")){
  		regex ending("s");
  		newending = "";
  		string result = regex_replace(word, ending, newending);
  		cout << "result is: " << result << endl;
  	}

	}
	
	void step1b(string word){
// (m>0) EED	->		EE		  feed			->		feed
//  agreed		->		agree
// (*v*) ED		->				  plastered		->		plaster
// bled			->		bled
// (*v*) ING	->				  motoring		->		motor
// sing			->		sing
	
	string newending = "";
  	if(ends(word, "eed")){
  		regex ending("eed");
  		newending = "ee";
  		string result = regex_replace(word, ending, newending);
  	}
  	else if(ends(word, "ies")){
  		regex ending("ies");
  		newending = "i";
  		string result = regex_replace(word, ending, newending);
  	}
  	else if(ends(word, "s")){
  		regex ending("s");
  		newending = "";
  		string result = regex_replace(word, ending, newending);
  		cout << "result is: " << result << endl;
  	}
	

		
	}
	
	void step1c(){
		
	}
	
	void step2(){
		
	}
	
	void step3(){
		
	}
	
	void step4(){
		
	}
	
	void step5a(){
		
	}
	
	void step5b(){
		
	}
	
	
	
	// tests that getModifiedWords(string line) works properly
	bool testModifiedWords(string cleaned_file_name){
		bool result = false;
		string line = "";
		string word_to_check = "";
		ifstream inFile;
		inFile.open(cleaned_file_name);
		if(inFile.is_open()){// false
			while(getline (inFile, line)){
				word_to_check = line;
				if(isStopWord(stop_words, word_to_check)){
					result = true;
					cout << word_to_check << endl;
					break;
				}
				else{
					result = false;
				}
			}//while
			inFile.close();
			word_to_check = "";
		}//if
		else{
			cout << "Can't open the main files" << endl;
		}
		return result;
	}

int main(){
	int measure = m("tree");
	cout << "the measure is: " << measure << endl;
	
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
				string index_to_str = lexical_cast<string>(i);
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
	
	// ----------------------------- TESTS -------------------------------------
	
	// checks to confirm cleaned_files are cleaned
	for(int i = 1; i < 41; i++){
		string cleaned_file_path = "";
		string index_to_str = lexical_cast<string>(i);
		cleaned_file_path = "./corpus/txt" + index_to_str + "_cleaned.txt";
		cout << "File path: "<< cleaned_file_path << " returned " << testModifiedWords(cleaned_file_path) << endl;
	}
	
	return 0;
}//main
