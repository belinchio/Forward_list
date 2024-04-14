#include <cstddef>
#include <cassert>
#include <iostream>
#include <utility>

template <typename T>
class Forward_list {
public:
    using   value_type       = T;
    using   size_type        = size_t;
    using   difference_type  = ptrdiff_t;
    using   pointer          = value_type*;
    using   const_pointer    = const value_type*;
    using   reference        = value_type&;
    using   const_reference  = const value_type&;

private:
    struct node {
        node* next = nullptr;
        value_type data;

        node(value_type item) noexcept : data {std::move(item)} {};
    };

public:
    class ForwardListConstIterator {
    private:
        friend class Forward_list;

        explicit ForwardListConstIterator(const node* ptr) noexcept : m_current {ptr} {}

    public:
        using difference_type   = Forward_list::difference_type;
        using value_type        = Forward_list::value_type;
        using pointer           = Forward_list::const_pointer;
        using reference         = Forward_list::const_reference;
        using iterator_category = std::forward_iterator_tag;

        reference operator*() const noexcept {
            assert(m_current != nullptr);
            return m_current->data;
        }

        ForwardListConstIterator& operator++() noexcept {
            assert(m_current != nullptr);
            m_current = m_current->next;
            return *this;
        }

        ForwardListConstIterator operator++(int) noexcept {
            assert(m_current != nullptr);
            auto copy = *this;

            m_current = m_current->next;
            return copy;
        }

        bool operator==(ForwardListConstIterator other) const noexcept {
            return m_current == other.m_current;
        }

        bool operator!=(ForwardListConstIterator other) const noexcept {
            return !(*this == other);
        }

    protected:
        const node* Get() const noexcept {
            return m_current;
        }

    protected:
        const node* m_current;
    };

    class ForwardListIterator : public ForwardListConstIterator {
    private:
        friend class Forward_list;
      
        explicit ForwardListIterator(node* ptr) noexcept : ForwardListConstIterator {ptr} {}

    public:
        using difference_type     = Forward_list::difference_type;
        using value_type          = Forward_list::value_type;
        using pointer             = Forward_list::pointer;
        using reference           = Forward_list::reference;
        using iterator_category   = std::forward_iterator_tag;

        reference operator*() noexcept {
            auto&& res = ForwardListConstIterator::operator*();
            return const_cast<reference>(res);
        }

        ForwardListIterator& operator++() noexcept {
            ForwardListConstIterator::operator++();
            return *this;
        }

        ForwardListIterator operator++(int) noexcept {
            auto res = ForwardListConstIterator::operator++(0);
            return ForwardListIterator {const_cast<node*>(res.Get())};
        }
    };

    using iterator       = ForwardListIterator;
    using const_iterator = ForwardListConstIterator;

    Forward_list() = default;

    Forward_list(std::initializer_list<T> items) {
        for (auto& item : items) {
            push_back(item);
        }
    }

    ~Forward_list() {
        clear();
    }

    void clear() noexcept {
        while (m_head) {
            delete std::exchange(m_head, m_head->next);
        }

        m_tail = nullptr;
    }

    void push_front(value_type item) {
        auto newnode = new node{std::move(item)};
        if (m_head) {
            newnode->next = m_head;
            m_head = newnode;
        } else {
            m_head = m_tail = newnode;
        }
}

    void push_back(value_type item) {
        auto newnode = new node {std::move(item)};
        if (m_tail) {
            m_tail->next = newnode;
            m_tail = newnode;
        } else {
            m_head = m_tail = newnode;
        }
    }

    void insert_after(const_iterator place, value_type item) {
        auto ptr = const_cast<node*>(place.Get());
        if (!ptr) {
            push_front(std::move(item));
            return;
        }

        auto newnode = new node{std::move(item)};
        newnode->next = ptr->next;
        ptr->next = newnode;
}

    const_iterator find(const_reference item) const noexcept {
        for (auto it = begin(); it != end(); ++it) {
            if (*it == item) {
                return it;
            }
        }
        return const_iterator{nullptr};
    }

    iterator find(const_reference item) noexcept {
        auto it = static_cast<const Forward_list &>(*this).find(item);
        return iterator {const_cast<node*>(it.Get())};
    }

    void erase_after(const_iterator place) noexcept {
        auto ptr = const_cast<node*>(place.Get());
        if (ptr) {
            auto nodeToDelete = ptr->next;
            if (ptr->next) {
                ptr->next = ptr->next->next;
            }
        delete nodeToDelete;
        } else {
            assert(m_head != nullptr);
            delete std::exchange(m_head, m_head->next);
        }
    }

    void pop_front() noexcept {
        erase_after(iterator{nullptr});
    }

    const_iterator begin() const noexcept {
        return const_iterator{m_head};
    }

    const_iterator end() const noexcept {
        return const_iterator{nullptr};
    }

    const_iterator cbegin() const noexcept {
        return const_iterator{m_head};
    }

    const_iterator cend() const noexcept {
        return const_iterator{nullptr};
    }

    iterator begin() noexcept {
        return iterator{m_head};
    }

    iterator end() noexcept {
        return iterator{nullptr};
    }

private:
    node* m_head = nullptr;
    node* m_tail = nullptr;
};
