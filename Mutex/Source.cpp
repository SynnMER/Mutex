#include <iostream>
#include <mutex>
#include <string>

// Mutex - помогает синхронихировать потоки. Блокирует проход потока через строчку.
//Mutex, deadlock, recursive mutex
class Logger {
	public:
		//race_conditon
		void log(const std::string& message) {
			std::lock_guard<std::mutex> lock(_mutex);
			std::cout << "[" << counter << "]" << std::endl;
			counter++;
		}
private:
	int counter = 0;
	std::mutex _mutex;
};


int main() {
	Logger logger;
	logger.log("Hello");
	logger.log("Info message");
	std::cout << "Hello world\n";

	std::thread t1 = std::thread([&logger]() {
		std::string threadName = "t1";
		for (size_t i = 0; i < 100; i++) {
			logger.log(threadName + " doing" + std::to_string(i) + " iteration of work");
		}
		});

	std::thread t2 = std::thread([&logger]() {
		std::string threadName = "t2";
		for (size_t i = 0; i < 100; i++) {
			logger.log(threadName + " doing" + std::to_string(i) + " iteration of work");
		}
		});


	t1.join(); t2.join();










}