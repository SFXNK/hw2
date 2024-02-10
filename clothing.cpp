#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) :
    Product::Product(category, name, price, qty),
    size_(size),
    brand_(brand)
{

}

Clothing::~Clothing()
{

}

std::set<std::string> Clothing::keywords()const{
  std::string keyw;
  keyw=convToLower(name_+std::string(" ")+brand_);
  std::set<std::string> res=parseStringToWords(keyw);
  return res;
}

std::string Clothing::displayString()const{
  std::string res=name_+std::string("\n")+std::string("Size: ")+size_+std::string(" Brand: ")+brand_+std::string("\n")+std::to_string(price_)+std::string(" ")+std::to_string(qty_)+std::string(" left. ");
  return res;
}

void Clothing::dump(std::ostream& os)const
{
    os << displayString() << std::endl;
}

void Clothing::write(std::ostream& os)const{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << std::endl;
}
