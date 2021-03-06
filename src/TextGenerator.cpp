/*
 * Steven Tran 
 * TextGenerator.cpp
 */

#include "TextGenerator.hpp"
#include <iostream>

TextGenerator::TextGenerator(const string & textDirectory) {
	// psuedo random seed for std::rand
	srand(time(NULL));

	DIR * dir;
	struct dirent * ent;
	ifstream infile;
	string line;
	string output;
	vector<string tokens>;

	// Opening the directory
	if((dir = opendir(textDirectory.c_str())) != nullptr) {
    	int i = 0;
		 
		// Loop to open individual files 
    	while((ent = readdir(dir)) != nullptr) {
    		i++;
    		// Skips the current and parent directory file in the current directory
    		if(i < 2) {
    			continue;
    		}

    		char str[BUFSIZ]; // may need to update this size
    		strcat(str, textDirectory.c_str());
    		strcat(str, "/");
    		strcat(str, end->d_name);

    		// Opening individual files
    		infile.open(str);
    		if(!infile) {
 				closedir(dir);
 				cerr << "Couldn't Open File!" << str << endl;
 				exit(1);
    		}

    		// Remove Unwanted Charactor! 
    		while(getline(infile, line)) {
                output += removeChars(line);
            }

    		infile.close();

    		// Tokenize text into individual words and punctuations
    		tokens = tokenize(output);
            populateTable(tokens);
            output = "";
    	} else {
    		cerr << "Couldn't Open Directory" << textDirectory << endl;
    		exit(1);
    	}

	}
}

string TextGenerator::generateNextWord(const string & prevWord) {
	return genRand(this->umap[prevWord]);
}

string TextGenerator::generateText(const int numWords) {
	string nextWord = ".";
    string document;

    for(int i = 0; i < numWords; i++) {
        nextWord = generateNextWord(nextWord);
        
        if(nextWord == "." || nextWord == "!" || nextWord == "?" || nextWord == "," || i == 0) {
            document.append(nextWord);
        }else if(nextWord.empty() == true) {
            nextWord = ".";
            document.append(nextWord);
        }else {
            document.append(" ");
            document.append(nextWord);
        } 
    } 
    return document;
}

string TextGenerator::removeChars(string & text) {
	string toReturn;

	// Iterate through each character within the string
    for(unsigned int i = 0; i < text.length(); i++) {
        
        // Adding white space around punctuations
        if(PUNCTUATION.find(text[i]) != string::npos) { 
            toReturn = toReturn + " " + text[i] + " ";
        } // Removing the unwanted characters
        else if(UNWANTED_CHARACTERS.find(text[i]) == string::npos) {
            toReturn += text[i];
        } 
    }
    // returns a more formatted string
    return toReturn;
}

void TextGenerator::populateTable(vector<string> & tokens) {
	// The first word of the text would be following a period 
	string curr = ".";
    vector<string> v;
    this->umap[curr] = v;

    // Loop through entire tokens vector to fill the hash map
    for(string key : tokens) {
        // If the key already exists within the hash map
        if(this->umap.find(key) != this->umap.end()) {
            umap[curr].push_back(key);
        }else { // If it doesn't exist, add it
            vector<string> tempVector;
            this->umap[key] = tempVector;
            this->umap[curr].push_back(key);
        }
        curr = key;
    } //end-for
}

vector<string> TextGenerator::tokenize(string & input) {
	vector<string> toReturn;
    string word;
    stringstream stream(input);
    
    // Tokenize based on white space
    while(getline(stream, word, ' ')) {
        // Add item to vector if it is not an empty string
        if(!word.empty()) {
            toReturn.push_back(word);
        }    
    }
    return toReturn;
}

string TextGenerator::genRand(vector<string> & v) {
	int total = v.size();
	int index = rand() % total;
	return v[index];
}

// Destructor
TextGenerator::~TextGenerator() {
	// Never used dynamically allocated memory
	// No need to call the destructor
}