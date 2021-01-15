/* Ляшун Дмитрий Сергеевич, группа М8О-207Б-19 */
#include <queue>
#include <cassert>
#include <memory>
#include <functional>
using namespace std;
template<class T, size_t SIZE> 
class my_allocator {
    private:
        T* buffer;
        std::queue<T*> q;
    public:
        using value_type = T;
        using pointer = T *;
        using const_pointer = const T *;
        using size_type = std::size_t;
    
        template <class U>
        struct rebind {
            using other = my_allocator<U, SIZE>;
        };
        my_allocator() : buffer(nullptr) {
            static_assert(SIZE > 0);
        }
        ~my_allocator() {
            delete[] buffer;
        }
        T *allocate(size_t n) {
            if (buffer == nullptr) {
                buffer = new T[SIZE];
                for (int i = 0; i < SIZE; ++i) {
                    q.push(&buffer[i]); // buffer + i
                }
            }
            else if (q.size() < n) {
                return throw(std::bad_alloc());
            }
            else {
                T* res = q.front();
                for (int i = 0; i < n; ++i) {
                    q.pop();
                }
                return res;
            }
        }
        void deallocate(T* pointer, size_t n) {
            for (int i = 0; i < n; ++i) {
                q.push(pointer[i]);
            }
        }
        
        template <typename U, typename... Args>
        void construct(U *p, Args &&... args)
        {
            new (p) U(std::forward<Args>(args)...);
        }
        void destroy(pointer p)
        {
            p->~T();
        }
};
template<class T, class ALLOCATOR>
class Myqueue {
    public:
        template<class S>
        struct Node {
            using allocator_type = typename ALLOCATOR::template rebind<Node>::other;
            static allocator_type get_allocator()
            {
                static allocator_type allocator;
                return allocator;
            }
            void *operator new(size_t size)
            {
                return get_allocator().allocate(sizeof(Node));
            }
            void operator delete(void *p)
            {
                get_allocator().destroy((Node*)p);
                get_allocator().deallocate((Node *)p, sizeof(Node));
            }
            Node() = default;
            Node(const S& elem) : elem(elem) {
                next = make_shared<Node>();
            }
            ~Node() {
                next = nullptr;
                prev = nullptr;
            }
            S elem;
            shared_ptr<Node> next;
            shared_ptr<Node> prev;
        };
    public:
        template<class V>
        class forward_iterator : public std::iterator<std::forward_iterator_tag, V, int> {
            public:
                friend class Myqueue<T, ALLOCATOR>;
                typedef forward_iterator<V> self_type;
                typedef std::forward_iterator_tag iterator_category;
                typedef V value_type;
                typedef V &reference;
                typedef weak_ptr<Node<V> > pointer;
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
                        throw std::out_of_range("Ошибка! Произошел выход за границы очереди!");
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
template<class T, class ALLOCATOR>
auto Myqueue<T, ALLOCATOR>::Begin() {
    return forward_iterator<T>(begin_ptr, size, 0);
}
template<class T, class ALLOCATOR>
auto Myqueue<T, ALLOCATOR>::End() {
    return forward_iterator<T>(end_ptr, size, size);
}
template<class T, class ALLOCATOR>
void Myqueue<T, ALLOCATOR>::Insert(auto iterator, const T& elem) {
    auto new_elem = make_shared<Node<T> >(elem);
    if (iterator.index == size) {
        Push(elem);
    }
    else if (iterator.index < 0 || iterator.index >= size) {
        throw(std::runtime_error("Ошибка! Выход за границы очереди!"));
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
template<class T, class ALLOCATOR>
void Myqueue<T, ALLOCATOR>::Erase(auto iterator) {
    if (iterator.index == 0) {
        Pop();
    }
    else if (iterator.index < 0 || iterator.index >= size) {
        throw(std::runtime_error("Ошибка! Выход за границы очереди!"));
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
template<class T, class ALLOCATOR>
void Myqueue<T, ALLOCATOR>::Push(const T elem) {
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
template<class T, class ALLOCATOR>
void Myqueue<T, ALLOCATOR>::Pop() {
    if (size == 0) {
        throw std::runtime_error("Ошибка! Удаление из пустой очереди!");
    }
    begin_ptr->next->prev = nullptr;
    begin_ptr = begin_ptr->next;
    --size;
}
template<class T, class ALLOCATOR>
T Myqueue<T, ALLOCATOR>::Top() {
    if (size == 0) {
        throw std::runtime_error("Ошибка! Очередь пуста!");
    }
    return begin_ptr->elem;
}
