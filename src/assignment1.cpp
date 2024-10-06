#include"myTL/Bag.h"

#include<iostream>

int main(void){
    My::Bag<int> bag1={3, 1, 5}, bag2={1, 2, 3};
    std::cout<<"bag1: ";
    bag1.show_contents();
    std::cout<<"\nbag2: ";
    bag2.show_contents();
    std::cout<<"\e[31m *** bag2 final modifying\e[0m\n"<<std::endl;

    std::cout<<"insert 42 28 35 28 at bag1: ";
    bag1.insert(42).insert(28).insert(35).insert(28).show_contents();
    std::cout<<"\e[31m *** bag1 final modifying\e[0m\n";
    std::cout<<"bag1 amount: "<<bag1.amount()<<'\n'<<std::endl;

    std::cout<<"bag3=bag1+bag2: ";
    auto bag3=bag1+bag2;
    bag3.show_contents();
    std::cout<<'\n'<<std::endl;

    std::cout<<"bag4(bag3): ";
    My::Bag<int> bag4(bag3);
    bag4.show_contents();
    std::cout<<"\n"<<std::endl;

    std::cout<<"sort bag3: ";
    bag3.bubble_sort().show_contents();
    std::cout<<'\n'<<std::endl;

    std::cout<<"erase_one 28 at bag4: ";
    bag4.erase_one(28).show_contents();
    std::cout<<'\n'<<std::endl;

    std::cout<<"bag4+=bag2: ";
    (bag4+=bag2).show_contents();
    std::cout<<'\n'<<std::endl;

    std::cout<<"bag4=bag1: ";
    (bag4=bag1).show_contents();
    std::cout<<"\e[31m *** bag4 final modifying\e[0m\n"<<std::endl;

    std::cout<<"bag1==bag4: "<<std::boolalpha<<(bag1==bag4)<<std::endl;
    std::cout<<"bag1!=bag4: "<<std::boolalpha<<(bag1!=bag4)<<std::endl;

    std::cout<<"bag1==bag2: "<<std::boolalpha<<(bag1==bag2)<<std::endl;
    std::cout<<"bag1!=bag2: "<<std::boolalpha<<(bag1!=bag2)<<'\n'<<std::endl;

    std::cout<<"bag5(bag4): ";
    auto bag5(bag4);
    bag5.show_contents();
    std::cout<<'\n'<<std::endl;

    std::cout<<"bag1+bag2: ";
    (bag1+bag2).show_contents();

    return 0;
}