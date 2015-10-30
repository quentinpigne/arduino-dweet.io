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

#include "Dweet.h"

//Default constructor, called when a Dweet object is instantiated
Dweet::Dweet(Client& theClient) : client(theClient) {}

//Dweeting method
void Dweet::dweet(char* thing, char* data) {
	//Establishing connection with dweet.io
	client.connect("dweet.io", 80);

	//Sending POST request with json content
	client.print(F("POST /dweet/for/"));
	client.print(thing);
	client.println(F(" HTTP/1.1"));
	client.println(F("Host: dweet.io"));
	client.println(F("User-Agent: Arduino/1.0"));
	client.println(F("Accept: application/json"));
	client.println(F("Connection: close"));
	client.println(F("Content-Type: application/json"));
	client.print(F("Content-Length: "));
	client.println(strlen(data));
	client.println();
	client.println(data);

	//Stopping client
	client.stop();
}

char* Dweet::get_latest(char* thing) {
	//Establishing connection with dweet.io
	client.connect("dweet.io", 80);

	//Sending GET request
	client.print(F("GET /get/latest/dweet/for/"));
	client.print(thing);
	client.println(F(" HTTP/1.1"));
	client.println(F("Host: dweet.io"));
	client.println(F("User-Agent: Arduino/1.0"));
	client.println(F("Accept: application/json"));
	client.println(F("Connection: close"));
	client.println();

	//Waiting for response
	while(!client.available()) {}

	eatHeader();
	readLine();

	//Stopping client
	client.stop();

	return databuffer;
}

//Consume the header
void Dweet::eatHeader() {
	//Consume lines to the empty line between the end of the header and the beginning of the response body
	while(client.available()) {
		readLine();
		if(strlen(databuffer) == 0) break;
	}
}

//Put incoming data's first line into the data buffer
void Dweet::readLine() {
	//dataptr pointer points to the beginning of the buffer
	dataptr = databuffer;

	char c = client.read();
	while(client.available() && c != '\r') {
		*dataptr++ = c;
		c = client.read();
	}
	client.read();

	*dataptr = 0;
}