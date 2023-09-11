#ifndef BOOK_H
#define BOOK_H
#include "product.h"
#include <iostream>

class Book : public Product { // inherit from product class
  public:
    Book(const std::string category, const std::string name, double price, int qty, const std::string author, const std::string isbn);
    ~Book();

    /**
     * Returns the appropriate keywords that this product should be associated with
     */
    std::set<std::string> keywords() const;

    /**
     * Allows for a more detailed search beyond simple keywords
     */
    bool isMatch(std::vector<std::string>& searchTerms) const;

    /**
     * Returns a string to display the product info for hits of the search
     */
    std::string displayString() const;

    /**
     * Outputs the product info in the database format
     */
    void dump(std::ostream& os) const;
  private:
    std::string author_, isbn_;
};
#endif