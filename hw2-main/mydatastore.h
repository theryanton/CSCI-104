#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <map>
#include <string>
#include <set>
#include <vector>
#include "datastore.h"
#include "product.h"
#include "product_parser.h"
#include "util.h"
#include "user.h"
#include <iostream>

class MyDataStore : public DataStore {
public:
    ~MyDataStore() { 
        for (std::vector<Product*>::iterator it = prodVector.begin(); it != prodVector.end(); ++it) {
            delete *it; // delete *it products
        }
        for (std::map<std::string, User*>::iterator it = userMap.begin(); it != userMap.end(); ++it) {
            delete it->second; // delete it->second (value)
        }
        for (std::map<std::string, std::vector<Product*>>::iterator it = cartMap.begin(); it != cartMap.end(); ++it) {
            delete &(it->second);
        }
        for (std::map<std::string, std::set<Product*>>::iterator it = prodSearches.begin(); it != prodSearches.end(); ++it) {
            delete &(it->second);
        }
    }

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

    void addToCart(const std::string& username, Product *p);
    void viewCart(const std::string& username); // iterate through user's cart, cout all items, iterate thru prodicts, user pointer and displaystring()
    void buyCart(const std::string& username); // iterate check if it can be biught, if not just leave in cart
private:
    std::vector<Product*> prodVector; // vector containing all products
    std::map<std::string, User*> userMap; // map linking users to username, check if user exists
    std::map<std::string, std::vector<Product*>> cartMap; // map that links each username to products in their cart
    std::map<std::string, std::set<Product*>> prodSearches; // map that links each search word to proper item
};

#endif