#include "clothing.h"
#include "util.h"
#include <iomanip>
Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string brand, const std::string size) :
    Product(category, name, price, qty)
{
  brand_ = brand;
  size_ = size;
}

Clothing::~Clothing()
{

}

std::set<std::string> Clothing::keywords() const
{
  // create individual sets, add to main, convert into upper/lowercase
  std::set<std::string> main_set;
  std::set<std::string> name_set = parseStringToWords(name_);
  std::set<std::string> brand_set = parseStringToWords(brand_);

  main_set = setUnion(name_set, brand_set);
  return main_set;
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const
{
  return false;
}

std::string Clothing::displayString() const
{
  std::string output = name_ + "\nSize: " + size_ + " " + "Brand: " + brand_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.\n";
  return output;
}

void Clothing::dump(std::ostream& os) const
{
  os << category_ << "\n";
  os << name_ << "\n";
  os << price_ << "\n";
  os << qty_ << "\n";
  os << size_ << "\n";
  os << brand_ << "\n";
}