#include<string>
#include<iostream>

void writeInt(int i){
    if(i==0) return;
    else if(i<0){
        std::cout<<'-'<<std::endl;
        i=-i;
    }
    writeInt(i/10);
    std::cout<<i%10<<std::endl;
}

int main(void){
    writeInt(-1234);
}