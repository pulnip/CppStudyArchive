#include"myTL/Set.h"

#include<iostream>
#include<string>

int main(void){
    My::Set<int> set;

    std::string cmd;
    int arg=0;
    while(true){
        std::cout<<"current state of set"<<std::endl;
        set.show_contents();
        std::cout<<"--------------------"<<std::endl;
        std::cout<<"command: ";
        std::cin>>cmd;

        if(!cmd.compare("quit")) break;
        else{
            std::cin>>arg;
            if(!cmd.compare("insert")){
                std::cout<<"Result: "<<std::boolalpha<<set.insert(arg)<<'\n';
            }
            else if(!cmd.compare("erase")){
                std::cout<<"Result: "<<std::boolalpha<<set.erase(arg)<<'\n';
            }
            else if(!cmd.compare("count")){
                std::cout<<"Result: "<<set.count(arg)<<'\n';
            }
            std::cout<<std::endl;
        }
    }    
}