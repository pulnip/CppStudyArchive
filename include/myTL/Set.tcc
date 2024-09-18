#ifndef __INC_SET_TCC
#define __INC_SET_TCC

template<typename T, std::size_t M>
My::Set<T, M>::Set(const std::initializer_list<value_type>& il){
    for(auto& item: il){
        insert(item);
    }
}

template<typename T, std::size_t M>
My::Set<T, M>::~Set(){
    delete root;
    root=nullptr;
}

template<typename T, std::size_t M>
My::Set<T, M>::Node::~Node(){
    for(int i=0; i<data_count; ++i) delete data[i];
    for(int i=0; i<child_count; ++i) delete subset[i];
}

template<typename T, std::size_t M>
bool My::Set<T, M>::contains(const value_type& target){
    return root->contains(target);
}
template<typename T, std::size_t M>
int My::Set<T, M>::count(const value_type& target){
    return int(root->contains(target));
}

template<typename T, std::size_t M>
std::size_t My::Set<T, M>::Node::data_search(const value_type& target) const{
    std::size_t min=0, max=data_count;
    std::size_t mid=(min+max)>>1;

    while((min!=max) && (target!=*data[mid])){
        if(target<*data[mid]) max=mid;
        else min=mid+1;

        mid=(min+max)>>1;
    }

    return mid;
}

template<typename T, std::size_t M>
typename My::Set<T, M>::Node*
My::Set<T, M>::Node::search(const value_type& target){
    int i=data_search(target);

    if((data_count!=i) && (target==*data[i])) return this;

    if(subset[i]==nullptr) return nullptr;
    
    return subset[i]->search(target);
}

template<typename T, std::size_t M>
bool My::Set<T, M>::Node::contains(const value_type& target){
    const Node* const node=search(target);

    if(node==nullptr) return false;
    return true;
}

template<typename T, std::size_t M>
bool My::Set<T, M>::insert(const value_type& target){
    Node* const node=root->loose_insert(target);
    if(node==nullptr) return false;

    root=node->fix_excess();
    return true;
}

template<typename T, std::size_t M>
typename My::Set<T, M>::Node*
My::Set<T, M>::Node::loose_insert(const value_type& target){
    const int i=data_search(target);

    // target is found
    if((i!=data_count) && (target==*data[i])) return nullptr;

    // target not found, and subtree exist
    if(subset[i]!=nullptr) return subset[i]->loose_insert(target);

    push(i, new value_type(target));
    return this;
}

template<typename T, std::size_t M>
void My::Set<T, M>::Node::push(const int idx, value_type* target){
    if((data_count==MAX+1)||(target==nullptr)) return;

    for(int j=data_count; j>idx; --j){
        data[j]=data[j-1];
    }
    data[idx]=target;

    ++data_count;
}

template<typename T, std::size_t M>
typename My::Set<T, M>::value_type*
My::Set<T, M>::Node::pop(const int idx){
    if(data_count==0) return nullptr;

    value_type* v=data[idx];
    --data_count;

    for(int j=idx; j<data_count; ++j){
        data[j]=data[j+1];
    }
    data[data_count]=nullptr;

    return v;
}

template<typename T, std::size_t M>
void My::Set<T, M>::Node::pushSet(const int idx, Node* target){
    if((child_count==MAX+2)||(target==nullptr)) return;

    for(int j=data_count; j>idx; --j){
        subset[j]=subset[j-1];
    }
    subset[idx]=target;

    ++child_count;
}

template<typename T, std::size_t M>
typename My::Set<T, M>::Node*
My::Set<T, M>::Node::popSet(const int idx){
    if(child_count==0) return nullptr;

    Node* n=subset[idx];
    --child_count;

    for(int j=idx; j<child_count; ++j){
        subset[j]=subset[j+1];
    }
    subset[child_count]=nullptr;

    return n;
}

template<typename T, std::size_t M>
My::Set<T, M>::Node::Node(Node* left, value_type* mid, Node* right)
:data_count(1), data{mid, nullptr, },
child_count(2), subset{left, right, nullptr}{}

template<typename T, std::size_t M>
typename My::Set<T, M>::Node*
My::Set<T, M>::Node::fix_excess(void){
    if(data_count<=MAX){
        if(nullptr==parent) return this;
    }
    else{
        // fix excess
        const int mid=data_count>>1;

        // split node
        auto new_node=new Node();
        // move data
        for(int i=0; i<mid; ++i){
            new_node->push(i, pop(mid+1));
        }
        //move subset
        for(int i=0; i<mid+1; ++i){
            auto _subset=popSet(mid+1);
            if(_subset!=nullptr)
                _subset->parent=new_node;
            new_node->pushSet(i, _subset);
        }

        auto parent_element=pop(mid);

        if(nullptr!=parent){
            const int i=parent->data_search(*parent_element);
            parent->push(i, parent_element);
            parent->pushSet(i+1, new_node);

            new_node->parent=parent;
        }
        else{
            auto new_parent=new Node(this, parent_element, new_node);

            parent=new_parent;
            
            new_node->parent=new_parent;
        }
    }

    return parent->fix_excess();
}

template<typename T, std::size_t M>
void My::Set<T, M>::show_contents(void){
    root->show_contents();
}

template<typename T, std::size_t M>
void My::Set<T, M>::Node::show_contents(std::size_t depth) const{
    if(subset[data_count]!=nullptr){
        subset[data_count]->show_contents(depth+1);
    }
    for(int i=data_count-1; i>=0; --i){

        for(int j=0; j<depth; ++j){
            std::cout<<'\t';
        }
        if(data[i]!=nullptr){
            std::cout<<*data[i]<<std::endl;
        }
        if(subset[i]!=nullptr){
            subset[i]->show_contents(depth+1);
        }
    }
}

template<typename T, std::size_t M>
bool My::Set<T, M>::erase(const value_type& target){
    Node* const node=root->search(target);
    if(node==nullptr) return false;

    Node* const short_leaf=node->loose_erase(target);

    root=short_leaf->fix_shortage();
    return true;
}

template<typename T, std::size_t M>
typename My::Set<T, M>::Node*
My::Set<T, M>::Node::get_rightmost_node(void){
    Node* node=this;
    // if node is branch(=not leaf)
    while(node->subset[node->child_count-1]!=nullptr){
        // rightmost leaf
        node=node->subset[node->child_count-1];
    }
    return node;
}

template<typename T, std::size_t M>
typename My::Set<T, M>::value_type*
My::Set<T, M>::Node::data_remove_biggest(void){
    return pop(data_count-1);
}

template<typename T, std::size_t M>
typename My::Set<T, M>::Node*
My::Set<T, M>::Node::loose_erase(const value_type& target){
    const int i=data_search(target);
    value_type* v=pop(i);

    // leaf=left branch
    Node* leaf=subset[i];
    if(leaf!=nullptr){
        leaf=leaf->get_rightmost_node();
    }
    else leaf=this;

    if(leaf!=this){
        // swap Target element and Left branch's rightmost value
        value_type* swappable=leaf->data_remove_biggest();
        push(i, swappable);
    }

    delete v;
    return leaf;
}

template<typename T, std::size_t M>
typename My::Set<T, M>::Node*
My::Set<T, M>::Node::fix_shortage(void){
    if(MIN<=data_count){
        if(nullptr==parent) return this;
    }
    else{
        // fix shortage
        if(parent!=nullptr){
            int i=0;
            while(parent->subset[i]!=this) ++i;
            Node* right=parent->subset[i+1];
            Node* left=nullptr;
            if(i>0) left=parent->subset[i-1];

            // can steal element from right sibling
            if((right!=nullptr)&&(right->data_count!=MIN)){
                // steal data
                push(data_count, parent->pop(i));
                parent->push(i, right->pop(0));

                // steal subset
                pushSet(child_count, right->popSet(0));
                if(subset[child_count-1] != nullptr){
                    subset[child_count-1]->parent=this;
                }
            }
            // can steal element from left sibling
            else if((left!=nullptr)&&(left->data_count!=MIN)){
                // steal data
                push(0, parent->pop(i-1));
                parent->push(i-1, left->pop(left->data_count-1));

                // steal subset
                pushSet(0, left->popSet(left->child_count-1));
                if(subset[0] != nullptr){
                    subset[0]->parent=this;
                }
            }
            // cannot steal element.
            else{
                //merge this and right
                if(right!=nullptr){
                    value_type* mid=parent->pop(i);
                    right=parent->popSet(i+1);

                    // move data
                    push(data_count, mid);
                    const int end=right->data_count;
                    for(int i=0; i<end; ++i){
                        push(data_count, right->pop(0));
                    }

                    // move subset
                    const int end2=right->child_count;
                    for(int i=0; i<end2; ++i){
                        pushSet(child_count, right->popSet(0));
                        if(subset[child_count-1] != nullptr){
                            subset[child_count-1]->parent=this;
                        }
                    }

                    delete right;
                }
                // merge left and this
                else{
                    value_type* mid=parent->pop(i-1);
                    Node* self=parent->popSet(i);

                    // move data
                    const int end=data_count;
                    left->push(left->data_count, mid);
                    for(int i=0; i<end; ++i){
                        left->push(left->data_count, pop(0));
                    }

                    // move subset
                    const int end2=child_count;
                    for(int i=0; i<end2; ++i){
                        left->pushSet(left->child_count, popSet(0));
                        if(left->subset[left->child_count-1] != nullptr){
                            left->subset[left->child_count-1]->parent=left;
                        }
                    }

                    Node* node=parent->fix_shortage();
                    delete this;
                    return node;
                }
            }
        }
        else{
            // this is root
            if(data_count==0){
                Node* node=subset[0];
                node->parent=nullptr;
                subset[0]=nullptr;
                delete this;
                return node;
            }
        }
    }
    
    return parent->fix_shortage();
}

template<typename T, std::size_t M>
My::Set<T, M>::Node::Node(const Node& that, Node* parent)
:parent(parent){
    // copy data
    for(int i=0; i<that.data_count; ++i){
        value_type* v=new value_type(that.data[i]);
        push(data_count, v);
    }

    // copy subset
    for(int i=0; i<that.child_count; ++i){
        Node* n=new Node(that.subset[i], this);
        pushSet(child_count, n);
    }
}

template<typename T, std::size_t M>
typename My::Set<T, M>::self_type&
My::Set<T, M>::clear(void){
    delete root;
    root=new Node();
    return *this;
}

template<typename T, std::size_t M>
bool My::Set<T, M>::empty(void){
    if(root->data_count==0) return true;
    return false;
}

template<typename T, std::size_t M>
typename My::Set<T, M>::self_type&
My::Set<T, M>::operator=(const self_type& that){
    delete root;
    root=new Node(that.root, nullptr);
    return *this;
}

template<typename T, std::size_t M>
typename My::Set<T, M>::self_type&
My::Set<T, M>::operator=(const std::initializer_list<T>& that){
    delete root;
    root=new Node();
    for(auto& item: that){
        insert(item);
    }
    return *this;
}

#endif // __INC_SET_TCC