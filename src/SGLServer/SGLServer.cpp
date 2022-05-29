#include "SGLServer.h"

// SGLServer::SGLServer() {};

// void SGLServer::setArea(long windowID, Area area) {};
// Area SGLServer::getArea(long windowID) {
// 	Area foo;
// 	return foo;
// };
// Area SGLServer::getScreenSize(long screenID) {
// 	Area foo;
// 	return foo;
// };
std::vector<long> SGLServer::getScreens() {
	std::vector<long> foo;
	return foo;
};
std::vector<long> SGLServer::getWindows(long screenID) {
	std::vector<long> foo;
	return foo;
};
void SGLServer::setInitCallback(InitHandlerFn fn) {};
void SGLServer::setEventCallback(EventHandlerFn fn) {};
void SGLServer::run() {};