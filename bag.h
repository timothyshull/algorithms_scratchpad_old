#ifndef ALGORITHMS_BAG_H
#define ALGORITHMS_BAG_H

#include <memory>

namespace custom_bag {

    template<class T, class VoidPtr>
    struct bag_node;

    template<class NodePtr>
    struct begin_node {
        using pointer = NodePtr;
        pointer next;

        inline begin_node() : next{nullptr} { }
    };

    template<class T, class VoidPtr>
    struct begin_node_of {
        using type = begin_node<typename std::pointer_traits<VoidPtr>::template rebind<bag_node<T, VoidPtr>>>;
    };

    template<class T, class VoidPtr>
    struct bag_node : public begin_node_of<T, VoidPtr>::type {
        using value_type = T;
        value_type value;
    };

    template<class T, class Allocator = std::allocator<T>>
    class bag;

    template<class NodeConstPtr>
    class bag_const_iterator;

    template<class NodePtr>
    class bag_iterator {
        using node_pointer = NodePtr;
        node_pointer ptr;

        inline explicit bag_iterator(node_pointer p) noexcept : ptr{p} { }

        template<class, class> friend
        class bag;

        template<class> friend
        class bag_const_iterator;

    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef typename std::pointer_traits<node_pointer>::element_type::value_type value_type;
        typedef value_type& reference;
        typedef typename std::pointer_traits<node_pointer>::difference_type difference_type;
        typedef typename std::pointer_traits<node_pointer>::template
        rebind<value_type> pointer;

        inline bag_iterator() noexcept : ptr{nullptr} { }

        reference operator*() const { return ptr->__value_; }

        inline pointer operator->() const { return std::pointer_traits<pointer>::pointer_to(ptr->value); }

        inline bag_iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }

        inline bag_iterator operator++(int) {
            bag_iterator it(*this);
            ++(*this);
            return it;
        }

        friend inline bool operator==(const bag_iterator& x, const bag_iterator& y) {
            return x.ptr == y.ptr;
        }

        friend inline bool operator!=(const bag_iterator& x, const bag_iterator& y) {
            return !(x == y);
        }
    };

    template<class NodeConstPtr>
    class bag_const_iterator {
        using node_const_pointer = NodeConstPtr;
        node_const_pointer ptr;

        inline explicit bag_const_iterator(node_const_pointer p) noexcept : ptr{p} { }

        using node = std::remove_const<typename std::pointer_traits<node_const_pointer>::element_type>::type;
        using node_pointer = std::pointer_traits<node_const_pointer>::template rebind<node>

        template<class, class> friend
        class bag;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = node::value_type;
        using reference = value_type&;
        using difference_type = std::pointer_traits<node_const_pointer>::difference_type;
        using pointer = typename std::pointer_traits<node_const_pointer>::template rebind<const value_type>;

        inline bag_const_iterator() noexcept : ptr{nullptr} { }

        inline bag_const_iterator(bag_iterator<node_pointer> p) noexcept : ptr{p.ptr} { }

        inline reference operator*() const { return ptr->value; }

        inline pointer operator->() const { return std::pointer_traits<pointer>::pointer_to(ptr->value); }

        inline bag_const_iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }

        inline bag_const_iterator operator++(int) {
            bag_const_iterator it(*this);
            ++(*this);
            return it;
        }

        friend inline bool operator==(const bag_const_iterator& x,
                                      const bag_const_iterator& y) { return x.ptr == y.ptr; }

        friend inline bool operator!=(const bag_const_iterator& x,
                                      const bag_const_iterator& y) { return !(x == y); }
    };

    template<class T, class Allocator>
    class bag_base {
    protected:
        using value_type = T;
        using allocator_type = Allocator;

        using void_pointer = typename std::allocator_traits<allocator_type>::void_pointer;
        using node = bag_node<value_type, void_pointer>;
        using begin_node = begin_node_of<value_type, void_pointer>::type;
        using node_allocator = std::allocator_traits<allocator_type>::template rebind_alloc<node>;
        using node_traits = std::allocator_traits<node_allocator>;
        using node_pointer = node_traits::pointer;
        using node_const_pointer = node_traits::pointer;

        using begin_node_allocator = typename std::allocator_traits<allocator_type>::template rebind_alloc<begin_node>;
        using begin_node_pointer = typename std::allocator_traits<begin_node_allocator>::pointer;

        std::pair<begin_node, node_allocator> before_begin_;

        inline node_pointer before_begin() noexcept {
            return static_cast<node_pointer>(std::pointer_traits<begin_node_pointer>::pointer_to(before_begin_.first));
        }

        inline node_const_pointer before_begin() const noexcept {
            return static_cast<node_const_pointer>(std::pointer_traits<begin_node_pointer>::pointer_to(
                    const_cast<begin_node&>(before_begin_.first)));
        }

        inline node_allocator& alloc() noexcept { return before_begin_.second(); }

        inline const node_allocator& alloc() const noexcept { return before_begin_.second(); }

        using iterator = bag_iterator<node_pointer>;
        using const_iterator = bag_const_iterator<node_pointer>;

        inline bag_base() noexcept(std::is_nothrow_default_constructible<node_allocator>::value) : before_begin_(begin_node()) { }

        inline bag_base(const allocator_type& a) : before_begin_(begin_node(), node_allocator(a)) { }

    public:
        bag_base(bag_base&& x) noexcept(std::is_nothrow_move_constructible<node_allocator>::value);

        bag_base(bag_base&& x, const allocator_type& a);

    private:
        bag_base(const bag_base&);

        bag_base& operator=(const bag_base&);

    public:
        ~bag_base();

    protected:
        inline void copy_assign_alloc(const bag_base& x) {
            copy_assign_alloc(x, std::integral_constant<bool, node_traits::propagate_on_container_copy_assignment::value>());
        }

        inline void move_assign_alloc(bag_base& x) noexcept(
        !node_traits::propagate_on_container_move_assignment::value ||
        std::is_nothrow_move_assignable<node_allocator>::value) {
            move_assign_alloc(x, std::integral_constant<bool, node_traits::propagate_on_container_move_assignment::value>());
        }

    public:
        void swap(bag_base& x) noexcept(!node_traits::propagate_on_container_swap::value ||
                                                 std::is_nothrow_swappable<node_allocator>::value);

    protected:
        void clear() noexcept;

    private:
        using false_type = std::integral_constant<bool, false>;
        using true_type = std::integral_constant<bool, true>;

        inline void copy_assign_alloc(const bag_base&, false_type) { }

        inline void copy_assign_alloc(const bag_base& x, true_type) {
            if (alloc() != x.alloc())
                clear();
            alloc() = x.alloc();
        }

        inline void move_assign_alloc(bag_base& __x, false_type) noexcept { }

        inline void move_assign_alloc(bag_base& x,
                                      true_type) noexcept(std::is_nothrow_move_assignable<node_allocator>::value) {
            alloc() = std::move(x.alloc());
        }

        inline static void swap_alloc(node_allocator& x, node_allocator& y) noexcept(
        !node_traits::propagate_on_container_swap::value || std::is_nothrow_swappable<node_allocator>::value) {
            swap_alloc(x, y, std::integral_constant<bool, node_traits::propagate_on_container_swap::value>());
        }

        inline static void swap_alloc(node_allocator& x, node_allocator& y, false_type) noexcept { }

        inline static void swap_alloc(node_allocator& x, node_allocator& y,
                                      true_type) noexcept(is_nothrow_swappable<node_allocator>::value) {
            std::swap(x, y);
        }
    };
}

#endif //ALGORITHMS_BAG_H


//bags
//operator=
//assign
//get_allocator
//begin
//end
//cbegin
//cend
//before_begin
//cbefore_begin
//empty
//max_size
//front
//emplace_front
//push_front
//pop_front
//emplace_after
//insert_after
//erase_after
//swap
//resize
//clear
//splice_after
//remove
//remove_if
//unique
//merge
//sort
//reverse
//move_assign