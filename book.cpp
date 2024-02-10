#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author) :
    Product::Product(category, name, price, qty),
    isbn_(isbn),
    author_(author)
{

}

Book::~Book()
{

}

std::set<std::string> Book::keywords()const{
  std::string keyw;
  keyw=convToLower(name_+std::string(" ")+author_);
  std::set<std::string> res=parseStringToWords(keyw);
  res.insert(isbn_);
  return res;
}

std::string Book::displayString()const{
  std::string res=name_+std::string("\n")+std::string("Author: ")+author_+std::string(" ISBN: ")+isbn_+std::string("\n")+std::to_string(price_)+std::string(" ")+std::to_string(qty_)+std::string(" left. ");
  return res;
}

void Book::dump(std::ostream& os)const
{
  os << displayString() << std::endl;
}

void Book::write(std::ostream& os)const{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ <<"\n"<<isbn_<<"\n"<<author_<< std::endl;
}

