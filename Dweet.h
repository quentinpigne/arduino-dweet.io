/*
	arduino-dweet.io: A dweet.io client for Arduino

	The MIT License (MIT)

	Copyright (c) 2015 Quentin Pigné

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#ifndef DWEET_H
#define DWEET_H

#include <Arduino.h>
#include <Client.h>

//Length of static data buffer
#define DATA_BUFFER_LEN 200

class Dweet {
	public:
		Dweet(Client& client);
		//"Dweeting" method
		void dweet(char* thing, char* data);
		//Getting latest dweet
		char* get_latest(char* thing);

	private:
		Client& client;
		//Incoming data reading attributes
		char databuffer[DATA_BUFFER_LEN];
		char* dataptr;

		//Private incoming data reading methods
		void eatHeader();
		void readLine();
};

#endif //DWEET_H