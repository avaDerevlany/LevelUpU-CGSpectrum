/*
Follow the provided videos in this chapter, recreating the hello world example code,
and reviewing how threading can be used in the maze game

Attempt the small challenges shown along the way to familiarise yourself with threading,
before moving into the next chapter
*/

#include "..\Section3Header.h"
#include <thread>
#include <iostream>
#include <chrono>

bool isEnded = false;
bool paused = false;
int threadValue = 0;
int threadValue2 = 0;

void HelloWorldThread()
{
	while (!isEnded)
	{
		threadValue++;
		if (threadValue > 1000) threadValue = 0;
	}
}

void HelloWorldThread2()
{
	while (!isEnded)
	{
		if (!paused)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(500));	 // update a bit slower
			threadValue2++;
		}
	}
}

void HelloWorldExample()
{
	isEnded = false;
	paused = false;
	threadValue = 0;
	threadValue2 = 0;
	char userInput;

	std::cout << "Hello World Threading Example from the videos:" << std::endl;
	std::cout << "    w: see current thread values" << std::endl;
	std::cout << "    e: pause thread 2" << std::endl;
	std::cout << "    q: quit" << std::endl;

	std::thread HelloWorld_Thread(HelloWorldThread);
	std::thread HelloWorld_Thread2(HelloWorldThread2);

	while (!isEnded)
	{
		std::cin >> userInput;

		if (userInput == 'q') isEnded = true;
		else if (userInput == 'w')
		{
			std::cout << "\nThread1 value: " << threadValue << std::endl;
			std::cout << "Thread2 value: " << threadValue2 << std::endl;
		}
		else if (userInput == 'e') paused = !paused;
	}

	HelloWorld_Thread.join();
	HelloWorld_Thread2.join();

}