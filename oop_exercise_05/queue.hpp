/* Ляшун Дмитрий Сергеевич, группа М8О-207Б-19 */
#include <cassert>
#include <memory>
#include <functional>
using namespace std;
template<class T>
class Myqueue;
template<class T>
struct Node {
    Node() = default;
    Node(const T& elem) : elem(elem) {
        next = make_shared<Node>();
    }
    ~Node() {
        next = nullptr;
        prev = nullptr;
    }
    T elem;
    shared_ptr<Node> next;
    shared_ptr<Node> prev;
};
template <typename T>
class forward_iterator : public std::iterator<std::forward_iterator_tag, T, int> {
    public:
        friend class Myqueue<T>;
        typedef forward_iterator<T> self_type;
        typedef std::forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef T &reference;
        typedef weak_ptr<Node<T> > pointer;
        typedef ptrdiff_t difference_type;
    private:
        pointer ptr;
        size_t index = 0;
        size_t size = 0;
        bool compatible(self_type const &other) const {
            auto s_ptr1 = ptr.lock();
            auto s_ptr2 = other.ptr.lock();
            return s_ptr1 == s_ptr2;
        }
    public:
        explicit forward_iterator(pointer ptr, size_t const size, size_t const index) : ptr(ptr), size(size), index(index) {}
        
        forward_iterator() = default;
        forward_iterator(forward_iterator const &o) = default;
        forward_iterator &operator=(forward_iterator const &o) = default;
        ~forward_iterator() = default;
    
        self_type &operator++() {
            if (index >= size) {
                throw std::out_of_range("Iterator cannot be incremented past the end of range.");
            }
            ++index;
            auto s_ptr = ptr.lock();
            ptr = s_ptr->next;
            return *this;
        }
    
        self_type operator++(int) {
            self_type tmp = *this;
            ++*this;
            return tmp;
        }
        
        bool operator==(self_type const &other) const {
            if (index == other.index) {
            	assert(compatible(other));
            	return true;
            }
            else  {
            	return false;
            }
        }
    
        bool operator!=(self_type const &other) const {
            return !(*this == other);
        }
    
        reference operator*() const {
            if (index >= size) {
                throw std::bad_function_call();
            }
            auto s_ptr = ptr.lock();
            return s_ptr->elem;
        }
    
        reference operator->() const {
            if (index >= size) {
                throw std::bad_function_call();
            }
            auto s_ptr = ptr.lock();
            return s_ptr->elem;
        }
};
template<class T>
class Myqueue {
    public:
        Myqueue() : size(0) {}
        ~Myqueue() = default;
        size_t Size() { return size; }
        auto Begin();
        auto End();
        void Insert(auto iterator, const T& elem);
        void Erase(auto iterator);
        T Top();
        void Push(const T);
        void Pop();
        
    private:
        shared_ptr<Node<T> > begin_ptr;
        shared_ptr<Node<T> > end_ptr;
        size_t size;
};
template<class T>
auto Myqueue<T>::Begin() {
    return forward_iterator<T>(begin_ptr, size, 0);
}
template<class T>
auto Myqueue<T>::End() {
    return forward_iterator<T>(end_ptr, size, size);
}
template<class T>
void Myqueue<T>::Insert(auto iterator, const T& elem) {
    auto new_elem = make_shared<Node<T> >(elem);
    if (iterator.index == size) {
        Push(elem);
    }
    else if (iterator.index == 0) {
        new_elem->next = begin_ptr;
        begin_ptr->prev = new_elem;
        begin_ptr = new_elem;
        ++size;
    }
    else {
        auto s_ptr = iterator.ptr.lock();
        s_ptr->prev->next = new_elem;
        new_elem->prev = s_ptr->prev;
        s_ptr->prev = new_elem;
        new_elem->next = s_ptr;
        ++size;
    }
}
template<class T>
void Myqueue<T>::Erase(auto iterator) {
    if (iterator.index == 0) {
        Pop();
    }
    else if (iterator.index == size-1) {
        end_ptr->prev->prev->next = end_ptr;
        end_ptr->prev = end_ptr->prev->prev;
        --size;
    }
    else {
        auto s_ptr = iterator.ptr.lock();
        s_ptr->next->prev = s_ptr->prev;
        s_ptr->prev->next = s_ptr->next;
        --size;
    }
}
template<class T>
void Myqueue<T>::Push(const T elem) {
    if (size == 0) {
        begin_ptr = make_shared<Node<T> >(elem);
        end_ptr = begin_ptr->next;
        end_ptr->prev = begin_ptr;
    }
    else {
        end_ptr->elem = elem;
        end_ptr->next = make_shared<Node<T> >();
        end_ptr->next->prev = end_ptr;
        end_ptr = end_ptr->next;
    }
    ++size;
}
template<class T>
void Myqueue<T>::Pop() {
    if (size == 0) {
        throw std::bad_function_call();
    }
    begin_ptr->next->prev = nullptr;
    begin_ptr = begin_ptr->next;
    --size;
}
template<class T>
T Myqueue<T>::Top() {
    if (size == 0) {
        throw std::bad_function_call();
    }
    return begin_ptr->elem;
}
