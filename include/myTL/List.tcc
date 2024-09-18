/**
 * @file List.tcc
 * @author 최우혁
 * 
 * @brief double-linked-list toolkit function definitions
 */

#ifndef __INC_LIST_TCC
#define __INC_LIST_TCC

/**
 * @brief double-linked-list의 node
 * 
 * @tparam data_type list element의 type
 */
template<typename data_type>
struct My::Node{
private:
    using value_type=data_type;
    using self_type=Node<data_type>;

public:
    value_type* data;
    Node *prev=nullptr, *next=nullptr;

public:
    Node(const data_type& value):data(new data_type(value)){}

    /**
     * @brief @p prev 와 this와 @p next 를 연결함.
     * 
     * @param prev this 이전 노드
     * @param next this 이후 노드
     */
    void hook(self_type* prev, self_type* next){
        this->prev=prev;
        this->next=next;

        if(prev!=nullptr) prev->next=this;
        if(next!=nullptr) next->prev=this;
    }

    /**
     * @brief @p prev 와 this와 @p next 의 연결을 끊음.
     */
    void unhook(void){
        if(prev!=nullptr){
            prev->next=next;
        }
        if(next!=nullptr){
            next->prev=prev;
        }
        prev=next=nullptr;
    }

    ~Node(){ unhook(); delete data; }
};

template<typename data_type>
My::Node<data_type>* My::createNode(
    const data_type& value,
    My::Node<data_type>* prev, My::Node<data_type>* next
){
    Node<data_type>* node=new Node<data_type>(value);
    node->hook(prev, next);

    return node;
}

/**
 * @param head list head
 * @return const size_t: list element의 개수
 */
template<typename data_type>
const size_t My::list_length(My::Node<data_type>* head){
    size_t count=0;
    
    for(
        Node<data_type>* cursor=head;
        cursor!=nullptr;
        cursor=cursor->next
    ){
        count+=1;
    }

    return count;
}

/**
 * @brief 앞에서부터 list에 특정 값이 속해있는지 찾음.
 * 
 * @param head list head
 * @param value value to be searched
 * @return My::Node<data_type>*: @p value 에 해당하는 node(없을 경우 nullptr)
 */
template<typename data_type>
My::Node<data_type>* My::list_search(My::Node<data_type>* head, const data_type& value){
    Node<data_type>* cursor=head;

    for(;
        cursor!=nullptr;
        cursor=cursor->next
    ){
        if(value==*(cursor->data)) break;
    }

    return cursor;
}

/**
 * @brief 뒤에서부터 list에 특정 값이 속해있는지 찾음.
 * 
 * @param head list tail
 * @param value value to be searched
 * @return My::Node<data_type>*: @p value 에 해당하는 node(없을 경우 nullptr)
 */
template<typename data_type>
My::Node<data_type>* My::list_tail_search(My::Node<data_type>* tail, const data_type& value){
    Node<data_type>* cursor=tail;

    for(;
        cursor!=nullptr;
        cursor=cursor->prev
    ){
        if(value==*(cursor->data)) break;
    }

    return cursor;
}

/**
 * @brief 특정 번째에 해당하는 노드를 찾음.
 * 
 * @param head list head
 * @param n index
 * @return My::Node<data_type>*: @p n 에 해당하는 node(없을 경우 nullptr)
 */
template<typename data_type>
My::Node<data_type>* My::list_locate(const My::Node<data_type>* head, const int n){
    Node<data_type>* cursor=head;

    for(int i=0; i<n; ++i){
        if(cursor!=nullptr){
            cursor=cursor->next;
        }
        else break;
    }

    return cursor;
}

/**
 * @brief list tail 뒤에 value를 추가함.
 * 
 * @param head list head(in and out)
 * @param tail list tail(in and out)
 * @param value value to be inserted
 */
template<typename data_type>
void My::list_insert(
    My::Node<data_type>* &head, My::Node<data_type>* &tail,
    const data_type& value
){
    // 추가될 node
    Node<data_type>* temp=createNode(
        value,
        tail, (Node<data_type>*)nullptr
    );

    // list의 head와 tail도 바꿔줌.
    if(head==nullptr) head=temp;
    tail=temp;
}

/**
 * @brief list head 앞에 value를 추가함.
 * 
 * @param head list head(in and out)
 * @param tail list tail(in and out)
 * @param value value to be inserted
 */
template<typename data_type>
void My::list_head_insert(
    My::Node<data_type>* &head, My::Node<data_type>* &tail,
    const data_type& value
){
    // 추가될 node
    Node<data_type>* temp=createNode(
        value,
        (Node<data_type>*)nullptr, head
    );

    // list의 head와 tail도 바꿔줌.
    if(tail==nullptr) tail=temp;
    head=temp;
}

/**
 * @brief value가 있을 경우 삭제함. (여러 개일 경우 앞에서부터)
 * 
 * @param head list head(in and out)
 * @param tail list tail(in and out)
 * @param value value to be removed
 */
template<typename data_type>
void My::list_head_remove(
    My::Node<data_type>* &head, My::Node<data_type>* &tail,
    const data_type& value
){
    Node<data_type>* cursor=list_search(head, value);
    
    // value에 해당하는 node가 있으면 nullptr이 아님.
    if(cursor!=nullptr){
        if(head==cursor) head=head->next;
        if(tail==cursor) tail=tail->prev;

        delete cursor;
    }
}

/**
 * @brief value가 있을 경우 삭제함. (여러 개일 경우 뒤에서부터)
 * 
 * @param head list head(in and out)
 * @param tail list tail(in and out)
 * @param value value to be removed
 */
template<typename data_type>
void My::list_remove(
    My::Node<data_type>* &head, My::Node<data_type>* &tail,
    const data_type& value
){
    Node<data_type>* cursor=list_tail_search(tail, value);

    // value에 해당하는 node가 있으면 nullptr이 아님.
    if(cursor!=nullptr){
        if(head==cursor) head=head->next;
        if(tail==cursor) tail=tail->prev;

        delete cursor;
    }
}

/**
 * @brief list의 모든 element를 삭제함.
 * 
 * @param head list head(in and out)
 * @param tail list tail(in and out)
 */
template<typename data_type>
void My::list_clear(
    My::Node<data_type>* &head, My::Node<data_type>* &tail
){
    while(head!=nullptr){
        Node<data_type>* temp=head->next;
        //굳이 일일히 unhook()을 해줄 필요는 없음.
        delete head;
        head=temp;
    }

    head=tail=nullptr;
}

/**
 * @brief src list 뒤에 dest list의 elements를 추가함.
 * 
 * @param dest_head dest list head(in and out)
 * @param dest_tail dest list tail(in and out)
 * @param src src list head
 */
template<typename data_type>
void My::list_append(
    My::Node<data_type>* &dest_head, My::Node<data_type>* &dest_tail,
    My::Node<data_type>* src
){
    if(src!=nullptr){
        for(Node<data_type> *i=src; i!=nullptr; i=i->next){
            list_insert(dest_head, dest_tail, *(i->data));
        }
    }
}

/**
 * @brief src list에 dest list를 복사함.
 * @details src list의 기존 elements는 전부 삭제됨.
 * 
 * @param dest_head dest list head(in and out)
 * @param dest_tail dest list tail(in and out)
 * @param src src list head
 */
template<typename data_type>
void My::list_copy(
    My::Node<data_type>* &dest_head, My::Node<data_type>* &dest_tail,
    My::Node<data_type>* src
){
    list_clear(dest_head, dest_tail);

    list_append(dest_head, dest_tail, src);
}

/**
 * @brief list 1의 elements와 list2의 elements가 같은지 검사함.
 * @details 
 * 1. 순서가 다르거나,
 * 2. 값이 다르거나,
 * 3. list의 길이가 다를 경우
 * true를 반환
 * 
 * @param l1_head list 1 head
 * @param l2_head list 2 head
 * @return false: 순서, 값, 리스트의 길이 모두 일치 
 */
template<typename data_type>
bool My::list_compare(My::Node<data_type>* l1_head, My::Node<data_type>*l2_head){
    Node<data_type> *i1=l1_head, *i2=l2_head;
    for(;
        (i1!=nullptr)&&(i2!=nullptr);
        i1=i1->next, i2=i2->next
    ){
        if(*(i1->data)!=*(i2->data)) break;
    }

    // break에 한 번도 걸리지 않았다면, 적어도 i1 i2 둘 중 하나는 nullptr
    // 둘 중 하나가 nullptr이 아니라면, 두 list의 길이가 다르다는 뜻.
    if((i1!=nullptr)||(i1!=nullptr)) return true;
    
    return false;
}

#endif //__INC_LIST_TCC