/* filename: TextGenerator.hpp
 * name : Steven Tran
 * start date: 12/10/18
 */

#ifndef TEXTGENERATOR_HPP
#define TEXTGENERATOR_HPP

#include <iostream> // terminal output
#include <fstream> // file opening
#include <vector>
#include <algorithm> // cpp sort

/*
 * This program builds a text from another provided text document. It utilized the 
 * Markov Text Generation data structure to accomplish this.
 *
 *
 */
class TextGenerator {
public:
  unordered_map <string, vector<string>> umap;

  /*
   * Builds a textGenerator object using the provided directory.
   * This opens all of the files within the given directory, reads them in, and
   * tokenizes them into individual words and punctuations.
   */
  TextGenerator(const string & textDirectory);

  /* 
   * Function that generates the next word to output.
   * It calls on the random function to find the next word.
   */
  string generateNextWord(const string & prevWord);

  string generateText(const int numWords);

  string removeChars(string & text);

  /*
   * random number generator that scales based on the size of the passed in vector
   * and then indexes the element at the random index in the vector
   */
  string genRand(vector<string> & tokens);

  // Fills the hash table with string keys and vetors
  void populateTable(vector<string> & tokens);

  vector<string> tokenize(string & input);

private:
  const string PUNCTUATION = ".!,?";
  const string UNWANTED_CHARACTERS = ";:\"~()[]{}\\/^_<>*=&%@$+|`";
  const string WHITESPACE = "\t\r\n\v\f";

  // Destructor
  ~TextGenerator();
};

#endif
