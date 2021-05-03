#include <iostream>
#include "hole_punch_coordinator.hpp"

int main(){
	HolePunchCoordinator server;

	server.run();

	for(std::string in; std::getline(std::cin, in);){
		if(in == "exit"){
			break;
		}
	}

	server.stop();

	return 0;
}
