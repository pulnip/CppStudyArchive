/**
 * @file Bag.tcc
 * @author 최우혁
 * 
 * @brief member function definitions
 */

#ifndef __INC_BAG_TCC
#define __INC_BAG_TCC

/**
 * @brief 두 node의 data를 swap함.
 * 
 * @tparam T: data의 type
 */
template<typename T>
void My::swap(My::Bag_Iterator<T> lhs, My::Bag_Iterator<T> rhs){
    My::Node<T> *n1=lhs.pNode, *n2=rhs.pNode;

    //n1 또는 n2가 null일 경우는 오류.
    assert((n1!=nullptr)||(n2!=nullptr));

    if(n1!=n2){
        //data를 가리키는 포인터만 서로 바꿔주면 됨.
        T* temp=n1->data;
        n1->data=n2->data;
        n2->data=temp;
    }
}

// Bag_ConstIterator의
// operator+과 operator-의 코드 중복을 제거하기 위한 용도
template<typename T>
My::Bag_ConstIterator<T> My::Bag_ConstIterator<T>::add_sub_aux(const int n) const{
    self_type temp(*this);

    const int abs_n=(n>=0)?n:-n;

    // 다음/이전 요소를 순차적으로 접근함.
    if(n>=0) for(int i=0; i<abs_n; ++i) ++temp;
    else for(int i=0; i<abs_n; ++i) --temp;
        
    return temp;
}
// Bag_Iterator의
// operator+과 operator-의 코드 중복을 제거하기 위한 용도
template<typename T>
My::Bag_Iterator<T> My::Bag_Iterator<T>::add_sub_aux(const int n) const{
    self_type temp(*this);

    const int abs_n=(n>=0)?n:-n;

    // 다음/이전 요소를 순차적으로 접근함.
    if(n>=0) for(int i=0; i<abs_n; ++i) ++temp;
    else for(int i=0; i<abs_n; ++i) --temp;
        
    return temp;
}

/**
 * @brief Bag이 내용물이 무엇인지 stdout에 내보냄.
 * @details 
 * examples.
 * {1, 2, 3}
 * {}
 */
template<typename T>
std::ostream& operator<<(std::ostream& o, const My::Bag<T>& bag){
    o<<'{';        

    for(auto it=bag.cbegin(); it!=bag.cend(); ++it){
        o<<*it<<", ";
    }
        
    //출력할 원소가 하나 이상인지 확인함.
    //하나 이상이라면 뒤에 ", "를 지움.
    if(!bag.cbegin().is_null()) o<<"\b\b";

    return o<<'}';
}

/**
 * @brief list tail 뒤에 value를 추가함.
 * 
 * @param value 추가할 value
 */
template<typename T>
My::Bag<T>& My::Bag<T>::insert(const T& value){
    if(head==nullptr) tail=head=createNode(value, (Node<T>*)nullptr, (Node<T>*)nullptr);
    else {
        list_insert(head, tail, value);
    }
    return *this;
}

/**
 * @brief Bag을 bubble sort를 이용해 정렬함. (기본은 오름차순)
 * 
 * @param f 정렬 기준
 */
template<typename T>
typename My::Bag<T>::self_type&
My::Bag<T>::bubble_sort(const std::function<const bool(const T&, const T&)>& f){
    iterator tail_it(tail);
        
    // i=0, 1, ..., n-2
    for(auto i=begin(); i!=tail_it; ++i){
        // j=1, 2, ..., n-1
        for(auto j=i+1; j!=end(); ++j){
            //정렬 조건 f를 만족하지 않으면 swap
            if(!f(*i, *j)) swap(i, j);
        }
    }

    return *this;
}

#endif // __INC_BAG_TCC