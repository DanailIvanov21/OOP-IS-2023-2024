pragma once
#ifndef EVENT_H
#define EVENT_H
#include <cstring>
#include <iostream>

class Event {

private:
	char* event;

public:
	Event();
	Event(const char* event);
	~Event();

	void setEvent(const char* event);
	const char* getEvent()const;

	void cpyEvent(const Event& event);
	void printEvent()const;
};

#endif // EVENT_H




________
#include "Event.h"


Event::Event() {

	const size_t max = 7;
	event = new char[max + 1];
	strcpy_s(event, max + 1, "koncert");
}

Event::Event(const char* event) {

	size_t size = strlen(event);
	this->event = new char[size + 1];
	strcpy_s(this->event, size + 1, event);
}

Event::~Event() {


	delete[] this->event;
	
}

void Event::setEvent(const char* event) {

	size_t size = strlen(event);
	this->event = new char[size + 1];
	strcpy_s(this->event, size + 1, event);
}

const char* Event::getEvent()const {

	return this->event;
}

void Event::cpyEvent(const Event& event) {

	setEvent(event.getEvent());
}

void Event::printEvent()const {

	std::cout << event << std::endl;
}


--------
#pragma once
#ifndef EVENT_LOG_H
#define EVENT_LOG_H
#include "Event.h"

class EventLog {

private:
	Event* events;
	size_t currentSize;
	size_t capacity;

public:
	EventLog();
	EventLog(Event* events, size_t currentSize, size_t capacity);
	~EventLog();

	void addEvent(const Event& event);
	void print()const;
	void setSize(size_t size);
	void setCapacity(size_t cap);

	Event getEventAt(size_t index)const;
	size_t getSize()const;
	size_t getCapacity()const;
};

#endif // EVENT_LOG_H

_______
#include "EventLog.h"

EventLog::EventLog() {

	capacity = 1;
	currentSize = 1;
	events = new Event[capacity];
	events[0].setEvent("koncert");
}

EventLog::EventLog(Event* events, size_t currentSize, size_t capacity)
	: currentSize(currentSize), capacity(capacity) {

	if (currentSize > capacity) {
		this->capacity = currentSize;
		this->currentSize = capacity;
	}

	this->events = new Event[this->capacity];

	for (size_t i = 0; i < currentSize; ++i) {
		this->events[i].cpyEvent(events[i]);
	}
}

EventLog::~EventLog() {

	currentSize = 0;
	capacity = 0;
	delete[] events;
}

void EventLog::addEvent(const Event& event) {

	if (currentSize == capacity) {
		return;
	}

	events[currentSize].cpyEvent(event);
	++currentSize;
}

void EventLog::print()const {

	for (size_t i = 0; i < currentSize; ++i) {
		events[i].printEvent();
	}
}

void EventLog::setSize(size_t size) {

	if (size > 0 && size < capacity) {
		currentSize = size;
	}
}

void EventLog::setCapacity(size_t cap) {

	if (cap > 0 && cap > capacity) {
		capacity = cap;
	}
}

Event EventLog::getEventAt(size_t index)const {

	if (index < 0 || index > currentSize) {
		// throw "Invalid index";
		std::cout << "Invalid index!\n";
		return events[0];
	}

	return events[index];
}

size_t EventLog::getSize()const {

	return currentSize;
}

size_t EventLog::getCapacity()const {

	return capacity;
}


-----


#include <iostream>
#include"EventLog.h"

const size_t Size = 3;
const size_t Capacity = 5;

int main() {

	Event e1("match");
	Event e2("concert");
	Event e3("exam");

	Event events[Size];
	events[0].cpyEvent(e1);
	events[1].cpyEvent(e2);
	events[2].cpyEvent(e3);

	EventLog log(events, Size, Capacity);

	Event e4("wedding");

	log.addEvent(e4);
	log.print();

	return 0;
}


