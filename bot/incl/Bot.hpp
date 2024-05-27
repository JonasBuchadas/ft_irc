#pragma once
#ifndef __BOT_HPP__
#define __BOT_HPP__

#include <map>
#include <vector>
#include <iostream>

class Bot {
 private:
  std::string                 _name;
  std::vector<int>            _operators;
  std::vector<int>            _users;
  std::map<std::string, std::map<int, std::string> > _aliases;
  std::map<std::string, bool>                        _isOpen;

 public:
  Bot();
  Bot( Bot const &src );
  Bot  &operator=( Bot const &src );
  ~Bot();

  void addOper( int fd );
  void addUser( int fd );
  void rmvOper( int fd );
  void rmvUser( int fd );
  void setName( std::string &name );
  void setIsOpen( std::string id, bool open );
  void setAlias( std::string id, std::string msg );
  void rmAlias( std::string id, int num );

  std::string       getName( void ) const;
  bool              getIsOpen( std::string id );
  std::vector<int>  getAllOpers();
  std::vector<int>  getAllUsers();
  int               getOper( int fd );
  int               getUser( int fd );
  std::string       getOption( std::string alias, int option );
  int               getAlias( std::string id );
  std::map<std::string, std::map<int, std::string> >  getAllAlias();

};

#endif
