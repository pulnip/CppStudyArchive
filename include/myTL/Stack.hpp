#ifndef __INC_STACK_HPP
#define __INC_STACK_HPP

namespace My{
    template<typename data_type>
    class Stack{
    public:
        using self_type=Stack<data_type>;
        using value_type=data_type;
    
    private:
        Node<data_type> *head=nullptr, *tail=nullptr;

    public:
        self_type& push(const value_type& value);
        value_type pop(void);
        value_type& top(void);
        const bool empty(void) const{ return head==nullptr; };
        const size_t size(void);
    };
}

#endif