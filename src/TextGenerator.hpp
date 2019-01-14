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

class TextGenerator {
public:
  unordered_map <string, vector<string>> umap;

  TextGenerator(const string & textDirectory);

  string generateNextWord(const string & prevWord);

  string generateText(const int numWords);

  string removeChars(string & text);

  string genRand(vector<string> & tokens);

  vector<string> tokenize(string & input);

private:
  const string PUNCTUATION = ".!,?";
  const string UNWANTED_CHARACTERS = ";:\"~()[]{}\\/^_<>*=&%@$+|`";
  const string WHITESPACE = "\t\r\n\v\f";

  // Destructor
  ~TextGenerator();
};

#endif
