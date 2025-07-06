// Ensures the header is included only once during compilation.
#pragma once
#include <iostream>

class SingletonBase
{
public:
	// This deletes the copy constructor, so no one can
	// do SingletonBase copy = SingletonBase::Get();
	// Prevents accidental creation of multiple instances.
	SingletonBase(const SingletonBase&) = delete;

	// It returns a reference (&) to the single instance of SingletonBase.
	// If & is not used, copy the singleton instance and return a new
	// object, defeating the whole purpose of the singleton pattern,
	// even instance is defined as a static variable, because it only assures
	// that one internal SingletonBase obj is ever created, and return by value
	// will make it copy and return a copied instance, not exactly the original
	// object ==> to keep the Singleton works, need to return a reference.
	static SingletonBase& Get() {
		// Means it will create the object once,
		// the first time Get() is called.
		static SingletonBase instance;
		return instance;
	}

	static float GetFloat() {
		// SingletonBase& a = SingletonBase::Get();  // a refers to the singleton
		// SingletonBase& b = SingletonBase::Get();  // b refers to the same singleton
		return Get().IFloat();
	}


private:
	float IFloat() {
		return floatNum;
	}
	// SingletonBase() is a private constructor, so can't construct
	// this class directly (e.g., SingletonBase sb; would be illegal).
	SingletonBase(){}
	float floatNum = 0.5f;
};

int main() {
	// GetFloat() is a static method → it doesn't belong to
	// any instance, so must call it using the class name.
	float random = SingletonBase::GetFloat();

	std::cout << "Random float: " << random << std::endl;
	return 0;
}

