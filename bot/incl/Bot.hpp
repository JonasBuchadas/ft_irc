#pragma once
#ifndef __BOT_HPP__
#define __BOT_HPP__

#include <map>
#include <vector>
#include <iostream>

class Bot {
 private:
  std::map<std::string, std::map<int, std::string> > _asks;
  std::map<std::string, bool>                        _isOpen;
  std::vector<std::string>                           _users;

 public:
  Bot();
  Bot( Bot const &src );
  Bot  &operator=( Bot const &src );
  ~Bot();

  void addUser( std::string nick );
  void rmvUser( std::string nick );
  void setIsOpen( std::string id, bool open );
  void setAsk( std::string id, std::string msg );
  void rmAsk( std::string id, int num );

  bool                      getIsOpen( std::string id );
  std::vector<std::string>  getAllUsers();
  std::string               getUser( std::string nick );
  std::string               getOption( std::string Ask, int option );
  int                       getAsk( std::string id );
  std::map<std::string, std::map<int, std::string> >  getAllAsk();

};

#endif
