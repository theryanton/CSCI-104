#include "movie.h"
#include "util.h"
#include <iomanip>

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) :
    Product(category, name, price, qty)
{
  genre_ = genre;
  rating_ = rating;
}

Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const
{
  // create individual sets, add to main, convert into upper/lowercase
  
  std::set<std::string> main_set; // set of keywords
  std::string tempString;

  unsigned int ratingIndex = 0;
  while (ratingIndex != rating_.size())
  {
    tempString += tolower(rating_[ratingIndex]);
    ratingIndex++;
  }
  main_set.insert(tempString);
  tempString = "";

  unsigned int genreIndex = 0;
  while (genreIndex != genre_.size()) 
  {
    tempString += tolower(genre_[genreIndex]);
    genreIndex++;
  }
  main_set.insert(tempString);
  tempString = "";

  for (unsigned int i = 0; i < name_.size(); ++i) // solves issues with case insensitive test case, names can be read in and outputted without changing case
  {
    if ((std::ispunct(name_[i]) && (tempString.size() >= 2)) || (std::isspace(name_[i]) && (tempString.size() >= 2))) 
    {
      main_set.insert(tempString);
      tempString = "";
    }  
    else if (std::ispunct(name_[i]) || std::isspace(name_[i])) // cut off string at punctuation/space
    {
      tempString = "";
    }
    else 
    {
      tempString += std::tolower(name_[i]);
    }
  }

  if (tempString.size() >= 2) 
  {
    main_set.insert(tempString);
    tempString = "";
  }
  return main_set;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const
{
  return false;
}

std::string Movie::displayString() const
{
  std::string output = name_ + "\nGenre: " + genre_ + " " + "Rating: " + rating_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.\n";
  return output;
}

void Movie::dump(std::ostream& os) const
{
  os << category_ << "\n";
  os << name_ << "\n";
  os << price_ << "\n";
  os << qty_ << "\n";
  os << genre_ << "\n";
  os << rating_ << "\n";
}