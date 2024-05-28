#pragma once
#ifndef __ANSWERCOMMAND_HPP__
#define __ANSWERCOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class AnswerCommand : public ACommand {
 private:
 public:
  AnswerCommand( BotManager *BotManager, std::string args, std::string nick );
  ~AnswerCommand();
  AnswerCommand( AnswerCommand const &src );
  AnswerCommand &operator=( AnswerCommand const &src );
  std::string  execute() const;
};

#endif
