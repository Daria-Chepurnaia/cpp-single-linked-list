#pragma once

#include <iterator>

template <typename Type>
class SingleLinkedList {
    
    struct Node {
        Node() = default;
        Node(const Type& val, Node* next);
        
        Type value;
        Node* next_node = nullptr;
    };

    template <typename ValueType>
    class BasicIterator {
        friend class SingleLinkedList;

        explicit BasicIterator(Node* node);
    
    public:    
        using iterator_category = std::forward_iterator_tag;       
        using value_type = Type;        
        using difference_type = std::ptrdiff_t;      
        using pointer = ValueType*;        
        using reference = ValueType&;

        BasicIterator();
        BasicIterator(const BasicIterator<Type>& other) noexcept;
        BasicIterator& operator=(const BasicIterator& rhs) = default;

        [[nodiscard]] bool operator==(const BasicIterator<const Type>& rhs) const noexcept;
        [[nodiscard]] bool operator!=(const BasicIterator<const Type>& rhs) const noexcept;

        BasicIterator& operator++() noexcept;
        BasicIterator operator++(int) noexcept;
        [[nodiscard]] reference operator*() const noexcept;
        [[nodiscard]] pointer operator->() const noexcept;

    private:
        Node* node_ = nullptr;
    };

public:
    SingleLinkedList();
    SingleLinkedList(std::initializer_list<Type> values);
    SingleLinkedList(const SingleLinkedList& other);
    SingleLinkedList& operator=(const SingleLinkedList& rhs);
    
    void swap(SingleLinkedList& other) noexcept;

    using value_type = Type;
    using reference = value_type&;
    using const_reference = const value_type&;   
    using Iterator = BasicIterator<Type>;   
    using ConstIterator = BasicIterator<const Type>;

    [[nodiscard]] Iterator begin() noexcept;
    [[nodiscard]] Iterator end() noexcept;
    [[nodiscard]] ConstIterator begin() const noexcept;
    [[nodiscard]] ConstIterator end() const noexcept;
    [[nodiscard]] ConstIterator cbegin() const noexcept;
    [[nodiscard]] ConstIterator cend() const noexcept;

    ~SingleLinkedList();
    void PushFront(const Type& value);
    void Clear() noexcept;
    [[nodiscard]] size_t GetSize() const noexcept;
    [[nodiscard]] bool IsEmpty() const noexcept;
 
    [[nodiscard]] Iterator before_begin() noexcept;
    [[nodiscard]] ConstIterator cbefore_begin() const noexcept;
    [[nodiscard]] ConstIterator before_begin() const noexcept;

    Iterator InsertAfter(ConstIterator pos, const Type& value);
    void PopFront() noexcept;
    Iterator EraseAfter(ConstIterator pos) noexcept;  

private:
    Node head_;
    size_t size_ = 0;    
};

template <typename Type>
void swap(SingleLinkedList<Type>& lhs, SingleLinkedList<Type>& rhs) noexcept;

template <typename Type>
bool operator==(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs);

template <typename Type>
bool operator!=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs);

template <typename Type>
bool operator<(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs);

template <typename Type>
bool operator<=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs);

template <typename Type>
bool operator>(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs);

template <typename Type>
bool operator>=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs);



// Template implementations for SingleLinkedList and BasicIterator
// Defines all template methods to ensure visibility at the point of use.



template <typename Type>
SingleLinkedList<Type>::Node::Node(const Type& val, Node* next) : value(val), next_node(next) {}

template <typename Type>
template <typename ValueType>
SingleLinkedList<Type>::BasicIterator<ValueType>::BasicIterator(Node* node) : node_(node) {}

template <typename Type>
template <typename ValueType>
SingleLinkedList<Type>::BasicIterator<ValueType>::BasicIterator() = default;

template <typename Type>
template <typename ValueType>
SingleLinkedList<Type>::BasicIterator<ValueType>::BasicIterator(const BasicIterator<Type>& other) noexcept 
    : node_(other.node_) {}

template <typename Type>
SingleLinkedList<Type>::SingleLinkedList() : size_(0) {}

template <typename Type>
SingleLinkedList<Type>::SingleLinkedList(std::initializer_list<Type> values) : size_(0) {
    for (auto it = values.end(); it != values.begin();) {
        --it; // Move to the last element
        PushFront(*it);
    }      
}

template <typename Type>
SingleLinkedList<Type>::SingleLinkedList(const SingleLinkedList& other) {         
    SingleLinkedList elem_copy;
    BasicIterator<Type> head_it{ &elem_copy.head_ };

    for (auto it = other.begin(); it != other.end(); ++it) {
        head_it = elem_copy.InsertAfter(head_it, *it);
    } 
    swap(elem_copy);
}

template <typename Type>
SingleLinkedList<Type>& SingleLinkedList<Type>::operator=(const SingleLinkedList& rhs) { 
    SingleLinkedList tmp = rhs;
    swap(tmp);
    return *this;
}

template <typename Type>
void SingleLinkedList<Type>::swap(SingleLinkedList& other) noexcept {      
    std::swap(head_.next_node, other.head_.next_node);
    std::swap(size_, other.size_);
}

template <typename Type>
typename SingleLinkedList<Type>::Iterator SingleLinkedList<Type>::begin() noexcept { 
    return Iterator(head_.next_node);
}

template <typename Type>
typename SingleLinkedList<Type>::Iterator SingleLinkedList<Type>::end() noexcept {
    return Iterator(nullptr);
}

template <typename Type>
typename SingleLinkedList<Type>::ConstIterator SingleLinkedList<Type>::begin() const noexcept {
    return ConstIterator(head_.next_node);
}

template <typename Type>
typename SingleLinkedList<Type>::ConstIterator SingleLinkedList<Type>::end() const noexcept { 
    return ConstIterator(nullptr);
}

template <typename Type>
typename SingleLinkedList<Type>::ConstIterator SingleLinkedList<Type>::cbegin() const noexcept {
    return ConstIterator(head_.next_node);
}

template <typename Type>
typename SingleLinkedList<Type>::ConstIterator SingleLinkedList<Type>::cend() const noexcept {
    return ConstIterator(nullptr);
}

template <typename Type>
SingleLinkedList<Type>::~SingleLinkedList() {
    Clear();
}

template <typename Type>
void SingleLinkedList<Type>::PushFront(const Type& value) {
    head_.next_node = new Node(value, head_.next_node);
    ++size_;
}

template <typename Type>
void SingleLinkedList<Type>::Clear() noexcept {
    while (head_.next_node != nullptr) {
        Node* copy = head_.next_node;
        head_.next_node = copy->next_node;            
        delete copy;            
    }
    size_ = 0;
}

template <typename Type>
size_t SingleLinkedList<Type>::GetSize() const noexcept {
    return size_;
}

template <typename Type>
bool SingleLinkedList<Type>::IsEmpty() const noexcept {
    return size_ == 0;
}

template <typename Type>
typename SingleLinkedList<Type>::Iterator SingleLinkedList<Type>::before_begin() noexcept {
    return Iterator(&head_);
}

template <typename Type>
typename SingleLinkedList<Type>::ConstIterator SingleLinkedList<Type>::cbefore_begin() const noexcept {
    return ConstIterator(const_cast<Node*>(&head_));
}

template <typename Type>
typename SingleLinkedList<Type>::ConstIterator SingleLinkedList<Type>::before_begin() const noexcept {        
    return cbefore_begin();
}

template <typename Type>
typename SingleLinkedList<Type>::Iterator SingleLinkedList<Type>::InsertAfter(ConstIterator pos, const Type& value) {
    assert(pos.node_ != nullptr);
    Node* new_node = new Node(value, pos.node_->next_node);
    pos.node_->next_node = new_node;
    ++size_;
    return Iterator(new_node);
}

template <typename Type>
void SingleLinkedList<Type>::PopFront() noexcept {
    if (size_ > 0) {
        Node* node_to_delete = head_.next_node;
        head_.next_node = head_.next_node->next_node;
        delete node_to_delete;
        --size_;
    }
}

template <typename Type>
typename SingleLinkedList<Type>::Iterator SingleLinkedList<Type>::EraseAfter(ConstIterator pos) noexcept {
    assert(pos.node_ != nullptr);
    Node* node_to_delete = pos.node_->next_node;
    if (node_to_delete != nullptr) {
        pos.node_->next_node = node_to_delete->next_node;
        delete node_to_delete;
        --size_;
    }
    return Iterator(pos.node_->next_node);
}

template <typename Type>
void swap(SingleLinkedList<Type>& lhs, SingleLinkedList<Type>& rhs) noexcept {
    lhs.swap(rhs);
}

template <typename Type>
template <typename ValueType>
typename SingleLinkedList<Type>::template BasicIterator<ValueType>&
SingleLinkedList<Type>::BasicIterator<ValueType>::operator++() noexcept {
    assert(node_ != nullptr);
    node_ = node_->next_node;
    return *this;    
}

template <typename Type>
template <typename ValueType>
typename SingleLinkedList<Type>::template BasicIterator<ValueType>
SingleLinkedList<Type>::BasicIterator<ValueType>:: operator++(int) noexcept {
	auto old_value(*this); 
	++(*this); 
	return old_value;
}

template <typename Type>
template <typename ValueType>
[[nodiscard]] typename SingleLinkedList<Type>::template BasicIterator<ValueType>::reference
SingleLinkedList<Type>::BasicIterator<ValueType>::operator*() const noexcept {
    assert(node_ != nullptr);
    return node_->value;
}

template <typename Type>
template <typename ValueType>
[[nodiscard]] typename SingleLinkedList<Type>::template BasicIterator<ValueType>::pointer 
SingleLinkedList<Type>::BasicIterator<ValueType>::operator->() const noexcept {
    assert(node_ != nullptr);
    return &(node_->value);        
}

template <typename Type>
template <typename ValueType>
[[nodiscard]] bool SingleLinkedList<Type>::BasicIterator<ValueType>::operator==(
    const BasicIterator<const Type>& rhs) const noexcept {
    return this->node_ == rhs.node_;
}

template <typename Type>
template <typename ValueType>
[[nodiscard]] bool SingleLinkedList<Type>::BasicIterator<ValueType>::operator!=(
    const BasicIterator<const Type>& rhs) const noexcept {
    return this->node_ != rhs.node_;
}

template <typename Type>
bool operator==(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    if (lhs.GetSize() != rhs.GetSize()) {
        return false;
    }
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename Type>
bool operator!=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return !(lhs == rhs);
}

template <typename Type>
bool operator<(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
bool operator<=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return !(lhs > rhs);
}

template <typename Type>
bool operator>(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return rhs < lhs;
}

template <typename Type>
bool operator>=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return !(lhs < rhs);
}
