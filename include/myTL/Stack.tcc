#ifndef __INC_STACK_TCC
#define __INC_STACK_TCC

template<typename data_type>
My::Stack<data_type>& My::Stack<data_type>::push(const data_type& value){
    list_head_insert(head, tail, value);
    return *this;
}

template<typename data_type>
data_type My::Stack<data_type>::pop(void){
    data_type temp=*(head->data);
    
    Node<data_type>* cursor=head;
    if(cursor!=nullptr){
        head=head->next;
        if(tail==cursor) tail=tail->prev;

        delete cursor;
    }

    return temp;
}

template<typename data_type>
data_type& My::Stack<data_type>::top(void){
    assert(head!=nullptr);
    return *(head->data);
}

template<typename data_type>
const size_t My::Stack<data_type>::size(void){
    return list_length(head);
}

#endif