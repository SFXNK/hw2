#include "user.h"
using namespace std;

User::User() : name_("unknown"), balance_(0.0), type_(1)
{

}
User::User(std::string name, double balance, int type) :
    name_(name), balance_(balance), type_(type)
{

}

User::~User()
{

}


std::string User::getName() const
{
    return name_;
}

double User::getBalance() const
{
    return balance_;
}

void User::deductAmount(double amt)
{
    balance_ -= amt;
}

void User::dump(std::ostream& os)
{
    os << name_ << " "  << balance_ << " " << type_ << endl;
}


void User::addCart(Product* p){
  cart_.push_back(p);
}
std::vector<Product*> User::getCart(){
  return cart_;
}
void User::buyCart(){
  std::vector<Product*> newcart;
  for(int i=0;i<cart_.size();i++){
    if(balance_>=cart_[i]->getPrice() && cart_[i]->getQty()>=1){
      balance_-=cart_[i]->getPrice();
      cart_[i]->subtractQty(1);
    }
    else{
      newcart.push_back(cart_[i]);
    }
  }
  cart_=newcart;
}