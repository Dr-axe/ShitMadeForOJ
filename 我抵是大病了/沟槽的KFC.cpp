#include<iostream>
#include<random>
int main(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(4, 50);
    for (int i = 0; i < dis(gen); ++i) {
        int x=dis(gen);
        for(int j=x;j<x*2;j++){
            if(!(j%4)){std::cout<<"Crazy ";continue;}
            else if(!(j%3)){std::cout<<"Tursday ";continue;}
            else if(!(j%2)){std::cout<<"V me 50";continue;}
            std::cout<<"KFC ";
        }
        std::cout<<"\ny5Cra Vezm u0Thsdayr\n";
    }
    return 0;
}