#include"myTL/Set.h"

#include<iostream>
#include<random>

int main(void){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> dist(0, 32);

    My::Set<int> set;

    for(int i=0; i<50; ++i){
        int temp=dist(generator);
        std::cout<<"insert "<<temp<<" result: "<<std::boolalpha<<set.insert(temp)<<std::endl;
        std::cout<<"After insertion"<<std::endl;
        set.show_contents();
        std::cout<<"---------------"<<'\n'<<std::endl;
    }

    int arr[10]={0, };
    for(int i=0; i<10; ++i){
        int temp=dist(generator);
        arr[i]=temp;
        std::cout<<"count "<<temp<<" result: "<<set.count(temp)<<std::endl;
        std::cout<<"After count() call"<<std::endl;
        set.show_contents();
        std::cout<<"---------------"<<'\n'<<std::endl;
    }
    for(int i=0; i<10; ++i){
        int temp=arr[i];
        std::cout<<"count "<<temp<<" result: "<<set.count(temp)<<std::endl;
        std::cout<<"After count() call"<<std::endl;
        set.show_contents();
        std::cout<<"---------------"<<'\n'<<std::endl;
    }

    for(int i=0; i<50; ++i){
        int temp=dist(generator);
        std::cout<<"erase "<<temp<<" result: "<<std::boolalpha<<set.erase(temp)<<std::endl;
        std::cout<<"After erase() call"<<std::endl;
        set.show_contents();
        std::cout<<"---------------"<<'\n'<<std::endl;
    }

}