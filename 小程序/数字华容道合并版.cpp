#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <random>
#include<stdio.h>
#include<stdlib.h>
#include<unordered_map>
#include<chrono>
#include<deque>
using namespace std;
unsigned long int checker_target=0x123456789abcdef0,checker=15;
unsigned long int nextLineChecker=0x0001000100010001;
int newd=1;unsigned long int wayPoint;int mindistance=45;
int MAX=1<<30;
unordered_map<unsigned long int,int> plates;
unordered_map<unsigned long int,int> plates_record;
unordered_map<unsigned long int,int> check_depth;
unordered_map<unsigned long int,int> check_depth_record;
unordered_map<unsigned long int,int>br1;
unordered_map<unsigned long int,int>b1;
unordered_map<unsigned long int,int>br2;
unordered_map<unsigned long int,int>b2;
int up=65520;int down=4095;int L=61166;int R=30583;int count=0;
struct termios original_termios;
int getRandom0To3() {
    static std::mt19937 engine(std::random_device{}());
    static std::uniform_int_distribution<int> dist(0, 3);
    return dist(engine);
}
void printPlate(unsigned long int p){
    int x=64;
    while (x){
        x-=4;
        printf("%ld\t",15&(p>>x));
        if(nextLineChecker&(1<<x)){printf("\n\n");}
    } 
}
int getp0(unsigned long int p){
    int i=0;
    while (checker&p){
        p>>=4;
        i++;
    }
    return (15-i);
}
unsigned long int getnp(unsigned long int node,int p_0,int s){
    unsigned long int move=(checker<<(60-4*(p_0)+s))&node;
    count++;
    if (s>0){ 
        return (move^node)|(move>>s);
    }
    else if (s<0){
        return (move^node)|(move<<(-s));
    }
}
unsigned long int randomPlate(){
    int movement[]={16,-16,4,-4};
    int position_0=15;
    unsigned long int p=0x123456789abcdef0;
    int count = 0,count1=0;
    int old=0;
    int watcher[]={13,14,7,11};//1101,1110,0111,1011
    while(count<50&&count1<100){
        int random=getRandom0To3();
        if(watcher[random]&(1<<old)){
            switch (random) {
                case 0:
                    if(up&(1<<position_0)){p=getnp(p,position_0,16);position_0-=4;count++;}
                    break;
                case 1:
                    if(down&(1<<position_0)){p=getnp(p,position_0,-16);position_0+=4;count++;}
                    break;
                case 2:
                    if(L&(1<<position_0)){p=getnp(p,position_0,4);position_0--;count++;}
                    break;
                case 3:
                    if(R&(1<<position_0)){p=getnp(p,position_0,-4);position_0++;count++;}
                    break;
            }
            count1++;
        }
        old=random;
    }
    return p;
}
enum Key {
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_Q,
    KEY_UNKNOWN
};
void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &original_termios);
    struct termios raw = original_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios); // 确保变量名一致
}
Key get_key() {
    char c;
    if (read(STDIN_FILENO, &c, 1) != 1) return KEY_UNKNOWN;
    if (c == '\x1B') { // 检测到ESC字符
        char seq[2];
        if (read(STDIN_FILENO, &seq[0], 1) != 1) return KEY_UNKNOWN;
        if (read(STDIN_FILENO, &seq[1], 1) != 1) return KEY_UNKNOWN;

        if (seq[0] == '[') {
            switch (seq[1]) {
                case 'A': return KEY_UP;
                case 'B': return KEY_DOWN;
                case 'D': return KEY_LEFT;
                case 'C': return KEY_RIGHT;
            }
        }
    }
    if (c == 'Q' || c == 'q') {
        return KEY_Q; 
    }
    return KEY_UNKNOWN;
}

void direction_go(unsigned long int node,int s,int p_0){
    unsigned long int np=getnp(node,p_0,s);
    auto it=plates.find(np);
    if(it==plates.end()){plates.emplace(np,newd);plates_record.emplace(np,-s);b1.emplace(np,p_0-(s/4));}
}
void explore(unsigned long int node,int p_0){
    if((up>>p_0)&1){direction_go(node,16,p_0);}
    if((down>>p_0)&1){direction_go(node,-16,p_0);}
    if((R>>p_0)&1){direction_go(node,-4,p_0);}
    if((L>>p_0)&1){direction_go(node,4,p_0);}
}
void direction_go2(unsigned long int node,int s,int p_0){
    unsigned long int np=getnp(node,p_0,s);
    auto it=check_depth.find(np);
    if(it==check_depth.end()){check_depth.emplace(np,newd);check_depth_record.emplace(np,-s);b2.emplace(np,p_0-(s/4));}
}
void explore2(unsigned long int node,int p_0){
    auto it=plates.find(node);
    if(it!=plates.end()&&mindistance>(it->second+newd-1)){mindistance=(it->second-1+newd);wayPoint=node;}
    if((up>>p_0)&1){direction_go2(node,16,p_0);}
    if((down>>p_0)&1){direction_go2(node,-16,p_0);}
    if((R>>p_0)&1){direction_go2(node,-4,p_0);}
    if((L>>p_0)&1){direction_go2(node,4,p_0);}
}
std::deque<unsigned long int> reconstructPath(
    unsigned long int wayPoint,
    const std::unordered_map<unsigned long int, int>& forward_parent,
    const std::unordered_map<unsigned long int, int>& backward_parent
) {
    std::deque<unsigned long int> path;
    path.push_back(wayPoint);
    unsigned long int current = wayPoint;
    while (forward_parent.find(current) != forward_parent.end()) {
        int move = forward_parent.at(current);
        current = getnp(current,getp0(current), move);
        path.push_front(current);
    }
    current = wayPoint;
    while (backward_parent.find(current) != backward_parent.end()) {
        int move = backward_parent.at(current);
        current = getnp(current, getp0(current),move);
        path.push_back(current);
    }
    return path;
}
void getBestWay(unsigned long int begin){
    int position_0=getp0(begin);
    if (begin==checker_target){printf("0");return;}
    plates.emplace(begin, 0);
    br1.emplace(begin,position_0);
    check_depth.emplace(checker_target,0);
    br2.emplace(checker_target,15);
    while (newd<=23){
        for(auto it = br1.begin();it!=br1.end();++it){
            explore(it->first,it->second);
        }
        br1=move(b1);b1.clear();
        for(auto it = br2.begin();it!=br2.end();++it){
            explore2(it->first,it->second);
        }
        br2=move(b2);b2.clear();
        if(mindistance<45){printf("最小步骤是：%d，接下来给出最小步骤解\n",mindistance);break;}
        newd++;
    }
auto path = reconstructPath(wayPoint, plates_record, check_depth_record);
for (auto state : path) {
    printPlate(state);
    std::cout << "↓\n";
}
printf("你的人机队友已完成步骤为 %d 的复原，现在该你玩了",mindistance);
}
int main() {
    enable_raw_mode();
    int position_0=14;
    unsigned long int p=0x0fedcba987654321;
    p=0x2376b458acf091de;
    p=randomPlate();
    position_0=getp0(p);
    int count=0;
    while (p!=checker_target) {
        printPlate(p);
        printf("\n当前已用步骤：%d ",count);
        if(count>=0){printf("当前步骤达到100，如果需要，按Q转人机自动解答");}
        Key key = get_key();
        system("clear");
        if (key==4){
            getBestWay(p);
            break;
        }
        switch (key) {
            case 0:
                std::cout << "↑\n";
                if(up&(1<<position_0)){p=getnp(p,position_0,16);position_0-=4;}
                break;
            case 1:
                std::cout << "↓\n";
                if(down&(1<<position_0)){p=getnp(p,position_0,-16);position_0+=4;}
                break;
            case 2:
                std::cout << "←\n";
                if(L&(1<<position_0)){p=getnp(p,position_0,4);position_0--;}
                break;
            case 3:
                std::cout << "→\n";
                if(R&(1<<position_0)){p=getnp(p,position_0,-4);position_0++;}
                break;
            case KEY_UNKNOWN:
                // 处理其他输入或退出
                break;
        }
    }
    printf("共用步骤 %d 步",count);
    disable_raw_mode();
    return 0;
}