#include "../include/ConnectionHandler.h"
#include "Frame.h"
#include "../include/user.h"

using boost::asio::ip::tcp;

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;



ConnectionHandler::ConnectionHandler(string host, short port) : host_(host), port_(port), io_service_(),
                                                                socket_(io_service_),user(User()),frame(Frame()),alive(true){}

ConnectionHandler::~ConnectionHandler() {
	close();
}

bool ConnectionHandler::connect() {
	std::cout << "Starting connect to "
	          << host_ << ":" << port_ << std::endl;
	try {
		tcp::endpoint endpoint(boost::asio::ip::address::from_string(host_), port_); // the server endpoint
		boost::system::error_code error;
		socket_.connect(endpoint, error);
		if (error)
			throw boost::system::system_error(error);
	}
	catch (std::exception &e) 
	{
		std::cerr << "Connection failed (Error: " << e.what() << ')' << std::endl;
		alive = false;
		return false;
	}
	return true;
}

bool ConnectionHandler::getBytes(char bytes[], unsigned int bytesToRead) {
	size_t tmp = 0;
	boost::system::error_code error;
	try {
		while (!error && bytesToRead > tmp) {
			tmp += socket_.read_some(boost::asio::buffer(bytes + tmp, bytesToRead - tmp), error);
		}
		if (error)
			throw boost::system::system_error(error);
	} catch (std::exception &e) 
	{
		std::cerr << "recv failed (Error: " << e.what() << ')' << std::endl;
		alive = false;
		return false;
	}
	return true;
}

bool ConnectionHandler::sendBytes(const char bytes[], int bytesToWrite) {
	int tmp = 0;
	boost::system::error_code error;
	try {
		while (!error && bytesToWrite > tmp) {
			tmp += socket_.write_some(boost::asio::buffer(bytes + tmp, bytesToWrite - tmp), error);
		}
		if (error)
			throw boost::system::system_error(error);
	} catch (std::exception &e) {
		std::cerr << "recv failed (Error: " << e.what() << ')' << std::endl;
		alive = false;
		return false;
	}
	return true;
}

bool ConnectionHandler::getLine(std::string &line) 
{
	
	bool answer = getFrameAscii(line, '\0');
	//cout << line << endl;
	if(line != "")
		alive = frame.translateFrame(line,user);

	return answer;
}

bool ConnectionHandler::sendLine(std::string &line)
{
	if(line != "")
	{
		std::vector<string> messagesToSend = frame.toString(line,user);
		for(string message: messagesToSend)
		{
			//cout << message<< endl;
			if(message != "NO MESSAGE")
			{
				if(!sendFrameAscii(message, '\0'))
					return false;
			}
		}
	}

	return true;
}

bool ConnectionHandler:: isAlive()
{
	return alive;
}


bool ConnectionHandler::getFrameAscii(std::string &frame, char delimiter) 
{
	char ch;
	// Stop when we encounter the null character.
	// Notice that the null character is not appended to the frame string.
	try {
		do {
			if (!getBytes(&ch, 1)) {
				return false;
			}
			if (ch != '\0')
				frame.append(1, ch);
		} while (delimiter != ch);
	} catch (std::exception &e) {
		std::cerr << "recv failed2 (Error: " << e.what() << ')' << std::endl;
		alive = false;
		return false;
	}
	return true;
}

bool ConnectionHandler::sendFrameAscii(const std::string &frame, char delimiter) {
	bool result = sendBytes(frame.c_str(), frame.length());
	if (!result) return false;
	return sendBytes(&delimiter, 1);
}

// Close down the connection properly.
void ConnectionHandler::close() {
	try {
		socket_.close();
	} catch (...) {
		std::cout << "closing failed: connection already closed" << std::endl;
	}
}


