#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) :
    Product::Product(category, name, price, qty),
    genre_(genre),
    rating_(rating)
{

}

Movie::~Movie()
{

}

std::set<std::string> Movie::keywords()const{
  std::string keyw;
  keyw=convToLower(name_+std::string(" ")+genre_);
  std::set<std::string> res=parseStringToWords(keyw);
  return res;
}

std::string Movie::displayString()const{
  std::string res=name_+std::string("\n")+std::string("Genre: ")+genre_+std::string(" Rating: ")+rating_+std::string("\n")+std::to_string(price_)+std::string(" ")+std::to_string(qty_)+std::string(" left. ");
  return res;
}

void Movie::dump(std::ostream& os)const
{
  os << displayString() << std::endl;
}

void Movie::write(std::ostream& os)const{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
}

