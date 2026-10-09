#include "Input.h"
#include <sstream>
#include <iostream>

void Input::inputCommand()
{
  std::getline(std::cin, lastCommand);
  std::istringstream stream(lastCommand);

  stream >> lastCommand;
  stream >> lastValue;

}

void Input::reset()
{
    lastCommand.clear();
    lastValue.clear();
}
std::string Input::getCommand()
{
    std::istringstream stream(lastCommand);

    stream >> lastCommand;

    return lastCommand;
}

std::string Input::getValue()
{
    return lastValue;
}
