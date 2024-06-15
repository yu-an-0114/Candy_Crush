#include <iostream>

template <typename T>
class Container {
private:
	T value;
public:
	Container(T val) : value(val) {}
	T getValue() const { return value; }
};
