#include "mydatastore.h"
#include <iostream>

void MyDataStore::addProduct(Product* p)
{
  prodVector.push_back(p); // add product to product vector
  std::set<std::string> tempstrings = p->keywords();
  std::set<std::string>::iterator it;
  for (it = tempstrings.begin(); it != tempstrings.end(); ++it) {
    if (prodSearches.find(*it) != prodSearches.end())
    {
      prodSearches[*it].insert(p);
    }
    else
    {
      std::set<Product*> tempset;
      tempset.insert(p);
      prodSearches.insert(make_pair(*it,tempset));
    }
  }
  // get list of keywords for this product p, iterate through each keyword, search inside prodsearches, for each product search inside map to see if it already exists
}

void MyDataStore::addUser(User *u)
{
  userMap.insert(make_pair(u->getName(), u));
  std::vector<Product*> tempCart;
  cartMap.insert(make_pair(u->getName(), tempCart));
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
  std::set<Product*> productSet;
  //productSet = prodSearches[terms[0]];
  if (type == 1) // type 1 = OR search (union of results for each term)
  {
    for (unsigned int i=0; i<terms.size(); ++i)
    {
      if (prodSearches.find(terms[i]) != prodSearches.end()) // check if keyword already exists
      {
        productSet = setUnion(productSet, prodSearches.at(terms[i]));
      }
    }
  }
  if (type == 0) // type 0 = AND search (intersection of results for each term)
  {
    for (unsigned int i=0; i<terms.size(); ++i)
    {
      if (prodSearches.find(terms[i]) != prodSearches.end()) 
      {
        if (productSet.empty()) 
        {
          productSet = prodSearches.at(terms[i]);
        }
        else
        {
          productSet = setIntersection(productSet, prodSearches.at(terms[i]));
        }
      }
    }
  }
 
  std::vector<Product*> searchHits(productSet.begin(), productSet.end()); // transform set into vector
  return searchHits;
}

void MyDataStore::dump(std::ostream& ofile)
{
  //iterate through map of users and product vector, output everything
  std::vector<Product*>::iterator prodit;
  ofile << "<products>\n";
  for (prodit = prodVector.begin(); prodit != prodVector.end(); ++prodit)
  {
    // ofile << "\n";
    (*prodit)->dump(ofile);
  }
  ofile << "</products>\n" << "<users>\n";
  std::map<std::string, User*>::iterator userit;
  for (userit = userMap.begin(); userit != userMap.end(); ++userit)
  {
    (userit->second)->dump(ofile); // dererference pointer
  }
  ofile << "</users>\n";
  return;
}

void MyDataStore::addToCart(const std::string& username, Product* p)
{
  // add product to user's cart using cart map
  if (userMap.find(username) != userMap.end())
  {
    if (cartMap.find(username) != cartMap.end())
    {
      std::map<std::string, std::vector<Product*>>::iterator it = cartMap.find(username);
      it->second.push_back(p);
    }
    else // username exists but does not have a cart
    {
      std::vector<Product*> tempProduct;
      tempProduct.push_back(p);
      cartMap.insert(make_pair(username, tempProduct));
    }
  }
  else
  {
    std::cout << "Invalid request\n";
    return;
  }
}

void MyDataStore::viewCart(const std::string& username)
{
  if (cartMap.find(username) != cartMap.end())
  {
    std::map<std::string, std::vector<Product*>>::iterator it = cartMap.find(username);
    for (unsigned int i=0; i<it->second.size(); ++i)
    {
      std::cout << "Item: " << i+1 << '\n' << it->second[i]->displayString() << "\n";
    }
  }
  else
  {
    std::cout << "Invalid username\n";
  }
  return;
}

void MyDataStore::buyCart(const std::string& username)
{
  if (cartMap.find(username) != cartMap.end())
  {
    std::map<std::string, std::vector<Product*>>::iterator it = cartMap.find(username);
    std::vector<Product*> tempProduct = it->second; // temp vector holding exact cart
    std::vector<Product*> tempCart;
    for (unsigned int i = 0; i < tempProduct.size(); i++) // iterate thru vector of products
    {
      if (userMap.find(username)->second->getBalance() < tempProduct[i]->getPrice())
      {
        tempCart.push_back(tempProduct[i]);
      }
      else if (!tempProduct[i]->getQty())
      {
        tempCart.push_back(tempProduct[i]);
      }
      else
      {
        userMap.find(username)->second->deductAmount(tempProduct[i]->getPrice());
        tempProduct[i]->subtractQty(1);
      }
    }
    cartMap.find(username)->second = tempCart;
  }
  else
  {
    std::cout << "Invalid username\n";
  }
  return;
}