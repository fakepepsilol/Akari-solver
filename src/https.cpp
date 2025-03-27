#include <iostream>
#include <string>

std::string pathFromUrl(std::string url);
std::string inputUrl(int argc, char *argv[]) {
	std::string input;
	if (argc > 1) {
		input = argv[1];
	} else {
		std::cout << "> ";
		std::cin >> input;
	}

	return pathFromUrl(input);
}
std::string pathFromUrl(std::string url) {
	return url;
	if (url.length() < 8) {
		std::cerr << "Not a valid URL, exiting..\n";
		exit(1);
	}
	if (url.substr(0, 8) == "https://") {
		url = url.substr(8);
		goto ret;
	}
	if (url.substr(0, 7) == "http://") {
		url = url.substr(7);
		goto ret;
	}
ret:
	return url.substr(url.find('/'));
}
std::string execCurl(const std::string &command) {
	char        buffer[128];
	std::string result = "";

#ifdef _WIN32
	FILE *pipe = _popen(command.c_str(), "r");  // WIN
#else
	FILE *pipe = popen(command.c_str(), "r");  // LIN
#endif

	if (!pipe) { throw std::runtime_error("Failed to open pipe!"); }
	while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
		result += buffer;
	}

#ifdef _WIN32
	_pclose(pipe);  // WIN
#else
	fclose(pipe);  // LIN
#endif

	return result;
}

std::string runCurl(std::string url) {
	try {
		std::string command = "curl -s " + url;
		std::string output  = execCurl(command);
		return output;
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}
