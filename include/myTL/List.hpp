/**
 * @file List.hpp
 * @author 최우혁

 * @brief double-linked-list toolkit declarations
 */

#ifndef __INC_LIST_HPP
#define __INC_LIST_HPP

namespace My{
    // double-linked-list의 node
    template<typename data_type> struct Node;

    template<typename data_type> class List_ConstIterator;
    template<typename data_type> class List_Iterator;
    template<typename data_type> class List;

    template<typename data_type>
    class List_ConstIterator{
    private:
        using self_type=List_ConstIterator<data_type>;
        using value_type=const data_type;
        using reference_type=const data_type&;
        using pointer_type=const data_type*;
        using iterator_category=std::bidirectional_iterator_tag;
        using node=const Node<data_type>;

    public:
        friend class My::List<data_type>;

    private:
        node *pNode;

    public:
        List_ConstIterator(node* pNode):pNode(pNode){}
        List_ConstIterator(const self_type& that):pNode(that.pNode){}

        // bidirectional iterator
        inline self_type& operator++(){ if(pNode!=nullptr) pNode=pNode->next; return *this;}
        inline self_type operator++(int){ self_type temp=pNode; if(pNode!=nullptr) pNode=pNode->next; return temp;}
        inline self_type& operator--(){ if(pNode!=nullptr) pNode=pNode->prev; return *this;}
        inline self_type operator--(int){ self_type temp=pNode; if(pNode!=nullptr) pNode=pNode->prev; return temp;}

    private:
        // operator+과 operator-의 코드 중복을 제거하기 위한 용도
        self_type add_sub_aux(const int) const;

    public:
        // random access iterator은 아니지만,
        // 순차 접근을 통해 구현.
        inline self_type operator+(const int n) const{ return add_sub_aux(n); }
        inline self_type operator-(const int n) const{ return add_sub_aux(-n); }

        inline reference_type operator*() const{ return *(pNode->data); }
        inline pointer_type operator->() const{ return pNode->data;}

        // 두 iterator 모두 같은 node를 가리키는지 확인함.
        inline bool operator==(const self_type& rhs) const{ return pNode==rhs.pNode; }
        inline bool operator!=(const self_type& rhs) const{ return !(*this==rhs); }

        // 만료된 저장공간를 가리키는지 확인(X)
        // list의 tail 다음 요소를 가리키는 iterator인지 확인(O)
        inline bool is_null(void) const{ return pNode==nullptr; }
    };
    
    // param: Node Initializing Argument

    // new keyword를 사용하지 않고, node를 만들 수 있도록 함.
    template<typename data_type>
    Node<data_type>* createNode(
        const data_type& value,
        Node<data_type>* prev=nullptr, Node<data_type>* next=nullptr
    );

    // param 1(in        ): list head

    // list element의 개수
    template<typename data_type>
    const size_t list_length(Node<data_type>*);

    // param 1(in        ): list head/tail
    // param 2(in        ): value to be searched
    
    // 앞에서부터
    // list에 특정 값이 속해있는지 찾음.
    // 있을 경우 그에 해당하는 node*를
    // 없을 경우 nullptr을 return
    template<typename data_type>
    Node<data_type>* list_search(Node<data_type>*, const data_type&);

    // 뒤에서부터
    // list에 특정 값이 속해있는지 찾음.
    // 있을 경우 그에 해당하는 node*를
    // 없을 경우 nullptr을 return
    template<typename data_type>
    Node<data_type>* list_tail_search(Node<data_type>*, const data_type&);

    // param 1(in        ): list head
    // param 2(in        ): index

    // 특정 번째에 해당하는 노드를 찾음.
    // 있을 경우 그에 해당하는 node*를
    // 없을 경우 nullptr을 return
    template<typename data_type>
    Node<data_type>* list_locate(const Node<data_type>*, const int);

    // list가 head에 해당하는 pointer와, tail에 해당하는 poiter을 가진다고 가정.
    // list를 수정하는 작업(head와 tail을 바꿔줘야되는 작업)일 경우,
    // head와 tail을 바꿔주기 위해 reference to pointer 사용.

    // param 1(in and out): list head
    // param 2(in and out): list tail
    // param 3(in        ): value to be inserted

    // list tail 뒤에 value를 추가함.
    // param 1과 param 2가 같은 list에서 나온건지 검사하지 않음.
    template<typename data_type>
    void list_insert(Node<data_type>*&, Node<data_type>*&, const data_type&);

    // list head 앞에 value를 추가함.
    // param 1과 param 2가 같은 list에서 나온건지 검사하지 않음.
    template<typename data_type>
    void list_head_insert(Node<data_type>*&, Node<data_type>*&, const data_type&);

    // param 1(in and out): list head
    // param 2(in and out): list tail
    // param 3(in        ): value to be removed

    // 앞에서부터 (list_search를 이용)
    // list에 특정 값이 속해있는지 찾고,
    // 있을 경우 그 node를 삭제함.
    template<typename data_type>
    void list_head_remove(Node<data_type>*&, Node<data_type>*&, const data_type&);
    
    // 뒤에서부터 (list_tail_search를 이용)
    // list에 특정 값이 속해있는지 찾고,
    // 있을 경우 그 node를 삭제함.
    template<typename data_type>
    void list_remove(Node<data_type>*&, Node<data_type>*&, const data_type&);

    // param 1(in and out): list head
    // param 2(in and out): list tail

    // list의 모든 element를 삭제함.
    template<typename data_type>
    void list_clear(Node<data_type>*&, Node<data_type>*&);

    // param 1(in and out): dest list head
    // param 2(in and out): dest list tail
    // param 3(in        ): src list head

    // src list 뒤에 dest list의 elements를 추가함.
    // src list의 기존 elements, dest list의 elements는 그대로 있음.
    template<typename data_type>
    void list_append(Node<data_type>*&, Node<data_type>*&, Node<data_type>*);

    // src list에 dest list를 복사함.
    // src list의 기존 elements는 전부 삭제됨.
    template<typename data_type>
    void list_copy(Node<data_type>* &dest_head, Node<data_type>* &dest_tail, Node<data_type>* src);

    // param 1(in        ): list 1 head
    // param 2(in        ): list 2 head

    // list 1의 elements와 list2의 elements가 같은지 검사함.
    // 순서가 다르거나, 값이 다르거나, list의 길이가 다를 경우 true
    template<typename data_type>
    bool list_compare(Node<data_type>*, Node<data_type>*);
}

#endif // __INC_LIST_HPP