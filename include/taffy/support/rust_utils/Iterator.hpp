#pragma once

#include <iterator> // for: std::forward_iterator_tag
#include <cstddef>  // for: std::ptrdiff_t

namespace taffy {

// Reference: https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
// Alternative (simple) impl: https://stackoverflow.com/a/39463987/

namespace impl {

    template <typename Item>
    class Iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = Item;
        using pointer           = Item*;  // or also value_type*
        using reference         = Item&;  // or also value_type&

        constexpr Iterator(pointer ptr) 
            : m_ptr(ptr) 
        {}

        reference operator * () const { return *m_ptr; }
        pointer operator -> () { return m_ptr; }

        // Prefix increment
        Iterator& operator ++ () { m_ptr++; return *this; }  

        // Postfix increment
        Iterator operator ++ (int) { Iterator tmp = *this; ++(*this); return tmp; }

        friend bool operator == (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator != (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };     

    private:
        pointer m_ptr;
    };

    template <typename Item>
    class ConstIterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = Item;
        using pointer           = Item*;  // or also value_type*
        using reference         = Item&;  // or also value_type&

        constexpr ConstIterator(pointer ptr)
            : m_ptr(ptr)
        {}

        const reference operator * () const { return *m_ptr; } // Note: following 'const' is the only difference from 'Iterator'
        pointer operator -> () { return m_ptr; }

        // Prefix increment
        ConstIterator& operator ++ () { m_ptr++; return *this; }  

        // Postfix increment
        ConstIterator operator ++ (int) { ConstIterator tmp = *this; ++(*this); return tmp; }

        friend bool operator == (const ConstIterator& a, const ConstIterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator != (const ConstIterator& a, const ConstIterator& b) { return a.m_ptr != b.m_ptr; };     

    private:
        pointer m_ptr;
    };

} // namespace impl

template <typename Item>
class Iterator
{
    impl::ConstIterator<Item> _begin;
    impl::ConstIterator<Item> _end;

public:

    Iterator(const impl::ConstIterator<Item>& begin_, const impl::ConstIterator<Item>& end_)
        : _begin(begin_)
        , _end(end_)
    {}

    inline impl::ConstIterator<Item> begin() const { return _begin; }
    inline impl::ConstIterator<Item> end() const { return _end; }
};

template <typename Item>
class IteratorMut
{
    impl::Iterator<Item> _begin;
    impl::Iterator<Item> _end;

public:

    IteratorMut(const impl::Iterator<Item>& begin_, const impl::Iterator<Item>& end_)
        : _begin(begin_)
        , _end(end_)
    {}

    inline impl::Iterator<Item> begin() const { return _begin; }
    inline impl::Iterator<Item> end() const { return _end; }
};

template <typename Container, typename T = typename Container::value_type>
inline Iterator<T> iter(const Container& container)
{
    return Iterator<T> { const_cast<T*>(container.data()), const_cast<T*>(container.data() + container.size()) };
}

} // namespace taffy