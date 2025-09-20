#include "client.hpp"
#include "thread_safe_iostream.hpp"
#include <string>

int main() {
    Client client;

	client.defineAction(3, [](const Message& msg){
        int doubledValue;
        Message msgCopy = msg;
        msgCopy >> doubledValue;
        threadSafeCout << "Received a doubled value: " << doubledValue << std::endl;
    });

    client.connect("127.0.0.1", 8081);

    Message message1(1);
    message1 << 42;
    client.send(message1);

    Message message2(2);
    std::string str = "Hello";
    message2 << str.size();
    for (char c : str) {
        message2 << c;
    }
    client.send(message2);

	bool quit = false;

	while (!quit)
	{
		client.update();

		threadSafeCout << "Client updated." << std::endl;
		threadSafeCout << "Available operations :" << std::endl;
		threadSafeCout << " - [Q]uit : close the program" << std::endl;
		threadSafeCout << " - Any other input to continue updating the client" << std::endl;

		std::string input;
		std::getline(std::cin, input);

		std::transform(input.begin(), input.end(), input.begin(), 
		               [](unsigned char c){ return std::tolower(c); });

		if (input == "quit" || (input.length() == 1 && input[0] == 'q')) {
		    quit = true;
		}
	}

    client.disconnect();

    return 0;
}
