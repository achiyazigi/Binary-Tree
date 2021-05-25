#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
#include "TreeIterator.hpp"
#include <stack>

namespace ariel
{

    template <typename T>
    class BinaryTree
    {

    private:
        Node<T> *root = nullptr;

        void print_vector_as_tree_recursive(std::ostream &out, Node<T> *root = 0, std::string prefix = "") const
        {
            if (root == nullptr)
                return;
            out << std::endl
                << prefix << root->value;
            print_vector_as_tree_recursive(out, root->left, prefix + "--");
            print_vector_as_tree_recursive(out, root->right, prefix + "--");
        }

    public:
        //-------------------------------------------------------------------
        // pre_iterator related code:
        // inner class and methods that return instances of it)
        //-------------------------------------------------------------------
        class pre_iterator : public TreeIterator<T>
        {
        private:
            std::stack<Node<T> *> s;

        public:
            using TreeIterator<T>::TreeIterator;
            pre_iterator &operator++()
            {
                if (this->p_to_cur == nullptr)
                {

                    throw std::out_of_range("out of range");
                }
                else
                {
                    if (this->p_to_cur->right != nullptr)
                    {
                        s.push(this->p_to_cur->right);
                    }
                    if (this->p_to_cur->left != nullptr)
                    {
                        this->p_to_cur = this->p_to_cur->left;
                    }
                    else if (!s.empty())
                    {
                        this->p_to_cur = s.top();
                        s.pop();
                    }
                    else
                    {
                        this->p_to_cur = nullptr;
                    }
                }
                return *this;
            }

            pre_iterator &operator++(int)
            {
                pre_iterator res = *this;
                *this ++;
                return res;
            }

        }; // END OF CLASS pre_ITERATOR
        class in_iterator : public TreeIterator<T>
        {
        public:
            std::vector<Node<T> *> v;

        private:
            virtual void recursive_init(Node<T> *n)
            {

                if (n != nullptr)
                {
                    auto index = std::find(this->v.begin(), this->v.end(), n);
                    if (n->left != nullptr)
                    {

                        v.insert(index, n->left);
                    }
                    index = std::find(this->v.begin(), this->v.end(), n);
                    if (n->right != nullptr)
                    {
                        v.insert(++index, n->right);
                    }
                    recursive_init(n->left);
                    recursive_init(n->right);
                }
            }

        public:
            in_iterator(Node<T> *ptr) : TreeIterator<T>(ptr)
            {
                if (ptr != nullptr)
                {
                    this->v.resize(1);
                    this->v.front() = ptr;
                    this->recursive_init(ptr);
                    this->p_to_cur = this->v.front();
                }
            }
            virtual in_iterator &operator++()
            {
                if (this->p_to_cur == nullptr)
                {

                    throw std::out_of_range("out of range");
                }

                auto pp = this->v.erase(this->v.begin());
                if (pp == this->v.end())
                {
                    this->p_to_cur = nullptr;
                }
                else
                {
                    this->p_to_cur = *pp;
                }
                return *this;
            }

            in_iterator &operator++(int)
            {
                in_iterator res{*this};
                ++(*this);
                return res;
            }

        }; // END OF CLASS in_ITERATOR

        class post_iterator : public in_iterator
        {
        private:
            void recursive_init(Node<T> *n) override
            {
                if (n != nullptr)
                {
                    auto index = std::find(this->v.begin(), this->v.end(), n);
                    if (n->left != nullptr)
                    {

                        this->v.insert(index, n->left);
                    }
                    index = std::find(this->v.begin(), this->v.end(), n);
                    if (n->right != nullptr)
                    {
                        this->v.insert(index, n->right);
                    }
                    recursive_init(n->left);
                    recursive_init(n->right);
                }
            }

        public:
            post_iterator(Node<T> *ptr = nullptr) : in_iterator(nullptr)
            {
                if (ptr != nullptr)
                {
                    this->v.resize(1);
                    this->v.front() = ptr;
                    this->recursive_init(ptr);
                    this->p_to_cur = this->v.front();
                }
            }
            using in_iterator::operator++;
            // using in_iterator::operator++(int);
            // post_iterator& operator++(){
            //     auto res = in_iterator::operator++();
            //     return *this;
            // }
            // post_iterator& operator++(int){
            //     auto res = this++;
            //     return *this;
            // }
        };

        pre_iterator begin_preorder() const
        {
            return pre_iterator{root};
        }

        pre_iterator end_preorder() const
        {
            return pre_iterator{nullptr};
        }

        //in order
        in_iterator begin_inorder()
        {
            return in_iterator{root};
        }

        in_iterator end_inorder()
        {
            return in_iterator{nullptr};
        }

        in_iterator begin()
        {
            return this->begin_inorder();
        }

        in_iterator end()
        {
            return this->end_inorder();
        }

        post_iterator begin_postorder()
        {
            return post_iterator{root};
        }

        post_iterator end_postorder()
        {
            return post_iterator{nullptr};
        }

        BinaryTree() = default;
        BinaryTree &add_root(const T &value)
        {
            if (root == nullptr)
            {
                root = new Node<T>{nullptr, nullptr, nullptr, value};
            }
            else
            {

                root->value = value;
            }
            return *this;
        }
        BinaryTree &add_left(const T &parent, const T &value)
        {
            auto it = this->begin_preorder();
            auto end = this->end_preorder();
            while (it != end && it->value != value)
            {
                if (it->value == parent)
                {
                    if (it->left == nullptr)
                    {
                        it->left = new Node<T>{it->pointer(), nullptr, nullptr, value};
                    }
                    else
                    {
                        it->left->value = value;
                    }
                    return *this;
                }
                ++it;
            }
            throw std::out_of_range("");

            return *this;
        }
        BinaryTree &add_right(const T &parent, const T &value)
        {

            auto it = this->begin_preorder();
            auto end = this->end_preorder();
            while (it != end)
            {
                if (it->value == parent)
                {
                    if (it->right == nullptr)
                    {
                        it->right = new Node<T>{it->pointer(), nullptr, nullptr, value};
                    }
                    else
                    {
                        it->right->value = value;
                    }
                    return *this;
                }
                ++it;
            }
            throw std::out_of_range("");
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