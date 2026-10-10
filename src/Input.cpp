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
void Input::setCommand(std::string command)
{
    lastCommand = command;
}
void Input::setValue(std::string value)
{
    lastValue = value;
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
