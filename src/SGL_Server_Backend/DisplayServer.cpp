#include "DisplayServer.h"

DisplayServer::DisplayServer() {};

void DisplayServer::setArea(long windowID, Area area) {};
// Area DisplayServer::getArea(long windowID) {
// 	Area foo;
// 	return foo;
// };
// Area DisplayServer::getScreenSize(long screenID) {
// 	Area foo;
// 	return foo;
// };
std::vector<long> DisplayServer::getScreens() {
	std::vector<long> foo;
	return foo;
};
std::vector<long> DisplayServer::getWindows(long screenID) {
	std::vector<long> foo;
	return foo;
};
void DisplayServer::setInitCallback(InitHandlerFn fn) {};
void DisplayServer::setEventCallback(EventHandlerFn fn) {};
void DisplayServer::run() {};