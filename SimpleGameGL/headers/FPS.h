#pragma once  

#include <chrono>  
#include <iostream>

class FPS {
private:

	int fpsCount = 0;
	int fps = 0;
	std::chrono::steady_clock::time_point lastFpsTime = std::chrono::high_resolution_clock::now();

	std::chrono::steady_clock::time_point currentTime;
	std::chrono::milliseconds deltaTime;

public:
	void Update() {
		currentTime = std::chrono::high_resolution_clock::now();
		fpsCount++;
		deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastFpsTime);
		if (deltaTime.count() >= 1000) {
			fps = fpsCount;
			fpsCount = 0;
			lastFpsTime = currentTime;
			std::cout << fps << std::endl;
		}
	}
};
