#include <iostream>
#include <memory>
#include <algorithm>
#include <iterator>
#include <vector>


template <typename Key>
class Set {
private:
    struct BaseNode {
        std::shared_ptr<BaseNode>  left_child_ptr;
    };

    struct Node: BaseNode {
        Key key;
        int height;
        std::shared_ptr<Node>  left_child_ptr;
        std::shared_ptr<Node> right_child_ptr;

        Node(const Key& key, const int& height = 0): key(key), height(height) {}
    };


    static int get_height(const std::shared_ptr<Node>& node_ptr) {
        if (node_ptr)
            return node_ptr->height;
        return 0;
    }

    static std::shared_ptr<Node> RightRotation(const std::shared_ptr<Node>& head) {
        auto newhead = head->left_child_ptr;
        head->left_child_ptr = newhead->right_child_ptr;
        newhead->right_child_ptr = head;
        head->height = 1 + std::max(get_height(head->left_child_ptr),
                                    get_height(head->right_child_ptr));
        newhead->height = 1 + std::max(get_height(newhead->left_child_ptr),
                                       get_height(newhead->right_child_ptr));
        return newhead;
    }

    static std::shared_ptr<Node> LeftRotation(const std::shared_ptr<Node>& head){
        auto newhead = head->right_child_ptr;
        head->right_child_ptr = newhead->left_child_ptr;
        newhead->left_child_ptr = head;
        head->height = 1 + std::max(get_height(head->left_child_ptr),
                                    get_height(head->right_child_ptr));
        newhead->height = 1 + std::max(get_height(newhead->left_child_ptr),
                                       get_height(newhead->right_child_ptr));
        return newhead;
    }

    static std::shared_ptr<Node> Balance(const std::shared_ptr<Node>& node) {
        int balance = get_height(node->left_child_ptr) - get_height(node->right_child_ptr);
        if (balance > 1) {
            if (get_height(node->left_child_ptr) >= get_height(node->right_child_ptr)) {
                return RightRotation(node);
            } else {
                node->left_child_ptr = LeftRotation(node->left_child_ptr);
                return RightRotation(node);
            }
        } else if (balance < -1) {
            if (get_height(node->right_child_ptr) >= get_height(node->left_child_ptr)) {
                return LeftRotation(node);
            } else {
                node->right_child_ptr = RightRotation(node->right_child_ptr);
                return LeftRotation(node);
            }
        }
        return node;
    }

    std::shared_ptr<Node> Insert(const std::shared_ptr<Node>& node, const Key& new_key) {
        if (!node) {
            size_ += 1;
            auto new_node = std::make_shared<Node>(new_key);
            if (leftmost_node_ptr_ == root_ptr_
            || new_key < std::static_pointer_cast<Node>(leftmost_node_ptr_)->key)
                leftmost_node_ptr_ = new_node;
            return new_node;
        }
        if (new_key < node->key)
            node->left_child_ptr = Insert(node->left_child_ptr, new_key);
        else if (node->key < new_key)
            node->right_child_ptr = Insert(node->right_child_ptr, new_key);
        node->height = 1 + std::max(get_height(node->left_child_ptr),
                                    get_height(node->right_child_ptr));
        return Balance(node);
    }

    std::shared_ptr<Node> Remove(std::shared_ptr<Node> node,
                                 const Key& new_key,
                                 bool size_can_decrease = true) {
        if (!node)
            return nullptr;
        if (new_key < node->key) {
            node->left_child_ptr = Remove(node->left_child_ptr, new_key);
        } else if (node->key < new_key) {
            node->right_child_ptr = Remove(node->right_child_ptr, new_key);
        } else {
            if (size_can_decrease) {
                --size_;
                auto leftmost_key = std::static_pointer_cast<Node>(leftmost_node_ptr_)->key;
                if (!(leftmost_key < new_key || new_key < leftmost_key))
                    leftmost_node_ptr_ = size_ > 0 ?
                            Next(new_key, root_ptr_) : root_ptr_;
            }
            auto right_ptr = node->right_child_ptr;
            if (!node->right_child_ptr) {
                node = node->left_child_ptr;
            } else if (!node->left_child_ptr) {
                node = right_ptr;
            } else {
                while(right_ptr->left_child_ptr)
                    right_ptr = right_ptr->left_child_ptr;
                node->key = right_ptr->key;
                node->right_child_ptr = Remove(node->right_child_ptr, right_ptr->key, false);
            }
        }
        if (!node)
            return node;
        node->height = 1 + std::max(get_height(node->left_child_ptr),
                                    get_height(node->right_child_ptr));
        return Balance(node);
    }

    static std::shared_ptr<Node> Find(const std::shared_ptr<Node>& node,
                               const Key& key) {
        if (!node)
            return nullptr;
        if (key < node->key)
            return Find(node->left_child_ptr, key);
        else if (node->key < key)
            return Find(node->right_child_ptr, key);
        return node;
    }

    static std::shared_ptr<Node> LowerBound(const std::shared_ptr<Node>& node,
                                     const Key& key,
                                     std::shared_ptr<Node> current_lower_bound) {
        if (!node)
            return current_lower_bound;
        if (key < node->key) {
            if (current_lower_bound->key < key || node->key < current_lower_bound->key)
                current_lower_bound = node;
            return LowerBound(node->left_child_ptr, key, current_lower_bound);
        }
        else if (node->key < key)
            return LowerBound(node->right_child_ptr, key, current_lower_bound);
        return node;
    }

    static std::shared_ptr<Node> Next(const Key& key,
                                      const std::shared_ptr<BaseNode>& root_ptr) {
        std::shared_ptr<Node> node = std::static_pointer_cast<Node>(root_ptr->left_child_ptr);
        std::shared_ptr<Node> res;
        while (node) {
            if (key < node->key) {
                res = node;
                node = node->left_child_ptr;
            } else {
                node = node->right_child_ptr;
            }
        }
        return res;
    }

    static std::shared_ptr<Node> Prev(const Key& key,
                                      const std::shared_ptr<BaseNode>& root_ptr) {
        std::shared_ptr<Node> node = std::static_pointer_cast<Node>(root_ptr->left_child_ptr);
        std::shared_ptr<Node> res;
        while (node) {
            if (node->key < key) {
                res = node;
                node = node->right_child_ptr;
            } else {
                node = node->left_child_ptr;
            }
        }
        return res;
    }

    static std::shared_ptr<Node> FindMax(const std::shared_ptr<Node>& node) {
        if (!node)
            return nullptr;
        else if (!node->right_child_ptr)
            return node;
        else
            return FindMax(node->right_child_ptr);
    }

    static void DeepCopy(const std::shared_ptr<Node>& orig_node,
                         std::shared_ptr<Node> copy_node) {
        if(orig_node) {
            if (orig_node->left_child_ptr)
                copy_node->left_child_ptr = std::make_shared<Node>(
                        orig_node->left_child_ptr->key, orig_node->left_child_ptr->height);
            DeepCopy(orig_node->left_child_ptr, copy_node->left_child_ptr);
            if (orig_node->right_child_ptr)
                copy_node->right_child_ptr = std::make_shared<Node>(
                        orig_node->right_child_ptr->key, orig_node->right_child_ptr->height);
            DeepCopy(orig_node->right_child_ptr, copy_node->right_child_ptr);
        }
    }

    static void Print(const std::shared_ptr<Node>& node, std::ostream& out = std::cout) {
        if (node) {
            Print(node->left_child_ptr, out);
            out << node->key << ' ';
            Print(node->right_child_ptr, out);
        }
    }

    struct SetIterator {
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = Key;
        using pointer = Key*;
        using reference = Key&;

        std::shared_ptr<BaseNode> node_ptr;
        std::shared_ptr<BaseNode> root_ptr;

        SetIterator() = default;
        SetIterator(std::shared_ptr<BaseNode> node_ptr, std::shared_ptr<BaseNode> root_ptr)
                : node_ptr(node_ptr), root_ptr(root_ptr) {}
        SetIterator(std::shared_ptr<Node> node_ptr, std::shared_ptr<BaseNode> root_ptr)
                : node_ptr(node_ptr), root_ptr(root_ptr) {}

        const Key& operator*() const {
            return std::static_pointer_cast<Node>(node_ptr)->key;
        }

        const Key* operator->() const {
            return &std::static_pointer_cast<Node>(node_ptr)->key;
        }

        SetIterator& operator++() {
            node_ptr = Next(std::static_pointer_cast<Node>(node_ptr)->key, root_ptr);
            if (!node_ptr)
                node_ptr = root_ptr;
            return *this;
        }

        SetIterator& operator--() {
            if (node_ptr != root_ptr)
                node_ptr = Prev(std::static_pointer_cast<Node>(node_ptr)->key, root_ptr);
            else
                node_ptr = FindMax(std::static_pointer_cast<Node>(root_ptr->left_child_ptr));
            return *this;
        }

        SetIterator operator++(int) {
            SetIterator copy = *this;
            node_ptr = Next(std::static_pointer_cast<Node>(node_ptr)->key, root_ptr);
            if (!node_ptr)
                node_ptr = root_ptr;
            return copy;
        }

        SetIterator operator--(int) {
            SetIterator copy = *this;
            if (node_ptr != root_ptr)
                node_ptr = Prev(std::static_pointer_cast<Node>(node_ptr)->key, root_ptr);
            else
                node_ptr = FindMax(std::static_pointer_cast<Node>(root_ptr->left_child_ptr));
            return copy;
        }

        bool operator==(const SetIterator& other) const {
            return root_ptr == other.root_ptr && node_ptr == other.node_ptr;
        }

        bool operator!=(const SetIterator& other) const {
            return !(*this == other);
        }
    };

    std::shared_ptr<BaseNode> root_ptr_;
    std::shared_ptr<BaseNode> leftmost_node_ptr_;
    size_t size_;

public:
    using value_type = Key;
    using iterator = SetIterator;
    using const_iterator = const SetIterator;

    Set()
    : root_ptr_(std::make_shared<BaseNode>()), leftmost_node_ptr_(root_ptr_), size_(0) {}

    template <typename InputIt>
    Set(InputIt first, InputIt last): Set() {
        InputIt it = first;
        while (it < last)
            root_ptr_->left_child_ptr = Insert(
                    std::static_pointer_cast<Node>(root_ptr_->left_child_ptr), *it++);
    }
    Set(std::initializer_list<Key> init): Set(init.begin(), init.end()) {}
    Set(const Set& other): Set() {
        if (other.root_ptr_->left_child_ptr) {
            root_ptr_->left_child_ptr = std::make_shared<Node>(
                    std::static_pointer_cast<Node>(other.root_ptr_->left_child_ptr)->key,
                    std::static_pointer_cast<Node>(other.root_ptr_->left_child_ptr)->height);
            DeepCopy(std::static_pointer_cast<Node>(other.root_ptr_->left_child_ptr),
                        std::static_pointer_cast<Node>(root_ptr_->left_child_ptr));
            size_ = other.size_;
            leftmost_node_ptr_ = Find(
                    std::static_pointer_cast<Node>(root_ptr_->left_child_ptr),
                    std::static_pointer_cast<Node>(other.leftmost_node_ptr_)->key);
        }
    }
    ~Set() = default;

    Set& operator=(const Set& other) {
        Set tmp = other;
        root_ptr_ = tmp.root_ptr_;
        leftmost_node_ptr_ = tmp.leftmost_node_ptr_;
        size_ = tmp.size_;
        return *this;
    }

    iterator begin() const {
        return {leftmost_node_ptr_, root_ptr_};
    }
    const_iterator cbegin() const {
        return {leftmost_node_ptr_, root_ptr_};
    }
    iterator end() const {
        return {root_ptr_, root_ptr_};
    }
    const_iterator cend() const {
        return {root_ptr_, root_ptr_};
    }

    void insert(const Key& new_key) {
        root_ptr_->left_child_ptr = Insert(
                std::static_pointer_cast<Node>(root_ptr_->left_child_ptr), new_key);
    }
    void erase(const Key& key) {
        root_ptr_->left_child_ptr = Remove(
                std::static_pointer_cast<Node>(root_ptr_->left_child_ptr), key);
    }
    size_t size() const {
        return size_;
    }
    bool empty() const {
        return size_ == 0;
    }
    iterator find(const Key& key) const {
        auto res_it = Find(std::static_pointer_cast<Node>(root_ptr_->left_child_ptr), key);
        if (!res_it)
            return end();
        return {res_it, root_ptr_};
    }
    iterator lower_bound(const Key& key) const {
        if (root_ptr_->left_child_ptr) {
            auto lb = LowerBound(
                    std::static_pointer_cast<Node>(root_ptr_->left_child_ptr),
                    key,
                    std::static_pointer_cast<Node>(root_ptr_->left_child_ptr));
            return lb->key < key ? end() : SetIterator(lb, root_ptr_);
        }
        return end();
    }
    void print(std::ostream& out = std::cout) const {
        Print(std::static_pointer_cast<Node>(root_ptr_->left_child_ptr), out);
    }
};

template <typename Key>
std::ostream& operator<<(std::ostream& out, const Set<Key>& s) {
    s.print(out);
    return out;
}
