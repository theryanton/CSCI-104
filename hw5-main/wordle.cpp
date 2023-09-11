// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
std::set<std::string> recurseHelper(std::string wordGuess, const std::string& in, const std::string& floating, const std::set<std::string>& dict);
bool checkIfInString (char letter, const std::string& floating);
bool wordValid (std::string wordGuess, const std::set<std::string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    // in  means characters plus letter in correct spot
    // floating is chars that are guessed, function will spit back words that contain it
    std::set<std::string> allPossibilities = recurseHelper("", in, floating, dict);
    return allPossibilities;

}

// Define any helper functions here

std::set<std::string> recurseHelper(std::string wordGuess, const std::string& in, const std::string& floating, const std::set<std::string>& dict)
{
  if (wordGuess.size() != in.size())
  {
    unsigned int letterMatches = 0; // keep track of valid letters right now
    for (unsigned int i=wordGuess.size(); i<in.size(); i++)
    {
      if (in[i] != '-')
      {
        letterMatches++; // we gucci, letters are there
      }
    }
    std::set<std::string> full_set;
    if (in[wordGuess.size()] != '-')
    {
      std::set<std::string> to_add;
      to_add = recurseHelper(wordGuess + in[wordGuess.size()], in, floating, dict);
      for (std::set<std::string>::iterator it = to_add.begin(); it != to_add.end(); ++it)
      {
        full_set.insert(*it);
      }
    }
    else 
    {
      for (unsigned int i=0; i<floating.size(); i++)
      {
        std::string floating_copy = floating;
        if (floating.size() == 1) // base case, only 1 char in str, null char
        {
          floating_copy = "";
        }
        else
        {
          floating_copy.erase(floating_copy.begin() + i);
        }
        std::set<std::string> to_add;
        to_add = recurseHelper(wordGuess + floating[i], in, floating_copy, dict);
        for (std::set<std::string>::iterator it = to_add.begin(); it != to_add.end(); ++it)
        {
          full_set.insert(*it);
        }
      }
      if (in.size() - wordGuess.size() - letterMatches > floating.size())
      {
        for (int i=97; i<=122; i++)
        {
          std::string floating_copy = floating;
          if (checkIfInString((char)i, floating))
          {
            if(floating.size() == 1)
            {
              floating_copy = "";
            }
            else
            {
              floating_copy = floating.substr(0, floating.find((char)i)) + floating.substr(floating.find((char)i)+1, floating.size());
            }
          }
          std::set<std::string> to_add; 
          to_add = recurseHelper(wordGuess + (char)i, in, floating_copy, dict);
          for (std::set<std::string>::iterator it = to_add.begin(); it != to_add.end(); ++it)
          {
            full_set.insert(*it);
          }
        }
      }
    }
    return full_set;
  }
  else // base case, the word we're guessing fits the in
  {
    if (wordValid(wordGuess, dict)) // could find word
    {
      std::set<std::string> foundWords; // found one word 
      foundWords.insert(wordGuess);
      return foundWords;
    }
    else
    {
      std::set<std::string> emptySet = {};
      return emptySet;
    }
  }
}

bool checkIfInString (char letter, const std::string& floating) // checks if inputted letter is within str
{
  if (floating.find(letter) != std::string::npos)
  {
    return true;
  }
  return false;
}

bool wordValid (std::string wordGuess, const std::set<std::string>& dict)
{
  if (dict.find(wordGuess) != dict.end())
  {
    return true;
  }
  return false;
}