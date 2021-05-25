
namespace ariel
{

    template <typename T>
    struct Node
    {
        Node *father;
        Node *left;
        Node *right;
        T value;

        Node(Node *father = nullptr, Node *left = nullptr, Node *right = nullptr, T value = 0) : father(father), left(left), right(right), value(value) {}
       
    };

    //-------------------------------------------------------------------
    // iterator related code:
    // inner class and methods that return instances of it)
    //-------------------------------------------------------------------
    template <typename T>
    class TreeIterator
    {
    public:
        Node<T> *p_to_cur;
        
        TreeIterator(Node<T> *ptr = nullptr) : p_to_cur(ptr)
        {
        }
        TreeIterator(const TreeIterator<T>& t) : p_to_cur(t.p_to_cur)
        {
        }
   
        T &operator*() const
        {
            return p_to_cur->value;
        }

        T *operator->() const
        {
            return &(p_to_cur->value);
        }

        // virtual TreeIterator &operator++();

        // virtual const TreeIterator operator++(int);

        bool operator==(const TreeIterator &rhs) const
        {
            return p_to_cur == rhs.p_to_cur;
        }

        bool operator!=(const TreeIterator &rhs) const
        {
            return p_to_cur != rhs.p_to_cur;
        }
    }; // END OF CLASS TreeIterator
}