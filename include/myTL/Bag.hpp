#ifndef __INC_BAG_HPP
#define __INC_BAG_HPP

namespace My{
    // 정렬에 사용할 수 있는 정렬 기준들.
    namespace SortingKey{
        // 오름차순
        template<typename T>
        const std::function<const bool(const T&, const T&)> ASCENDING=[](const T& lhs, const T& rhs){ return lhs<rhs; };
        // 내림차순
        template<typename T>
        const std::function<const bool(const T&, const T&)> DESCENDING=[](const T& lhs, const T& rhs){ return lhs>rhs; };
    }

    template<typename data_type> class Bag_Iterator;
    template<typename data_type> class Bag_ConstIterator;
    template<typename data_type> class Bag;

    // node의, data에 대한 pointer을 swap하는 것으로 swap을 수행.
    template<typename data_type>
    void swap(Bag_Iterator<data_type>, Bag_Iterator<data_type>);

    //Bag Class의 상수버전 iterator
    template<typename data_type>
    class Bag_ConstIterator{
    private:
        using self_type=Bag_ConstIterator<data_type>;
        using value_type=const data_type;
        using reference_type=const data_type&;
        using pointer_type=const data_type*;
        using iterator_category=std::bidirectional_iterator_tag;
        using node=const Node<data_type>;

    public:
        friend class My::Bag<data_type>;

    private:
        node *pNode;

    public:
        Bag_ConstIterator(node* pNode):pNode(pNode){}
        Bag_ConstIterator(const self_type& that):pNode(that.pNode){}

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

    //Bag Class의 iterator
    template<typename data_type>
    class Bag_Iterator{
    public:
        using self_type=Bag_Iterator<data_type>;
        using value_type=data_type;
        using reference_type=data_type&;
        using pointer_type=data_type*;
        using iterator_category=std::bidirectional_iterator_tag;
        using node=Node<data_type>;
    
    public:
        friend class My::Bag<data_type>;
        template<typename T>
        friend void My::swap(Bag_Iterator<T>, Bag_Iterator<T>);

    private:
        node *pNode;
    
    public:
        Bag_Iterator(node* pNode):pNode(pNode){}
        Bag_Iterator(const self_type& that):pNode(that.pNode){}

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
        inline pointer_type operator->() const{ return pNode->data; }

        // 두 iterator 모두 같은 node를 가리키는지 확인함.
        inline bool operator==(const self_type& rhs) const{ return pNode==rhs.pNode; }
        inline bool operator!=(const self_type& rhs) const{ return !(*this==rhs); }
        
        // 만료된 저장공간를 가리키는지 확인(X)
        // list의 tail 다음 요소를 가리키는 iterator인지 확인(O)
        inline bool is_null(void) const{ return pNode==nullptr; }
    };

    template<typename data_type>
    class Bag{
    private:
        using value_type=data_type;
        using node=Node<data_type>;
        using iterator=Bag_Iterator<data_type>;
        using const_iterator=Bag_ConstIterator<data_type>;
        using self_type=Bag<data_type>;
    
    public:
    
    private:
        node *head=nullptr, *tail=nullptr;
    
    public:
        Bag()=default;

        Bag(const Bag& that):Bag(){ list_copy(head, tail, that.head); }
        inline self_type operator=(const self_type& that){ list_copy(head, tail, that.head); return *this; }
        
        // Bag = {1, 2, 3, 4}와 같이 사용 가능.
        Bag(const std::initializer_list<data_type>& il){
            for(const auto& i: il) insert(i);
        }
        inline self_type operator=(const std::initializer_list<data_type>& il){
            list_clear(head, tail);
            for(const auto& i: il) insert(i);
            return *this;
        }

        // Bag에 들어있는 element의 개수
        inline const size_t amount(void){ return list_length(head); }

        // list tail 뒤에 value를 추가함.
        inline self_type& insert(const value_type&);

        // 앞에서부터 (list_search를 이용)
        // list에 특정 값이 속해있는지 찾고,
        // 있을 경우 그 element를 삭제함.
        inline self_type& erase_one(const value_type& value){ list_head_remove(head, tail, value); return *this; }

        // n번째에 있는 element를 찾음.
        inline iterator count(const int n) const{ return iterator(list_locate(head, n)); }
        inline iterator operator[](const int n) const{ return count(n); }
        
        // this에 that의 내용물을 합침.
        inline self_type operator+=(const self_type& that){ list_append(head, tail, that.head); return *this; }
        // this와 that을 합친 결과물을 return함.
        inline self_type operator+(const self_type& that) const{ return self_type(*this)+=that; }

        // this와 bag이 equivalent한지 검사함.
        inline bool operator!=(const self_type& that) const{ return list_compare(head, that.head); }
        inline bool operator==(const self_type& that) const{ return !((*this)!=that); }

        // 랜덤으로 Bag에서 한 element를 뽑음.
        inline value_type grab(void) const{ return *count(rand()%amount()); }

        // this를 정렬 기준에 맞춰 정렬함. (기본은 오름차순)
        self_type& bubble_sort(const std::function<const bool(const data_type&, const data_type&)>& f=SortingKey::ASCENDING<data_type>);

        // Bag이 내용물이 무엇인지 stdout에 내보냄.
        // std::ostream<<Bag은 Bag.tcc에 구현되어있음.
        inline self_type& show_contents(void){ std::cout<<*this; return *this; }
        
        inline iterator begin(void){ return iterator(head); }
        inline const_iterator cbegin(void) const{ return const_iterator(head); }
        inline iterator end(void){ return iterator(nullptr); }
        inline const_iterator cend(void) const{ return const_iterator(nullptr); }

        ~Bag(){ list_clear(head, tail); }
    };
};

#endif // __INC_BAG_HPP