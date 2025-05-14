#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <random>
using namespace std;
unsigned long int checker_target=0x123456789abcdef0,checker=15;//1111
unsigned long int nextLineChecker=0x0001000100010001;
int up=65520;int down=4095;int L=61166;int R=30583;int count=0;
/*
 0 0 0 0
 1 1 1 1
 1 1 1 1
 1 1 1 1
*/
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
    return KEY_UNKNOWN;
}
int main() {
    enable_raw_mode();
    int position_0=14;
    unsigned long int p=0x0fedcba987654321;
    p=0x2376b458acf091de;
    p=randomPlate();
    position_0=getp0(p);
    while (p!=checker_target) {
        printPlate(p);
        Key key = get_key();
        system("clear");
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