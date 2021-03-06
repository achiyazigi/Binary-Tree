#include <iostream>
#include <iterator>
#include <vector>
#include <memory>

namespace ariel
{

    template <typename T>
    class BinaryTree
    {

    private:
        struct Node
        {
            Node *left = nullptr;
            Node *right = nullptr;
            T value;
            Node(T value, Node *left = nullptr, Node *right = nullptr) : value(value), left(left), right(right) {}
            Node(const Node &other) : value(other.value)
            {
                if (other.left != nullptr)
                {
                    this->left = new Node(*(other.left));
                }
                if (other.right != nullptr)
                {
                    this->right = new Node(*(other.right));
                }
            }
            Node(Node &&other) noexcept
            {
                *this = std::move(other);
            }
            ~Node()
            {
                if (this->left != nullptr)
                {
                    delete this->left;
                }
                if (this->right != nullptr)
                {
                    delete this->right;
                }
            }

            Node &operator=(Node &&other) noexcept
            {
                *this = std::move(other);
                return *this;
            }
            Node &operator=(const Node &other)
            {
                if (this != &other)
                {

                    this = new Node(other);
                }
                return *this;
            }
        };
        typename std::vector<T *> pre_list;
        typename std::vector<T *> in_list;
        typename std::vector<T *> post_list;
        size_t _size = 0;
        Node *root = nullptr;

        void print_vector_as_tree_recursive(std::ostream &out, Node *root = 0, const std::string &prefix = "") const
        {
            if (root == nullptr)
            {
                return;
            }
            out << std::endl
                << prefix << root->value;
            print_vector_as_tree_recursive(out, root->left, prefix + "--");
            print_vector_as_tree_recursive(out, root->right, prefix + "--");
        }

        Node *find(Node *n, const T &value) const
        {
            if (n == nullptr)
            {
                return nullptr;
            }
            if (n->value == value)
            {
                return n;
            }
            Node *res_left = this->find(n->left, value);
            if (res_left != nullptr)
            {
                return res_left;
            }
            return find(n->right, value);
        }

        class iterator
        {
            unsigned long index;
            typename std::vector<T *> *order;

        public:
            iterator(unsigned long root, std::vector<T *> *order) : index(root), order(order)
            {
            }
            iterator(const iterator &other) : index(other.index), order(other.order) {}
            iterator(iterator &&other) noexcept : index(other.index)
            {
                *this = std::move(other);
            }
            ~iterator() = default;
            iterator &operator=(const iterator &other)
            {
                if (this != &other)
                {

                    this->index = other.index;
                    this->order = other.order;
                }
                return *this;
            }
            iterator &operator=(iterator &&other) noexcept
            {
                this->index = std::move(other.index);
                this->order = std::move(other.order);
                return *this;
            }
            iterator &operator++()
            {
                ++(this->index);
                return *this;
            }

            iterator operator++(int)
            {
                iterator res{*this};
                ++(this->index);
                return res;
            }

            T &operator*()
            {
                return *(this->order->at(this->index));
            }

            T *operator->()
            {
                return this->order->at(index);
            }

            bool operator==(const iterator &other) const
            {
                return (this->index == other.index && *(this->order) == *(other.order)) ||
                       (this->index >= this->order->size() && other.index >= other.order->size());
            }

            bool operator!=(const iterator &other) const
            {
                return !(*this == other);
            }

        }; // END OF CLASS ITERATOR

        void init_postorder(const Node *n)
        {
            if (n != nullptr)
            {

                auto it = std::find(this->post_list.begin(), this->post_list.end(), &(n->value));
                if (n->right != nullptr)
                {
                    it = this->post_list.insert(it, &(n->right->value));
                }
                if (n->left != nullptr)
                {
                    it = this->post_list.insert(it, &(n->left->value));
                }
                init_postorder(n->left);
                init_postorder(n->right);
            }
        }
        void init_preorder(const Node *n)
        {
            if (n != nullptr)
            {
                auto it = std::find(this->pre_list.begin(), this->pre_list.end(), &(n->value));
                ++it;
                if (n->right != nullptr)
                {

                    it = this->pre_list.insert(it, &(n->right->value));
                }
                if (n->left != nullptr)
                {
                    this->pre_list.insert(it, &(n->left->value));
                }
                init_preorder(n->left);
                init_preorder(n->right);
            }
        }
        void init_inorder(const Node *n)
        {
            if (n != nullptr)
            {
                auto it = std::find(this->in_list.begin(), this->in_list.end(), &(n->value));
                if (n->left != nullptr)
                {
                    it = this->in_list.insert(it, &(n->left->value));
                    ++it;
                }
                if (n->right != nullptr)
                {

                    this->in_list.insert(++it, &(n->right->value));
                }
                init_inorder(n->left);
                init_inorder(n->right);
            }
        }

    public:
        size_t size() const
        {
            return this->_size;
        }
        iterator begin_preorder()
        {
            if (root == nullptr)
            {
                return this->end_preorder();
            }
            this->pre_list.resize(this->size());
            this->pre_list.clear();
            this->pre_list.push_back(&(this->root->value));
            init_preorder(this->root);
            return iterator{0, &(this->pre_list)};
        }

        iterator end_preorder()
        {
            this->pre_list.resize(this->size());
            this->pre_list.clear();
            if (root != nullptr)
            {
                this->pre_list.push_back(&(this->root->value));
                init_preorder(this->root);
            }
            return iterator{this->pre_list.size(), &(this->pre_list)};
        }

        //in order
        iterator begin_inorder()
        {
            if (root == nullptr)
            {
                return this->end_inorder();
            }
            this->in_list.resize(this->size());

            this->in_list.clear();
            this->in_list.push_back(&(this->root->value));
            init_inorder(this->root);
            return iterator{0, &(this->in_list)};
        }

        iterator end_inorder()
        {
            this->in_list.resize(this->size());

            this->in_list.clear();
            if (root != nullptr)
            {
                this->in_list.push_back(&(this->root->value));
                init_inorder(this->root);
            }
            return iterator{this->in_list.size(), &(this->in_list)};
        }

        iterator begin()
        {
            return this->begin_inorder();
        }

        iterator end()
        {
            return this->end_inorder();
        }

        iterator begin_postorder()
        {
            if (root == nullptr)
            {
                return this->end_postorder();
            }
            this->post_list.resize(this->size());

            this->post_list.clear();
            this->post_list.push_back(&(this->root->value));
            init_postorder(this->root);
            return iterator{0, &(this->post_list)};
        }

        iterator end_postorder()
        {
            this->post_list.resize(this->size());

            this->post_list.clear();
            if (root != nullptr)
            {
                this->post_list.push_back(&(this->root->value));
                init_postorder(this->root);
            }
            return iterator{this->post_list.size(), &(this->post_list)};
        }

        BinaryTree() {}
        BinaryTree(const BinaryTree &other) : _size(other.size())
        {
            if (other.root != nullptr)
            {
                this->root = new Node(*(other.root));
            }
            for_each(other.in_list.begin(), other.in_list.end(), [=](T *val)
                     { this->in_list.push_back(new T(*val)); });
            for_each(other.pre_list.begin(), other.pre_list.end(), [=](T *val)
                     { this->pre_list.push_back(new T(*val)); });
            for_each(other.post_list.begin(), other.post_list.end(), [=](T *val)
                     { this->post_list.push_back(new T(*val)); });
        }
        BinaryTree(BinaryTree &&other) noexcept : _size(other.size())
        {
            *this = std::move(other);
        }
        ~BinaryTree()
        {
            delete this->root;
        }
        BinaryTree &add_root(const T &value)
        {
            if (this->root == nullptr)
            {
                this->root = new Node(value);
                this->_size = 1;
            }
            else
            {
                this->root->value = value;
            }
            return *this;
        }
        BinaryTree &add_left(const T &parent, const T &value)
        {
            Node *parent_found = this->find((this->root), parent);
            if (parent_found == nullptr)
            {
                throw std::out_of_range("no such parent");
            }

            if (parent_found->left == nullptr)
            {
                parent_found->left = new Node{value};
                ++this->_size;
            }
            else
            {

                parent_found->left->value = value;
            }

            return *this;
        }
        BinaryTree &add_right(const T &parent, const T &value)
        {

            Node *parent_found = this->find(this->root, parent);
            if (parent_found == nullptr)
            {
                throw std::out_of_range("no such parent");
            }

            if (parent_found->right == nullptr)
            {
                parent_found->right = new Node{value};
                ++this->_size;
            }
            else
            {
                parent_found->right->value = value;
            }

            return *this;
        }

        BinaryTree &operator=(const BinaryTree &other)
        {
            if (this != &other)
            {
                if (other.root != nullptr)
                {
                    this->root = new Node(*(other.root));
                }
                for_each(other.in_list.begin(), other.in_list.end(), [=](T *val)
                         { this->in_list.push_back(new T(*val)); });
                for_each(other.pre_list.begin(), other.pre_list.end(), [=](T *val)
                         { this->pre_list.push_back(new T(*val)); });
                for_each(other.post_list.begin(), other.post_list.end(), [=](T *val)
                         { this->post_list.push_back(new T(*val)); });
            }
            return *this;
        }
        BinaryTree &operator=(BinaryTree &&other) noexcept
        {
            *this = std::move(other);
            return *this;
        }

        friend std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &b)
        {
            b.print_vector_as_tree_recursive(os, b.root, "-");
            os << std::endl;
            return os;
        }
    };
}