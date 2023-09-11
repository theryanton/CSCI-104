#include "book.h"
#include "util.h"
#include <iomanip>
Book::Book(const std::string category, const std::string name, double price, int qty, const std::string author, const std::string isbn) :
    Product(category, name, price, qty)
{
  author_ = author;
  isbn_ = isbn;
}

Book::~Book()
{

}

std::set<std::string> Book::keywords() const
{
  // create individual sets, add to main, convert into upper/lowercase
  std::set<std::string> main_set;
  std::set<std::string> name_set = parseStringToWords(name_);
  std::set<std::string> author_set = parseStringToWords(author_);

  main_set = setUnion(name_set, author_set);
  main_set.insert(isbn_);
  return main_set;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const
{
  return false;
}

std::string Book::displayString() const
{
  std::string output = name_ + "\nAuthor: " + author_ + " " + "ISBN: " + isbn_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
  return output;
}

void Book::dump(std::ostream& os) const
{
  os << category_ << "\n";
  os << name_ << "\n";
  os << price_ << "\n";
  os << qty_ << "\n";
  os << isbn_ << "\n";
  os << author_ << "\n";
}