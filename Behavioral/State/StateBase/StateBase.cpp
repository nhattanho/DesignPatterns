#pragma once
#include <iostream>
#include <typeinfo>
#define className typeid(this).name();

using namespace std;
class Engine;

class StateBase
{
protected:
	Engine* _engine;

public:
	virtual ~StateBase() {}

	void set_engine(Engine* engine) {
		_engine = engine;
	}

	// Pure virtual functions <=> no implementation.
	// Any subclass must override this function,
	// or it will also be abstract.
	virtual void DoWorkA() = 0;
	virtual void DoWorkB() = 0;
};

class Engine {
private: StateBase* _state;

public:
	Engine(StateBase* state) {
		_state = nullptr;
		TransitionTo(state);
	}

	~Engine() { delete _state; }

	void TransitionTo(StateBase* state) {
		if (_state) delete _state;

		_state = state;
		_state->set_engine(this);
	}

	void RequestA() {
		_state->DoWorkA();
	}

	void RequestB() {
		_state->DoWorkB();
	}
};

class ConcreteStateA : public StateBase {
public:
	void DoWorkA() override {
		cout << " StateA called DoWorkA()\n";
	}

	void DoWorkB() override {
		cout << " StateA called DoWorkB()\n";
	}
};

class ConcreteStateB : public StateBase {
public:
	void DoWorkA() override {
		cout << " StateB called DoWorkA()\n";
		_engine->TransitionTo(new ConcreteStateA());
	}

	void DoWorkB() override {
		cout << " StateB called DoWorkB()\n";
	}
};

int main() {
	Engine engine1(new ConcreteStateB());
	engine1.RequestA();
	engine1.RequestB();
}