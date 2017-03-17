//
// Created by Timothy Shull on 2/4/16.
//

#ifndef ALGORITHMS_QUEUE_H
#define ALGORITHMS_QUEUE_H

#include <memory>

template<typename T, typename Alloc = std::allocator<T>>
class Queue_old {
private:
    class Node {
        T item;
        std::shared_ptr<Node> next;

    public:
        std::shared_ptr<Node> getNext() {
            return next;
        }

        void setNext(std::shared_ptr<Node> newNext) {
            next = newNext;
        }

        void setNext(Node newNext) {
            next = std::shared_ptr<Node>(&newNext);
        }

        void setItem(T newItem) {
            item = newItem;
        }

        T getItem() {
            return item;
        }
    };

    typedef typename Alloc::value_type Alloc_value_type;

    typedef Queue_old<T, Alloc> Queue_type;
    typedef typename Base::T_alloc_type T_alloc_type;

public:
    typedef T value_type;
    typedef typename T_alloc_type::pointer pointer;
    typedef typename T_alloc_type::const_pointer const_pointer;
    typedef typename T_alloc_type::reference reference;
    typedef typename T_alloc_type::const_reference const_reference;
    typedef std::iterator<pointer, Queue_type> iterator;
    typedef std::iterator<const_pointer, Queue_type> const_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef Alloc allocator_type;

private:
    std::shared_ptr<Node> first;
    std::shared_ptr<Node> last;
    int N;

public:
    bool isEmpty() { return first == nullptr; }

    int size() { return N; }

    void enqueue(value_type item) {
        std::shared_ptr<Node> old_last = last;
        last = std::make_shared<Node>();
        last->setItem(item);
        last->setNext(nullptr);
        if (isEmpty())
            first = last;
        else
            old_last->getNext() = last;
        N++;
    }

    value_type dequeue() {
        value_type return_item = first->getItem();
        first = first->getNext();
        if (isEmpty())
            last = nullptr;
        N--;
        return return_item;
    }

    iterator begin() { return iterator(this->_M_impl._M_start); }
};



//    public:
//        // [23.2.4.1] construct/copy/destroy
//        // (assign() and get_allocator() are also listed in this section)
//        /**
//         *  @brief  Default constructor creates no elements.
//         */
//        explicit
//        vector(const allocator_type& __a = allocator_type())
//                : _Base(__a) { }
//
//        /**
//         *  @brief  Create a %vector with copies of an exemplar element.
//         *  @param  n  The number of elements to initially create.
//         *  @param  value  An element to copy.
//         *
//         *  This constructor fills the %vector with @a n copies of @a value.
//         */
//        explicit
//        vector(size_type __n, const value_type& __value = value_type(),
//               const allocator_type& __a = allocator_type())
//                : _Base(__n, __a) {
//            std::__uninitialized_fill_n_a(this->_M_impl._M_start, __n, __value,
//                                          _M_get_Tp_allocator());
//            this->_M_impl._M_finish = this->_M_impl._M_start + __n;
//        }
//
//        /**
//         *  @brief  %Vector copy constructor.
//         *  @param  x  A %vector of identical element and allocator types.
//         *
//         *  The newly-created %vector uses a copy of the allocation
//         *  object used by @a x.  All the elements of @a x are copied,
//         *  but any extra memory in
//         *  @a x (for fast expansion) will not be copied.
//         */
//        vector(const vector& __x)
//                : _Base(__x.size(), __x._M_get_Tp_allocator()) {
//            this->_M_impl._M_finish =
//                    std::__uninitialized_copy_a(__x.begin(), __x.end(),
//                                                this->_M_impl._M_start,
//                                                _M_get_Tp_allocator());
//        }
//
//        /**
//         *  @brief  Builds a %vector from a range.
//         *  @param  first  An input iterator.
//         *  @param  last  An input iterator.
//         *
//         *  Create a %vector consisting of copies of the elements from
//         *  [first,last).
//         *
//         *  If the iterators are forward, bidirectional, or
//         *  random-access, then this will call the elements' copy
//         *  constructor N times (where N is distance(first,last)) and do
//         *  no memory reallocation.  But if only input iterators are
//         *  used, then this will do at most 2N calls to the copy
//         *  constructor, and logN memory reallocations.
//         */
//        template<typename _InputIterator>
//        vector(_InputIterator __first, _InputIterator __last,
//               const allocator_type& __a = allocator_type())
//                : _Base(__a) {
//            // Check whether it's an integral type.  If so, it's not an iterator.
//            typedef typename std::__is_integer<_InputIterator>::__type _Integral;
//            _M_initialize_dispatch(__first, __last, _Integral());
//        }
//
//        /**
//         *  The dtor only erases the elements, and note that if the
//         *  elements themselves are pointers, the pointed-to memory is
//         *  not touched in any way.  Managing the pointer is the user's
//         *  responsibilty.
//         */
//        ~vector() {
//            std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
//                          _M_get_Tp_allocator());
//        }
//
//        /**
//         *  @brief  %Vector assignment operator.
//         *  @param  x  A %vector of identical element and allocator types.
//         *
//         *  All the elements of @a x are copied, but any extra memory in
//         *  @a x (for fast expansion) will not be copied.  Unlike the
//         *  copy constructor, the allocator object is not copied.
//         */
//        vector&
//                operator=(const vector& __x);
//
//        /**
//         *  @brief  Assigns a given value to a %vector.
//         *  @param  n  Number of elements to be assigned.
//         *  @param  val  Value to be assigned.
//         *
//         *  This function fills a %vector with @a n copies of the given
//         *  value.  Note that the assignment completely changes the
//         *  %vector and that the resulting %vector's size is the same as
//         *  the number of elements assigned.  Old data may be lost.
//         */
//        void
//        assign(size_type __n, const value_type& __val) { _M_fill_assign(__n, __val); }
//
//        /**
//         *  @brief  Assigns a range to a %vector.
//         *  @param  first  An input iterator.
//         *  @param  last   An input iterator.
//         *
//         *  This function fills a %vector with copies of the elements in the
//         *  range [first,last).
//         *
//         *  Note that the assignment completely changes the %vector and
//         *  that the resulting %vector's size is the same as the number
//         *  of elements assigned.  Old data may be lost.
//         */
//        template<typename _InputIterator>
//        void
//        assign(_InputIterator __first, _InputIterator __last) {
//            // Check whether it's an integral type.  If so, it's not an iterator.
//            typedef typename std::__is_integer<_InputIterator>::__type _Integral;
//            _M_assign_dispatch(__first, __last, _Integral());
//        }
//
//        /// Get a copy of the memory allocation object.
//        using _Base::get_allocator;
//
//        // iterators
//        /**
//         *  Returns a read/write iterator that points to the first
//         *  element in the %vector.  Iteration is done in ordinary
//         *  element order.
//         */
//        iterator
//        begin() { return iterator(this->_M_impl._M_start); }
//
//        /**
//         *  Returns a read-only (constant) iterator that points to the
//         *  first element in the %vector.  Iteration is done in ordinary
//         *  element order.
//         */
//        const_iterator
//        begin() const { return const_iterator(this->_M_impl._M_start); }
//
//        /**
//         *  Returns a read/write iterator that points one past the last
//         *  element in the %vector.  Iteration is done in ordinary
//         *  element order.
//         */
//        iterator
//        end() { return iterator(this->_M_impl._M_finish); }
//
//        /**
//         *  Returns a read-only (constant) iterator that points one past
//         *  the last element in the %vector.  Iteration is done in
//         *  ordinary element order.
//         */
//        const_iterator
//        end() const { return const_iterator(this->_M_impl._M_finish); }
//
//        /**
//         *  Returns a read/write reverse iterator that points to the
//         *  last element in the %vector.  Iteration is done in reverse
//         *  element order.
//         */
//        reverse_iterator
//        rbegin() { return reverse_iterator(end()); }
//
//        /**
//         *  Returns a read-only (constant) reverse iterator that points
//         *  to the last element in the %vector.  Iteration is done in
//         *  reverse element order.
//         */
//        const_reverse_iterator
//        rbegin() const { return const_reverse_iterator(end()); }
//
//        /**
//         *  Returns a read/write reverse iterator that points to one
//         *  before the first element in the %vector.  Iteration is done
//         *  in reverse element order.
//         */
//        reverse_iterator
//        rend() { return reverse_iterator(begin()); }
//
//        /**
//         *  Returns a read-only (constant) reverse iterator that points
//         *  to one before the first element in the %vector.  Iteration
//         *  is done in reverse element order.
//         */
//        const_reverse_iterator
//        rend() const { return const_reverse_iterator(begin()); }
//
//        // [23.2.4.2] capacity
//        /**  Returns the number of elements in the %vector.  */
//        size_type
//        size() const { return size_type(this->_M_impl._M_finish - this->_M_impl._M_start); }
//
//        /**  Returns the size() of the largest possible %vector.  */
//        size_type
//        max_size() const { return _M_get_Tp_allocator().max_size(); }
//
//        /**
//         *  @brief  Resizes the %vector to the specified number of elements.
//         *  @param  new_size  Number of elements the %vector should contain.
//         *  @param  x  Data with which new elements should be populated.
//         *
//         *  This function will %resize the %vector to the specified
//         *  number of elements.  If the number is smaller than the
//         *  %vector's current size the %vector is truncated, otherwise
//         *  the %vector is extended and new elements are populated with
//         *  given data.
//         */
//        void
//        resize(size_type __new_size, value_type __x = value_type()) {
//            if (__new_size < size())
//                _M_erase_at_end(this->_M_impl._M_start + __new_size);
//            else
//                insert(end(), __new_size - size(), __x);
//        }
//
//        /**
//         *  Returns the total number of elements that the %vector can
//         *  hold before needing to allocate more memory.
//         */
//        size_type
//        capacity() const {
//            return size_type(this->_M_impl._M_end_of_storage
//                             - this->_M_impl._M_start);
//        }
//
//        /**
//         *  Returns true if the %vector is empty.  (Thus begin() would
//         *  equal end().)
//         */
//        bool
//        empty() const { return begin() == end(); }
//
//        /**
//         *  @brief  Attempt to preallocate enough memory for specified number of
//         *          elements.
//         *  @param  n  Number of elements required.
//         *  @throw  std::length_error  If @a n exceeds @c max_size().
//         *
//         *  This function attempts to reserve enough memory for the
//         *  %vector to hold the specified number of elements.  If the
//         *  number requested is more than max_size(), length_error is
//         *  thrown.
//         *
//         *  The advantage of this function is that if optimal code is a
//         *  necessity and the user can determine the number of elements
//         *  that will be required, the user can reserve the memory in
//         *  %advance, and thus prevent a possible reallocation of memory
//         *  and copying of %vector data.
//         */
//        void
//                reserve(size_type __n);
//
//        // element access
//        /**
//         *  @brief  Subscript access to the data contained in the %vector.
//         *  @param n The index of the element for which data should be
//         *  accessed.
//         *  @return  Read/write reference to data.
//         *
//         *  This operator allows for easy, array-style, data access.
//         *  Note that data access with this operator is unchecked and
//         *  out_of_range lookups are not defined. (For checked lookups
//         *  see at().)
//         */
//        reference
//        operator[](size_type __n) { return *(this->_M_impl._M_start + __n); }
//
//        /**
//         *  @brief  Subscript access to the data contained in the %vector.
//         *  @param n The index of the element for which data should be
//         *  accessed.
//         *  @return  Read-only (constant) reference to data.
//         *
//         *  This operator allows for easy, array-style, data access.
//         *  Note that data access with this operator is unchecked and
//         *  out_of_range lookups are not defined. (For checked lookups
//         *  see at().)
//         */
//        const_reference
//        operator[](size_type __n) const { return *(this->_M_impl._M_start + __n); }
//
//    protected:
//        /// @if maint Safety check used only from at().  @endif
//        void
//        _M_range_check(size_type __n) const {
//            if (__n >= this->size())
//                __throw_out_of_range(__N("vector::_M_range_check"));
//        }
//
//    public:
//        /**
//         *  @brief  Provides access to the data contained in the %vector.
//         *  @param n The index of the element for which data should be
//         *  accessed.
//         *  @return  Read/write reference to data.
//         *  @throw  std::out_of_range  If @a n is an invalid index.
//         *
//         *  This function provides for safer data access.  The parameter
//         *  is first checked that it is in the range of the vector.  The
//         *  function throws out_of_range if the check fails.
//         */
//        reference
//        at(size_type __n) {
//            _M_range_check(__n);
//            return (*this)[__n];
//        }
//
//        /**
//         *  @brief  Provides access to the data contained in the %vector.
//         *  @param n The index of the element for which data should be
//         *  accessed.
//         *  @return  Read-only (constant) reference to data.
//         *  @throw  std::out_of_range  If @a n is an invalid index.
//         *
//         *  This function provides for safer data access.  The parameter
//         *  is first checked that it is in the range of the vector.  The
//         *  function throws out_of_range if the check fails.
//         */
//        const_reference
//        at(size_type __n) const {
//            _M_range_check(__n);
//            return (*this)[__n];
//        }
//
//        /**
//         *  Returns a read/write reference to the data at the first
//         *  element of the %vector.
//         */
//        reference
//        front() { return *begin(); }
//
//        /**
//         *  Returns a read-only (constant) reference to the data at the first
//         *  element of the %vector.
//         */
//        const_reference
//        front() const { return *begin(); }
//
//        /**
//         *  Returns a read/write reference to the data at the last
//         *  element of the %vector.
//         */
//        reference
//        back() { return *(end() - 1); }
//
//        /**
//         *  Returns a read-only (constant) reference to the data at the
//         *  last element of the %vector.
//         */
//        const_reference
//        back() const { return *(end() - 1); }
//
//        // _GLIBCXX_RESOLVE_LIB_DEFECTS
//        // DR 464. Suggestion for new member functions in standard containers.
//        // data access
//        /**
//         *   Returns a pointer such that [data(), data() + size()) is a valid
//         *   range.  For a non-empty %vector, data() == &front().
//         */
//        pointer
//        data() { return pointer(this->_M_impl._M_start); }
//
//        const_pointer
//        data() const { return const_pointer(this->_M_impl._M_start); }
//
//        // [23.2.4.3] modifiers
//        /**
//         *  @brief  Add data to the end of the %vector.
//         *  @param  x  Data to be added.
//         *
//         *  This is a typical stack operation.  The function creates an
//         *  element at the end of the %vector and assigns the given data
//         *  to it.  Due to the nature of a %vector this operation can be
//         *  done in constant time if the %vector has preallocated space
//         *  available.
//         */
//        void
//        push_back(const value_type& __x) {
//            if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage) {
//                this->_M_impl.construct(this->_M_impl._M_finish, __x);
//                ++this->_M_impl._M_finish;
//            }
//            else
//                _M_insert_aux(end(), __x);
//        }
//
//        /**
//         *  @brief  Removes last element.
//         *
//         *  This is a typical stack operation. It shrinks the %vector by one.
//         *
//         *  Note that no data is returned, and if the last element's
//         *  data is needed, it should be retrieved before pop_back() is
//         *  called.
//         */
//        void
//        pop_back() {
//            --this->_M_impl._M_finish;
//            this->_M_impl.destroy(this->_M_impl._M_finish);
//        }
//
//        /**
//         *  @brief  Inserts given value into %vector before specified iterator.
//         *  @param  position  An iterator into the %vector.
//         *  @param  x  Data to be inserted.
//         *  @return  An iterator that points to the inserted data.
//         *
//         *  This function will insert a copy of the given value before
//         *  the specified location.  Note that this kind of operation
//         *  could be expensive for a %vector and if it is frequently
//         *  used the user should consider using std::list.
//         */
//        iterator
//                insert(iterator __position, const value_type& __x);
//
//        /**
//         *  @brief  Inserts a number of copies of given data into the %vector.
//         *  @param  position  An iterator into the %vector.
//         *  @param  n  Number of elements to be inserted.
//         *  @param  x  Data to be inserted.
//         *
//         *  This function will insert a specified number of copies of
//         *  the given data before the location specified by @a position.
//         *
//         *  Note that this kind of operation could be expensive for a
//         *  %vector and if it is frequently used the user should
//         *  consider using std::list.
//         */
//        void
//        insert(iterator __position, size_type __n, const value_type& __x) { _M_fill_insert(__position, __n, __x); }
//
//        /**
//         *  @brief  Inserts a range into the %vector.
//         *  @param  position  An iterator into the %vector.
//         *  @param  first  An input iterator.
//         *  @param  last   An input iterator.
//         *
//         *  This function will insert copies of the data in the range
//         *  [first,last) into the %vector before the location specified
//         *  by @a pos.
//         *
//         *  Note that this kind of operation could be expensive for a
//         *  %vector and if it is frequently used the user should
//         *  consider using std::list.
//         */
//        template<typename _InputIterator>
//        void
//        insert(iterator __position, _InputIterator __first,
//               _InputIterator __last) {
//            // Check whether it's an integral type.  If so, it's not an iterator.
//            typedef typename std::__is_integer<_InputIterator>::__type _Integral;
//            _M_insert_dispatch(__position, __first, __last, _Integral());
//        }
//
//        /**
//         *  @brief  Remove element at given position.
//         *  @param  position  Iterator pointing to element to be erased.
//         *  @return  An iterator pointing to the next element (or end()).
//         *
//         *  This function will erase the element at the given position and thus
//         *  shorten the %vector by one.
//         *
//         *  Note This operation could be expensive and if it is
//         *  frequently used the user should consider using std::list.
//         *  The user is also cautioned that this function only erases
//         *  the element, and that if the element is itself a pointer,
//         *  the pointed-to memory is not touched in any way.  Managing
//         *  the pointer is the user's responsibilty.
//         */
//        iterator
//                erase(iterator __position);
//
//        /**
//         *  @brief  Remove a range of elements.
//         *  @param  first  Iterator pointing to the first element to be erased.
//         *  @param  last  Iterator pointing to one past the last element to be
//         *                erased.
//         *  @return  An iterator pointing to the element pointed to by @a last
//         *           prior to erasing (or end()).
//         *
//         *  This function will erase the elements in the range [first,last) and
//         *  shorten the %vector accordingly.
//         *
//         *  Note This operation could be expensive and if it is
//         *  frequently used the user should consider using std::list.
//         *  The user is also cautioned that this function only erases
//         *  the elements, and that if the elements themselves are
//         *  pointers, the pointed-to memory is not touched in any way.
//         *  Managing the pointer is the user's responsibilty.
//         */
//        iterator
//                erase(iterator __first, iterator __last);
//
//        /**
//         *  @brief  Swaps data with another %vector.
//         *  @param  x  A %vector of the same element and allocator types.
//         *
//         *  This exchanges the elements between two vectors in constant time.
//         *  (Three pointers, so it should be quite fast.)
//         *  Note that the global std::swap() function is specialized such that
//         *  std::swap(v1,v2) will feed to this function.
//         */
//        void
//        swap(vector& __x) {
//            std::swap(this->_M_impl._M_start, __x._M_impl._M_start);
//            std::swap(this->_M_impl._M_finish, __x._M_impl._M_finish);
//            std::swap(this->_M_impl._M_end_of_storage,
//                      __x._M_impl._M_end_of_storage);
//
//            // _GLIBCXX_RESOLVE_LIB_DEFECTS
//            // 431. Swapping containers with unequal allocators.
//            std::__alloc_swap<_Tp_alloc_type>::_S_do_it(_M_get_Tp_allocator(),
//                                                        __x._M_get_Tp_allocator());
//        }
//
//        /**
//         *  Erases all the elements.  Note that this function only erases the
//         *  elements, and that if the elements themselves are pointers, the
//         *  pointed-to memory is not touched in any way.  Managing the pointer is
//         *  the user's responsibilty.
//         */
//        void
//        clear() { _M_erase_at_end(this->_M_impl._M_start); }
//
//    protected:
//        /**
//         *  @if maint
//         *  Memory expansion handler.  Uses the member allocation function to
//         *  obtain @a n bytes of memory, and then copies [first,last) into it.
//         *  @endif
//         */
//        template<typename _ForwardIterator>
//        pointer
//        _M_allocate_and_copy(size_type __n,
//                             _ForwardIterator __first, _ForwardIterator __last) {
//            pointer __result = this->_M_allocate(__n);
//            try {
//                std::__uninitialized_copy_a(__first, __last, __result,
//                                            _M_get_Tp_allocator());
//                return __result;
//            }
//            catch (...) {
//                _M_deallocate(__result, __n);
//                __throw_exception_again;
//            }
//        }
//
//
//        // Internal constructor functions follow.
//
//        // Called by the range constructor to implement [23.1.1]/9
//        template<typename _Integer>
//        void
//        _M_initialize_dispatch(_Integer __n, _Integer __value, __true_type) {
//            this->_M_impl._M_start = _M_allocate(__n);
//            this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
//            std::__uninitialized_fill_n_a(this->_M_impl._M_start, __n, __value,
//                                          _M_get_Tp_allocator());
//            this->_M_impl._M_finish = this->_M_impl._M_end_of_storage;
//        }
//
//        // Called by the range constructor to implement [23.1.1]/9
//        template<typename _InputIterator>
//        void
//        _M_initialize_dispatch(_InputIterator __first, _InputIterator __last,
//                               __false_type) {
//            typedef typename std::iterator_traits<_InputIterator>::
//            iterator_category _IterCategory;
//            _M_range_initialize(__first, __last, _IterCategory());
//        }
//
//        // Called by the second initialize_dispatch above
//        template<typename _InputIterator>
//        void
//        _M_range_initialize(_InputIterator __first,
//                            _InputIterator __last, std::input_iterator_tag) {
//            for (; __first != __last; ++__first)
//                push_back(*__first);
//        }
//
//        // Called by the second initialize_dispatch above
//        template<typename _ForwardIterator>
//        void
//        _M_range_initialize(_ForwardIterator __first,
//                            _ForwardIterator __last, std::forward_iterator_tag) {
//            const size_type __n = std::distance(__first, __last);
//            this->_M_impl._M_start = this->_M_allocate(__n);
//            this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
//            this->_M_impl._M_finish =
//                    std::__uninitialized_copy_a(__first, __last,
//                                                this->_M_impl._M_start,
//                                                _M_get_Tp_allocator());
//        }
//
//
//        // Internal assign functions follow.  The *_aux functions do the actual
//        // assignment work for the range versions.
//
//        // Called by the range assign to implement [23.1.1]/9
//        template<typename _Integer>
//        void
//        _M_assign_dispatch(_Integer __n, _Integer __val, __true_type) {
//            _M_fill_assign(static_cast<size_type>(__n),
//                           static_cast<value_type>(__val));
//        }
//
//        // Called by the range assign to implement [23.1.1]/9
//        template<typename _InputIterator>
//        void
//        _M_assign_dispatch(_InputIterator __first, _InputIterator __last,
//                           __false_type) {
//            typedef typename std::iterator_traits<_InputIterator>::
//            iterator_category _IterCategory;
//            _M_assign_aux(__first, __last, _IterCategory());
//        }
//
//        // Called by the second assign_dispatch above
//        template<typename _InputIterator>
//        void
//                _M_assign_aux(_InputIterator __first, _InputIterator __last,
//                              std::input_iterator_tag);
//
//        // Called by the second assign_dispatch above
//        template<typename _ForwardIterator>
//        void
//                _M_assign_aux(_ForwardIterator __first, _ForwardIterator __last,
//                              std::forward_iterator_tag);
//
//        // Called by assign(n,t), and the range assign when it turns out
//        // to be the same thing.
//        void
//                _M_fill_assign(size_type __n, const value_type& __val);
//
//
//        // Internal insert functions follow.
//
//        // Called by the range insert to implement [23.1.1]/9
//        template<typename _Integer>
//        void
//        _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __val,
//                           __true_type) {
//            _M_fill_insert(__pos, static_cast<size_type>(__n),
//                           static_cast<value_type>(__val));
//        }
//
//        // Called by the range insert to implement [23.1.1]/9
//        template<typename _InputIterator>
//        void
//        _M_insert_dispatch(iterator __pos, _InputIterator __first,
//                           _InputIterator __last, __false_type) {
//            typedef typename std::iterator_traits<_InputIterator>::
//            iterator_category _IterCategory;
//            _M_range_insert(__pos, __first, __last, _IterCategory());
//        }
//
//        // Called by the second insert_dispatch above
//        template<typename _InputIterator>
//        void
//                _M_range_insert(iterator __pos, _InputIterator __first,
//                                _InputIterator __last, std::input_iterator_tag);
//
//        // Called by the second insert_dispatch above
//        template<typename _ForwardIterator>
//        void
//                _M_range_insert(iterator __pos, _ForwardIterator __first,
//                                _ForwardIterator __last, std::forward_iterator_tag);
//
//        // Called by insert(p,n,x), and the range insert when it turns out to be
//        // the same thing.
//        void
//                _M_fill_insert(iterator __pos, size_type __n, const value_type& __x);
//
//        // Called by insert(p,x)
//        void
//                _M_insert_aux(iterator __position, const value_type& __x);
//
//        // Internal erase functions follow.
//
//        // Called by erase(q1,q2), clear(), resize(), _M_fill_assign,
//        // _M_assign_aux.
//        void
//        _M_erase_at_end(pointer __pos) {
//            std::_Destroy(__pos, this->_M_impl._M_finish, _M_get_Tp_allocator());
//            this->_M_impl._M_finish = __pos;
//        }
//    };
//
//
//    /**
//     *  @brief  Vector equality comparison.
//     *  @param  x  A %vector.
//     *  @param  y  A %vector of the same type as @a x.
//     *  @return  True iff the size and elements of the vectors are equal.
//     *
//     *  This is an equivalence relation.  It is linear in the size of the
//     *  vectors.  Vectors are considered equivalent if their sizes are equal,
//     *  and if corresponding elements compare equal.
//    */
//    template<typename _Tp, typename _Alloc>
//    inline bool
//    operator==(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y) {
//        return (__x.size() == __y.size()
//                && std::equal(__x.begin(), __x.end(), __y.begin()));
//    }
//
//    /**
//     *  @brief  Vector ordering relation.
//     *  @param  x  A %vector.
//     *  @param  y  A %vector of the same type as @a x.
//     *  @return  True iff @a x is lexicographically less than @a y.
//     *
//     *  This is a total ordering relation.  It is linear in the size of the
//     *  vectors.  The elements must be comparable with @c <.
//     *
//     *  See std::lexicographical_compare() for how the determination is made.
//    */
//    template<typename _Tp, typename _Alloc>
//    inline bool
//    operator<(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y) {
//        return std::lexicographical_compare(__x.begin(), __x.end(),
//                                            __y.begin(), __y.end());
//    }
//
//    /// Based on operator==
//    template<typename _Tp, typename _Alloc>
//    inline bool
//    operator!=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y) { return !(__x == __y); }
//
//    /// Based on operator<
//    template<typename _Tp, typename _Alloc>
//    inline bool
//    operator>(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y) { return __y < __x; }
//
//    /// Based on operator<
//    template<typename _Tp, typename _Alloc>
//    inline bool
//    operator<=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y) { return !(__y < __x); }
//
//    /// Based on operator<
//    template<typename _Tp, typename _Alloc>
//    inline bool
//    operator>=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y) { return !(__x < __y); }
//
//    /// See std::vector::swap().
//    template<typename _Tp, typename _Alloc>
//    inline void
//    swap(vector<_Tp, _Alloc>& __x, vector<_Tp, _Alloc>& __y) { __x.swap(__y); }
//
//    _GLIBCXX_END_NESTED_NAMESPACE
//
//#endif /* _VECTOR_H */
