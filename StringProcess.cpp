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
 	
 	
	set<string> stop_words;	//set of all the stop words
 	
 	// store stop words in a set
 	// read the stop words from the file and just put each word in the set
 	void hashStopWords(set<string>& stop_words){
 		string file_path = "./stop_words.txt";
	 	ifstream inFile(file_path.c_str());
	 	string word;
	 	if(inFile.is_open()){
			while(getline (inFile, word)){
				stop_words.insert(word);
				word = ""; // clear it
			}//while
			inFile.close();
		}//if
		else{
			 cout << "Can't open the stop words file" << endl;
		}//else
 		//return stop_words;
 	}//hashStopWords 
 	
 	// returns true if given word is a word contained in set
 	bool isStopWord(set<string>& stop_words, string word){
 		if (stop_words.find(word) != stop_words.end()){//if it has the word is in the hash_set, then it is a stop word
 			return true;
 		}//if
 		else {//otherwise it is not a stop word
 			return false;
 		}//else
 	}//isStopWord
	
	
	//strips the given word with the given endin
	// ex: "apples" is given and enging "s" is given
	// this "apples" -> "apple"
	string stem(string word, string ending){
		string newending = "";
  		regex ending_expression(ending);
  		return regex_replace(word, ending_expression, newending);
	}//stem

	
	
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
		//loop through all the matches of the VC form and increment counter
		// to know how many of those forms there are
	    for(sregex_iterator it(word.begin(), word.end(), VCExpression), it_end; it != it_end; ++it ){
	    	vc_count++;
	    }//for
	    
	    return vc_count;
	}//m
	
	// returns true if the word end with the given ending
	// false otherwise
	bool ends(string word, string ending){
		//regex pattern(ending + "$");
		regex pattern("[a-zA-z]+" + ending);
		return regex_match(word, pattern);
	}//ends
	
	
	//returns true if the word contains a vowel,
	//false otherwise
	bool contains_vowel(string word){
		regex vowel_expression("[aeiouy]+");
		int vowel_count = 0;
		//using regex, picks up everything thats a vowel, so if this loop runs
		// then we know we had a vowel so return true
	    for(sregex_iterator it(word.begin(), word.end(), vowel_expression), it_end; it != it_end; ++it ){
	    	vowel_count++;
	    	 if(vowel_count > 0){
	    		return true;
	    	}//if
	    }//for
	    
	    return false;//if it gets here, we know there were no vowels, so return false
	}//contanis
	
	//return true if the stem of the word ends with the given ending
	//false otherwise
	bool stem_ends(string word, string strip, string ending){
		word = stem(word, strip);
		return ends(word, ending);
	}//stem_ends
	
	//returns true if the given word ends in a double consonant
	//ex: tt, vv, bb, cc
	//false otherwise
	bool ends_doubleC(string word){
		int length = word.length();
		if(length > 1 && word.at(length - 1) == word.at(length - 2)){ // checking if last two characters are same
			regex pattern("[a-z]+[^aeiouy][^aeiouy]");
			return regex_match(word, pattern);
		}//if
		else {
			return false;
		}//else
		
	}//ends_double
	
	//returns true if the given word ends in a consonant, vowel, consant format
	// but the last consonant does not end in w, x, or y
	// the stem ends cvc, where the second c is not W, X or Y (e.g. -WIL, -HOP).
	bool ends_cvc(string word){
		regex pattern("[a-z]*[^aeiouy][aeiouy][^aeiouwxy]");
		return regex_match(word, pattern);
	}//ends_cvc
	
	// helper used to replace the given ending of the given word with the 
	// new given ending
	// ex: word: "hopping", ending: "ping", newending: "s"
	// result: "hops"
	string replace_ending(string word, string the_ending, string newending){
		regex ending(the_ending);
  		return regex_replace(word, ending, newending);
	}
	
	// just following the first step of the porter algorithm
	string step1a(string word){
// SSES		->		SS		    		caresses	->		caress
// IES		->		I		    		ponies		->		poni
//     									ties		->		ti
// SS		->		SS		    		caress		->		caress
// S		->				    		cats		->		cat

	  	string result = word;
	  	if(ends(word, "sses")){
	  		result = replace_ending(word, "sses", "ss");
	  	}//if
	  	else if(ends(word, "ies")){
	  		result = replace_ending(word, "ies", "i");
	  	}//else if
	  	else if(ends(word, "ss")){
	  		result = replace_ending(word, "ss", "ss");
	  	}//else if
	  	else if(ends(word, "s")){
	  		result = replace_ending(word, "s", "");
	  	}//else if
	  	
	  	return result;

	}//step1a
	
	// just following the first step of the porter algorithm
	string step1b(string word){
// (m>0) EED	->		EE		  feed			->		feed
//  							  agreed		->		agree
// (*v*) ED		->				  plastered		->		plaster
// 								  bled			->		bled
// (*v*) ING	->				  motoring		->		motor
// 								  sing			->		sing
	
		string result = word;
	  	if(ends(word, "eed") && m(stem(word, "eed")) > 0){
	  		result = replace_ending(word, "eed", "ee");
	  	}//if
	  	else if(ends(word, "ed") && contains_vowel(stem(word, "ed"))){
	  		result = replace_ending(word, "ed", "");
	  		if(ends(result, "at")){
	  			result = replace_ending(result, "at", "ate");
	  		}//if
	  		else if(ends(result, "bl")){
	  			result = replace_ending(result, "bl", "ble");
	  		}//else if
	  		else if(ends(word, "iz")){
	  			result = replace_ending(result, "iz", "ize");
	  		}//else
	  		else if(ends_doubleC(result) && !(ends(result, "l") || ends(result, "s") || ends(result, "z"))){
	  			result = result.substr(0, result.length() - 1); // strips last character off
	  		}//else if
	  		else if(m(result) == 1 && ends_cvc(result)){
	  			result += "e";
	  		}//else if
	  	}//else if
	  	else if(ends(word, "ing") && contains_vowel(stem(word, "ing"))){
	  		result = replace_ending(word, "ing", "");
	  		if(ends(result, "at")){
	  			result = replace_ending(result, "at", "ate");
	  		}//if
	  		else if(ends(result, "bl")){
	  			result = replace_ending(result, "bl", "ble");
	  		}//else if
	  		else if(ends(word, "iz")){
	  			result = replace_ending(result, "iz", "ize");
	  		}//else if
	  		else if(ends_doubleC(result) && !(ends(result, "l") || ends(result, "s") || ends(result, "z"))){
	  			result = result.substr(0, result.length() - 1); // strips last character off
	  		}//else if
	  		else if(m(result) == 1 && ends_cvc(result)){
	  			result += "e";
	  		}//else if
	  	}//else if
		
		return result;
		
	}//step1b
	
	// just following the first step of the porter algorithm
	string step1c(string word){
//		(*v*) Y		->		I		    		happy		->		happi
 //   											sky		->		sky
 		string result = word;
 		if(ends(word, "y") && contains_vowel(stem(word, "y"))){
 			result = replace_ending(word, "y", "i");
 		}//step1c

		return result;
	}//step1c
	
	// just following the second step of the porter algorithm
	string step2(string word){
		string result = word;
		if(ends(word, "ational") && m(stem(word, "ational")) > 0){
			result = replace_ending(word, "ational", "ate");
		}//if
		else if(ends(word, "tional") && m(stem(word, "tional")) > 0){
			result = replace_ending(word, "tional", "tion");
		}//else if
		else if(ends(word, "enci") && m(stem(word, "enci")) > 0){
			result = replace_ending(word, "enci", "ence");
		}//else if
		else if(ends(word, "anci") && m(stem(word, "anci")) > 0){
			result = replace_ending(word, "anci", "ance");
		}//else if
		else if(ends(word, "abli") && m(stem(word, "abli")) > 0){
			result = replace_ending(word, "abli", "able");
		}//else if
		else if(ends(word, "alli") && m(stem(word, "alli")) > 0){
			result = replace_ending(word, "alli", "al");
		}//else if
		else if(ends(word, "entli") && m(stem(word, "entli")) > 0){
			result = replace_ending(word, "entli", "ent");
		}//else if
		else if(ends(word, "eli") && m(stem(word, "eli")) > 0){
			result = replace_ending(word, "eli", "e");
		}//else if
		else if(ends(word, "ousli") && m(stem(word, "ousli")) > 0){
			result = replace_ending(word, "ousli", "ous");
		}//else if
		else if(ends(word, "ization") && m(stem(word, "ization")) > 0){
			result = replace_ending(word, "ization", "ize");
		}//else if
		else if(ends(word, "ation") && m(stem(word, "ation")) > 0){
			result = replace_ending(word, "ation", "ate");
		}//else if
		else if(ends(word, "ator") && m(stem(word, "ator")) > 0){
			result = replace_ending(word, "ator", "ate");
		}//else if
		else if(ends(word, "alism") && m(stem(word, "alism")) > 0){
			result = replace_ending(word, "alism", "al");
		}//else if
		else if(ends(word, "iveness") && m(stem(word, "iveness")) > 0){
			result = replace_ending(word, "iveness", "ive");
		}//else if
		else if(ends(word, "fulness") && m(stem(word, "fulness")) > 0){
			result = replace_ending(word, "fulness", "ful");
		}//else if
		else if(ends(word, "ousness") && m(stem(word, "ousness")) > 0){
			result = replace_ending(word, "ousness", "ous");
		}//else if
		else if(ends(word, "aliti") && m(stem(word, "aliti")) > 0){
			result = replace_ending(word, "aliti", "al");
		}//else if
		else if(ends(word, "iviti") && m(stem(word, "iviti")) > 0){
			result = replace_ending(word, "iviti", "ive");
		}//else if
		else if(ends(word, "biliti") && m(stem(word, "biliti")) > 0){
			result = replace_ending(word, "biliti", "ble");
		}//else if
		
		return result;
		
	}//step2
	
	// just following the third step of the porter algorithm
	string step3(string word){
		string result = word;
		if(ends(word, "icate") && m(stem(word, "icate")) > 0){
			result = replace_ending(word, "icate", "ic");
		}//if
		else if(ends(word, "ative") && m(stem(word, "ative")) > 0){
			result = replace_ending(word, "ative", "");
		}//else if
		else if(ends(word, "alize") && m(stem(word, "alize")) > 0){
			result = replace_ending(word, "alize", "al");
		}//else if
		else if(ends(word, "iciti") && m(stem(word, "iciti")) > 0){
			result = replace_ending(word, "iciti", "ic");
		}//else if
		else if(ends(word, "ical") && m(stem(word, "ical")) > 0){
			result = replace_ending(word, "ical", "ic");
		}//else if
		else if(ends(word, "ful") && m(stem(word, "ful")) > 0){
			result = replace_ending(word, "ful", "");
		}//else if
		else if(ends(word, "ness") && m(stem(word, "ness")) > 0){
			result = replace_ending(word, "ness", "");
		}//else if
		return result;
	}//step3
	
	// just following the fourth step of the porter algorithm
	string step4(string word){
		string result = word;
		if(ends(word, "al") && m(stem(word, "al")) > 1){
			result = replace_ending(word, "al", "");
		}//if
		else if(ends(word, "ance") && m(stem(word, "ance")) > 1){
			result = replace_ending(word, "ance", "");
		}//else if
		else if(ends(word, "ence") && m(stem(word, "ence")) > 1){
			result = replace_ending(word, "ence", "");
		}//else if
		else if(ends(word, "er") && m(stem(word, "er")) > 1){
			result = replace_ending(word, "er", "");
		}//else if
		else if(ends(word, "ic") && m(stem(word, "ic")) > 1){
			result = replace_ending(word, "ic", "");
		}//else if
		else if(ends(word, "able") && m(stem(word, "able")) > 1){
			result = replace_ending(word, "able", "");
		}//else if
		else if(ends(word, "ible") && m(stem(word, "ible")) > 1){
			result = replace_ending(word, "ible", "");
		}//else if
		else if(ends(word, "ant") && m(stem(word, "ant")) > 1){
			result = replace_ending(word, "ant", "");
		}//else if
		else if(ends(word, "ement") && m(stem(word, "ement")) > 1){
			result = replace_ending(word, "ement", "");
		}//else if
		else if(ends(word, "ment") && m(stem(word, "ment")) > 1){
			result = replace_ending(word, "ment", "");
		}//else if
		else if(ends(word, "ent") && m(stem(word, "ent")) > 1){
			result = replace_ending(word, "ent", "");
		}//else if
		else if(ends(word, "ion") && (m(stem(word, "ion")) > 1 && (ends(stem(word, "ion"), "s") || ends(stem(word, "ion"), "t")))){
			result = replace_ending(word, "ion", "");
		}//else if
		else if(ends(word, "ou") && m(stem(word, "ou")) > 1){
			result = replace_ending(word, "ou", "");
		}//else if
		else if(ends(word, "ism") && m(stem(word, "ism")) > 1){
			result = replace_ending(word, "ism", "");
		}//else if
		else if(ends(word, "ate") && m(stem(word, "ate")) > 1){
			result = replace_ending(word, "ate", "");
		}//else if
		else if(ends(word, "iti") && m(stem(word, "iti")) > 1){
			result = replace_ending(word, "iti", "");
		}//else if
		else if(ends(word, "ous") && m(stem(word, "ous")) > 1){
			result = replace_ending(word, "ous", "");
		}//else if
		else if(ends(word, "ive") && m(stem(word, "ive")) > 1){
			result = replace_ending(word, "ive", "");
		}//else if
		else if(ends(word, "ize") && m(stem(word, "ize")) > 1){
			result = replace_ending(word, "ize", "");
		}//else if
		return result;
	}//setp4
	
	// just following the fifth step of the porter algorithm
	string step5a(string word){
		string result = word;
		if(ends(word, "e") && m(stem(word, "e")) > 1){
			result = replace_ending(word, "e", "");
		}//if
		else if(ends(word, "e") && (m(stem(word, "e")) == 1 && !ends_cvc(stem(word, "e")))){
			result = replace_ending(word, "e", "");
		}//else if
		return result;
	}//step5a
	
	// just following the fifth step of the porter algorithm
	string step5b(string word){
		string result = word;
		if(m(word) > 1 && ends_doubleC(word) && ends(word, "l")){
			result = result.substr(0, result.length() - 1); // strips last character off
		}//if
		return result;
	}//step5b
	
	//the porter algorithm, just calls each step
	// and stores the running value into word,
	// which eventually gets returned fully, and correctly stemmed
	string porter(string word){
		word = step1a(word);
		word = step1b(word);
		word = step1c(word);
		word = step2(word);
		word = step3(word);
		word = step4(word);
		word = step5a(word);
		word = step5a(word);
		return word;
	}//porter
	
	// creates cleaned words
	// you recieve a line from the original file, which you the use regex to
	// get only words that are greater than 1 letter from that given line. Then you
	// you iterate through the words, lowercasing each one and determining if its 
	// a stop word or not. If it is not a stop word then you stem it properly passing
	// it onto the porter algorithm which returns a stemmed word. Then you simply add
	// that stemmed word along with a newline, so that evey stemmed word shows up on its own
	// line in the cleaned files, onto the modified line string. The string will finally
	// have all the stemmed words and no stop words in it from the orginally given line
	// which it then just returns
	string getModifiedWords(string line){
		string modified_line = "";
	    regex rgExpression("[a-zA-Z][a-zA-Z]+");
	
	    for(sregex_iterator it(line.begin(), line.end(), rgExpression), it_end; it != it_end; ++it ){
	    	string word = (*it)[0];
	    	transform(word.begin(), word.end(), word.begin(), ::tolower);
	    	if(!isStopWord(stop_words, word)){ //if its not a stop word, then add it
	    		modified_line += porter(word) + "\n";
	    	}//if
	    }//for
	    
	    return modified_line;
	}//getModifiedWords
	
	
	// tests that getModifiedWords(string line) works properly
	// mainly tests if there are any stop words in the cleaned file
	// currently
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
				}//if
				else{
					result = false;
				}//else
			}//while
			inFile.close();
			word_to_check = "";
		}//if
		else{
			cout << "Can't open the main files" << endl;
		}//else
		return result;
	}//testModifiedWords


int main(){
	
	// string result = step1c("sky");
	// cout << "Became " << result << endl;

	hashStopWords(stop_words); //store stop words
	ofstream outFile; // used to write to cleaned files
	string modified_words = ""; // used to contain to correct words to add to cleaned files 
	string line;//used to read each line from original files
	int switch_val;//holds input value in int form
	
	string input = "";
	cout << "Welcome to our Project 2 interface: " << endl;
	cout << "Type 1 if you want to clean your data and 'q' to exit" << endl;
	cin >> input;
	
	if(input == "1"){
		switch_val = 1;
	}//if
	else if (input == "q"){
		switch_val = 2;
	}//else if
	
	switch(switch_val){
		case 1:{
			// loop over all 40 of the original files
			for(int i = 1; i < 41; i++){
				string file_path = "";
				string index_to_str = lexical_cast<string>(i);
				file_path = "./Original_Files/txt" + index_to_str + ".txt";//dynamically set file names
				//ifstream inFile(file_path.c_str());
				ifstream inFile;
				inFile.open(file_path);//open file
				if(inFile.is_open()){
					while(getline (inFile, line)){
						modified_words += getModifiedWords(line); // get stemmed, and stop words removed, words
					}//while
					inFile.close();
					outFile.open("./corpus/txt" + index_to_str + "_cleaned.txt"); // open corresponding cleaned file
					outFile << modified_words << endl; // write to it
					outFile.close();
					modified_words = ""; // clear to be used for next line
				}//if
				else{
					 cout << "Can't open the main files" << endl;
				}//else
			}//for
			break;
    }//case 1
		
		case 2:{
			cout << "Exiting..." << endl;
			break;
		}//case 2
		default:{
			cout << "Not a valid input." << endl;
		}//default
	}//switch
	
	// ----------------------------- TESTS -------------------------------------
	
	// // checks to confirm cleaned_files are cleaned
	// for(int i = 1; i < 41; i++){
	// 	string cleaned_file_path = "";
	// 	string index_to_str = lexical_cast<string>(i);
	// 	cleaned_file_path = "./corpus/txt" + index_to_str + "_cleaned.txt";
	// 	cout << "File path: "<< cleaned_file_path << " returned " << testModifiedWords(cleaned_file_path) << endl;
	// }
	
	return 0;
}//main
