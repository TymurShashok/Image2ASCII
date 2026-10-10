#include <string>

class Input {

std::string lastCommand;
std::string lastValue;

public:

	void inputCommand();
	void reset();

	void setCommand(std::string command);
	void setValue(std::string value);

	std::string getCommand();
	std::string getValue();


};