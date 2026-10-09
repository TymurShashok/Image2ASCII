#include <string>

class Input {

std::string lastCommand = "DWADAWD";
std::string lastValue;

public:

	void inputCommand();
	void reset();

	std::string getCommand();
	std::string getValue();
};