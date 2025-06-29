#include <iostream>
#include <string>
#include <vector>

// Class: Iterator<T, U>
// T: the data type stored in the container(e.g., int).
// U : the type of the container(e.g., Container<int>).
// This allows the Iterator to work with different container types.
template <typename T, typename U>
class Iterator {
public:
    // it_type is an alias for the iterator type of std::vector<T>.
    typedef typename std::vector<T>::iterator it_type;

    Iterator(U* container) : _data_ref(container) {
        _it = _data_ref->_data.begin();
    }

    void First() {
        _it = _data_ref->_data.begin();
    }

    void Next() {
        _it++;
    }

    bool AtEnd() {
        return (_it == _data_ref->_data.end());
    }

    it_type Current() {
        return _it;
    }

private:
    U* _data_ref;
    it_type _it;
};

// Container<T> – a generic container holding elements of type T
template <typename T>
class Container {
    // friend declaration allows Iterator<T, Container> 
    // to access the private _data member.
    friend class Iterator<T, Container>;

public:
    void Add(T new_data) {
        _data.push_back(new_data);
    }

    Iterator<T, Container>* CreateIterator() {
        return new Iterator<T, Container>(this);
    }

private:
    std::vector<T> _data;
};


int main() {

    Container<int> our_data_bag;
    for (int i = 0; i < 10; i++) {
        our_data_bag.Add(i);
    }
    auto* our_iterator = our_data_bag.CreateIterator();

    for (our_iterator->First(); !our_iterator->AtEnd(); our_iterator->Next()) {
        std::cout << *our_iterator->Current() << std::endl;
    }

    return EXIT_SUCCESS;
}