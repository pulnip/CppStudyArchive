#ifndef __INC_SET_HPP
#define __INC_SET_HPP

namespace My{
    template<typename data_type, std::size_t MINIMUM=1>
    class Set{
    private:
        using value_type=data_type;
        using self_type=Set<data_type, MINIMUM>;
    
    private:
        static constexpr std::size_t MIN=MINIMUM;
        static constexpr std::size_t MAX=2*MINIMUM;

        struct Node{
        public:
            Node* parent=nullptr;
            
            std::size_t data_count=0;
            value_type* data[MAX+1]={nullptr, };

            std::size_t child_count=0;
            Node* subset[MAX+2]={nullptr, };

        public:
            Node()=default;
            ~Node();
            /**
             * @brief Auxiliary function for Set::contains 
             */
            bool contains(const value_type&);
            /**
             * @brief Auxiliary function for Set::loose_insert
             */
            Node* loose_insert(const value_type&);
            /**
             * @return new root(or root)
             */
            Node* fix_excess(void);
            /**
             * @brief Auxiliary function for Set::show_contents
             */
            void show_contents(const std::size_t depth=0) const;
            /**
             * @brief find target at data and subset
             */
            Node* search(const value_type& target);
            /**
             * @return short leaf
             */
            Node* loose_erase(const value_type&);
            /**
             * @return new root(or root)
             */
            Node* fix_shortage(void);

            /**
             * @brief copy node
             */
            Node(const Node&, Node*);
            Node& operator=(const Node&)=delete;

        private:
            /**
             * @brief find target at data(array) using binary search
             * 
             * @return Index of Target element, or Index of the First element to exceed target 
             */
            std::size_t data_search(const value_type& target) const;
            /**
             * @param idx position to be pushed
             */
            void push(const int idx, value_type* target);
            /**
             * @param idx position to be poped
             */
            value_type* pop(const int idx);
            /**
             * @param idx position to be pushed
             */
            void pushSet(const int idx, Node* target);
            /**
             * @param idx position to be poped
             */
            Node* popSet(const int idx);
            /**
             * @brief Constructor for force_insert
             */
            Node(Node* left, value_type* mid, Node* right);
            /**
             * @return rightmost leaf's rightmost value
             */
            Node* get_rightmost_node(void);
            /**
             * @return remove biggest value from data(*member)
             */
            value_type* data_remove_biggest(void);
        } *root=new Node();

    public:
        Set()=default;
        Set(const std::initializer_list<value_type>&);
        ~Set();
        /**
         * @brief searching for an item
         * 
         * @return true if target is found. else false
         */
        bool contains(const value_type&);
        /**
         * @brief searching for an item
         * 
         * @return 1 if target is found. else 0
         */
        int count(const value_type&);
        /**
         * @brief insert an item to Set
         * 
         * @return true if insert success, else false(target already exist in Set)
         */
        bool insert(const value_type&);
        /**
         * @brief erase an item from Set
         * 
         * @return true if erase success, else false(target is not in Set)
         */
        bool erase(const value_type&);
        /**
         * @brief make set empty
         * 
         * @return reference of this
         */
        self_type& clear(void);
        /**
         * @return true if set is empty, else false 
         */
        bool empty(void);
        /**
         * @brief copy other set
         */
        self_type& operator=(const self_type& that);
        /**
         * @brief copy by initializer_list
         */
        self_type& operator=(const std::initializer_list<value_type>&);
        /**
         * @brief show the element of the Set(B-Tree) in graph
         */
        void show_contents(void);
    };
}

#endif // __INC_SET_HPP