#include "mydatastore.h"
#include "util.h"
#include <iostream>

    MyDataStore::~MyDataStore() { 
      for(std::vector<Product*>::iterator it=products_.begin();it!=products_.end();it++){
        delete (*it);
      }
      for(std::vector<User*>::iterator it=users_.begin();it!=users_.end();it++){
        delete (*it);
      }
    }

    void MyDataStore::addProduct(Product* p){
      products_.push_back(p);
      std::set<std::string> kwd=p->keywords();
      for(std::set<std::string>::iterator it=kwd.begin();it!=kwd.end();it++){
        if(keymap_.count(*it)){
          keymap_.find(*it)->second.insert(p);
        }
        else{
          std::set<Product*> tmp;
          tmp.insert(p);
          keymap_.insert(std::make_pair((*it),tmp));
          //std::cout<<*it<<":      "<<p->getName()<<std::endl;
        }
      }
    }

    /**
     * Adds a user to the data store
     */
    void MyDataStore::addUser(User* u){
      users_.push_back(u);
    }

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
      std::set<Product*> res;
      if(type==0){
        for(std::vector<std::string>::iterator it=terms.begin(); it!=terms.end(); it++){
          if(keymap_.count(*it)){
            if(res.empty()){
              res=keymap_.find(*it)->second;
            }
            else{
              res=setIntersection(res,keymap_.find(*it)->second);
            }
          }
        }
      }
      else{
        for(std::vector<std::string>::iterator it=terms.begin(); it!=terms.end(); it++){
          if(keymap_.count(*it)){
            if(res.empty()){
              res=keymap_.find(*it)->second;
            }
            else{
              res=setUnion(res,keymap_.find(*it)->second);
            }
          }
        }
      }
      std::vector<Product*> resvec;
      for(std::set<Product*>::iterator it=res.begin(); it!=res.end(); it++){
        resvec.push_back(*it);
      }
      return resvec;
    }

    /**
     * Reproduce the database file from the current Products and User values
     */
    void MyDataStore::dump(std::ostream& ofile){
      ofile<<"<products>"<<std::endl;
      for(std::vector<Product*>::iterator it=products_.begin();it!=products_.end();it++){
        (*it)->write(ofile);
      }
      ofile<<"</products>"<<std::endl;
      ofile<<"<users>"<<std::endl;
      for(std::vector<User*>::iterator it=users_.begin();it!=users_.end();it++){
        (*it)->dump(ofile);
      }
      ofile<<"</users>"<<std::endl;
    }

    bool MyDataStore::checkUser(std::string username){
      for(int i=0;i<users_.size();i++){
        if(users_[i]->getName()==username){
          return true;
        }
      }
      return false;
    }

    User* MyDataStore::findUser(std::string username){
      for(int i=0;i<users_.size();i++){
        if(users_[i]->getName()==username){
          return users_[i];
        }
      }
      return nullptr;
    }