#include <SFML/Graphics.hpp>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <random>
#include <unordered_map>
#include <chrono>
#include <deque>
#include <thread>
#include <cmath>
#include <mutex>
/*
溺智小游戏
按Q显示AI解答的正确最优步骤（不唯一，仅展示一种）
按↑↓←→控制空白格移动
按R回到起点
按B回到上一步（可以是回到起点之后又飞回起飞的点）
------以下部分还未完成
初始有一个“关羽”，你是“曹操”（空白格），你初始有5点生命，每次靠近关羽（上下左右格）会扣除1点，与“关羽”重合会扣除2点
关羽会向你靠近（行动优先级为上下左右），但是在靠近一点你就要被关羽融化，同时你又要走出华容道（还原棋盘），所以你···获得了超能力，时间回溯法（只能回溯自己的）
*/
std::mutex data_mutex;
using namespace std;
unsigned long int checker_target=0x123456789abcdef0,checker=15;
unsigned long int nextLineChecker=0x0001000100010001;
unsigned long int wayPoint;
vector <unsigned long int>recordPlate;
int be[16],ba[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
int newd=1;int mindistance=45;
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
void loadbe (unsigned long int p){
    int count=1;
    for(int i=60;i>=0;i-=4){
        int t=15&(p>>i);
        be[t]=count;
        count++;
    }
}
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
    while(count<45&&count1<100){
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
void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &original_termios);
    struct termios raw = original_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios); // 确保变量名一致
}
bool Check(unsigned long int p,int b[16]){
    int summary=0;
    int n=1;
    for(int i=60;i>=0;i-=4){
        int t=15&(p>>i);
        t=b[t];
        if(t!=0){
            summary+=abs(t-n)%4+abs((t-1)/4-(n-1)/4);
        }
        n++;
    }
    return (summary+newd)<mindistance;
}
void direction_go(unsigned long int node,int s,int p_0){
    unsigned long int np=getnp(node,p_0,s);
    auto it=plates.find(np);
    if(it==plates.end()){
        if(Check(np,ba)){
            plates.emplace(np,newd);
            b1.emplace(np,p_0-(s/4));
            plates_record.emplace(np,-s);
        }
    }
}
void explore(unsigned long int node,int p_0){
    if((up>>p_0)&1){direction_go(node,16,p_0);}
    if((down>>p_0)&1){direction_go(node,-16,p_0);}
    if((R>>p_0)&1){direction_go(node,-4,p_0);}
    if((L>>p_0)&1){direction_go(node,4,p_0);}
}
void checkMin(unsigned long int node){
    auto it=plates.find(node);
    if(it!=plates.end()){mindistance=mindistance<(it->second+newd)?mindistance:(it->second+newd);wayPoint=node;}
}
void direction_go2(unsigned long int node,int s,int p_0){
    unsigned long int np=getnp(node,p_0,s);
    auto it=check_depth.find(np);
    if(it==check_depth.end()){
        if(Check(np,be)){
            check_depth.emplace(np,newd);checkMin(np);b2.emplace(np,p_0-(s/4));check_depth_record.emplace(np,-s);
        }
    }
}
void explore2(unsigned long int node,int p_0){
    
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
    printf("-------\n");
    printPlate(wayPoint);
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
    loadbe(begin);
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
void clears(){
    plates_record.clear(),check_depth_record.clear(),check_depth.clear(),plates.clear(),b1.clear(),b2.clear(),br1.clear(),br2.clear();
}
class PuzzleGame {

private:
    bool aiRunning = false;    // AI是否正在运行
    bool aiFinished = false;   // AI是否完成计算
    size_t currentStep = 0;    // 当前演示步骤
    bool completed = false; // 添加完成状态
    sf::Clock completionClock; // 完成动画计时器    
    std::mutex aiMutex; // 添加互斥锁
    bool aiReady = false; // 添加AI就绪标志
    sf::Texture backgroundTexture;
    sf::RenderWindow window;
    sf::Texture originalTexture;
    sf::Sprite numberSprites[16];
    sf::Image backgroundImage;
    sf::Sprite backgroundSprite;
    unsigned long int currentPlate;
    std::deque<unsigned long int> aiSteps;
    bool showSolution = false;
    sf::Texture victoryTexture;
    sf::Sprite victorySprite;
    void loadImageResources() {
        // 加载自定义图片
        if (!originalTexture.loadFromFile("图.png")) {
            // 添加默认图形生成逻辑
            sf::Image fallback;
            fallback.create(512, 512, sf::Color::Blue);
            originalTexture.loadFromImage(fallback);
        }
        // 创建低亮度背景
        backgroundImage = originalTexture.copyToImage();
        for (unsigned int y = 0; y < backgroundImage.getSize().y; ++y) {
            for (unsigned int x = 0; x < backgroundImage.getSize().x; ++x) {
                sf::Color color = backgroundImage.getPixel(x, y);
                color.r *= 0.3; color.g *= 0.3; color.b *= 0.3;
                backgroundImage.setPixel(x, y, color);
            }
        }
    
        // 修复步骤：加载到持久化纹理
        backgroundTexture.loadFromImage(backgroundImage); // 使用成员变量
        backgroundSprite.setTexture(backgroundTexture);   // 设置有效纹理
    
        // 切割原始图片为16块
        sf::Vector2u texSize = originalTexture.getSize();
        for (int i = 0; i < 16; ++i) {
            numberSprites[i].setTexture(originalTexture);
            numberSprites[i].setTextureRect(sf::IntRect(
                (i % 4) * texSize.x / 4,
                (i / 4) * texSize.y / 4,
                texSize.x / 4,
                texSize.y / 4
            ));
        }
        if (!victoryTexture.loadFromFile("图.png")) { // 确保图片路径正确
            // 生成备用胜利画面
            sf::Image fallback;
            fallback.create(512, 512, sf::Color::Green);
            victoryTexture.loadFromImage(fallback);
        }
        victorySprite.setTexture(victoryTexture);
    }
    void drawVictory() {
        sf::Vector2u winSize = window.getSize();
        sf::Vector2u texSize = victoryTexture.getSize();
        float scale = 0.5f;
    
        // 正确计算左半屏居中位置
        float leftHalfWidth = winSize.x / 2.0f;
        float imageWidth = texSize.x * scale;
        float imageHeight = texSize.y * scale;
    
        victorySprite.setScale(scale, scale);
        victorySprite.setPosition(
            (leftHalfWidth - imageWidth) / 2.0f, // 左半屏水平居中
            (winSize.y - imageHeight) / 2.0f      // 垂直居中
        );
        window.draw(victorySprite);
    }
    void drawBackground() {
        sf::Sprite leftBg = backgroundSprite;
        float n=0.5;
        leftBg.setPosition(0, 0);
        leftBg.setScale(n,n); // 正确缩放
        window.draw(leftBg);
        sf::Sprite rightBg = backgroundSprite;
        rightBg.setPosition(512, 0);
        rightBg.setScale(n,n);
        window.draw(rightBg);
    }
    void drawPuzzle(unsigned long int plate, float offsetX=0) {
        const float screenWidth = window.getSize().x;
        const float blockWidth = screenWidth / 8.0f; // 正确分割为4x4网格
        // 位置计算公式
        for (int i=0; i<16; ++i) {
            // 关键修复：从 plate 中提取当前块的值
            int val = (plate >> (60 - 4*i)) & 0xF; // 提取第i个4位值
            if (val == 0) continue; // 0代表空白块，跳过绘制
            const int col = i % 4;
            const int row = i / 4;
            // 确保数组索引有效（val范围：1~15）
            numberSprites[val-1].setPosition(
                offsetX + col * blockWidth + 2,
                row * blockWidth + 2
            );
            numberSprites[val-1].setScale(
                (blockWidth-4)/numberSprites[val-1].getLocalBounds().width,
                (blockWidth-4)/numberSprites[val-1].getLocalBounds().height
            );
            window.draw(numberSprites[val-1]);
        }
    }

public:
    PuzzleGame() : window(sf::VideoMode(1024, 512), "数字华容道") {
        loadImageResources();
        currentPlate = randomPlate();

    }
    void checkCompletion() {
        bool currentCompleted = (currentPlate == checker_target);
        if (currentCompleted != completed) {
            completed = currentCompleted;
            if (completed) completionClock.restart();
        }
    }
    void drawCompletionEffect() {
        if (completed) {
            // 创建绿色透明覆盖层
            sf::RectangleShape overlay(sf::Vector2f(window.getSize().x/2, window.getSize().y));
            overlay.setPosition(0, 0);
            
            // 添加脉冲动画
            float alpha = 128 + 127 * sin(completionClock.getElapsedTime().asSeconds() * 3);
            overlay.setFillColor(sf::Color(0, 255, 0, static_cast<sf::Uint8>(alpha)));
            window.draw(overlay);
        }
    }
    void startAISolution() {
        mindistance=45;
        std::lock_guard<std::mutex> lock(aiMutex);
        if (!aiRunning) {
            aiRunning = true;
            aiFinished = false;
            currentStep = 0;
            plates.clear();
            check_depth.clear();
            aiSteps.clear(); // 清空旧路径
            std::thread([this]{                
                getBestWay(currentPlate);
                std::lock_guard<std::mutex> lock(aiMutex);
                aiSteps = reconstructPath(wayPoint, plates_record, check_depth_record); // 生成新路径
                // printf("\n%d\n",aiSteps.size());
                aiFinished = true;
            }).detach();
        }
    }
    void resetAISolution() {
        std::lock_guard<std::mutex> lock(aiMutex);
        aiRunning = false;
        aiFinished = false;
        currentStep = 0;
    }
    void drawAITextInfo() {
        sf::Font font;
        font.loadFromFile("Arial");
        if (!font.loadFromFile("Arial")) { // 替换为实际路径
            std::cerr << "无法加载 Arial 字体，跳过文本绘制\n";
            return;
        }
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        
        if (aiRunning && !aiFinished) {
            text.setString("Calculating...");
            text.setPosition(550, 480);
            window.draw(text);
        } else if (!aiSteps.empty()) {
            text.setString("Steps: " + std::to_string(currentStep) + "/" + std::to_string(aiSteps.size()));
            text.setPosition(550, 450);
            window.draw(text);
        }
    }
    void run() {
        int printed=0;
        while (window.isOpen()) {
        if (showSolution) {
            std::lock_guard<std::mutex> lock(aiMutex);
            if (aiFinished) {
                if (currentStep < aiSteps.size()) {
                    drawPuzzle(aiSteps[currentStep], 512);
                    currentStep++;
                    // 添加步骤文本提示
                    sf::Text text;
                    text.setString("Step: " + std::to_string(currentStep) + "/" + std::to_string(aiSteps.size()));
                    text.setPosition(550, 450);
                    window.draw(text);
                } else {
                    aiRunning = false; // 运行结束
                    // 添加完成标识
                    sf::Text text;
                    text.setString("Solution Finished");
                    text.setPosition(550, 480);
                    window.draw(text);
                }
            } else if (aiRunning) {
                // 计算中的加载提示
                sf::Text text;
                text.setString("Calculating...");
                text.setPosition(550, 480);
                window.draw(text);
            }
        }
            checkCompletion();
            drawCompletionEffect();
            sf::Event event;
            int cnt=0;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                cnt++;
                // 处理键盘输入
                if (event.type == sf::Event::KeyPressed) {
                    int position_0 = getp0(currentPlate);
                    switch (event.key.code) {
                        case sf::Keyboard::Up:
                            if(up & (1<<position_0)){ 
                                recordPlate.push_back(currentPlate);
                                currentPlate = getnp(currentPlate, position_0, 16);completed = false;};
                            break;
                        case sf::Keyboard::Down:
                            if(down&(1<<position_0)){
                                recordPlate.push_back(currentPlate);
                                currentPlate=getnp(currentPlate,position_0,-16);completed = false;}
                            break;
                        case sf::Keyboard::Left:
                            if(L&(1<<position_0)){
                                recordPlate.push_back(currentPlate);
                                currentPlate=getnp(currentPlate,position_0,4);completed = false;}
                            break;
                        case sf::Keyboard::Right:
                            if(R&(1<<position_0)){
                                recordPlate.push_back(currentPlate);
                                currentPlate=getnp(currentPlate,position_0,-4);completed = false;}
                            break;
                        case sf::Keyboard::Q:
                            if (!aiRunning) {  // 如果AI未运行
                                currentStep=0;
                                clears();
                                printf("go");
                                startAISolution();
                                showSolution = true; 
                            } else {           // 如果AI正在运行
                                resetAISolution();
                                showSolution = false;
                            }
                            break;
                        case sf::Keyboard::R:
                            if(currentPlate!=recordPlate[0]){
                            recordPlate.push_back(currentPlate);
                            currentPlate=recordPlate[0];
                            }
                            break;
                        case sf::Keyboard::B:
                            if(recordPlate.size()!=0){
                                currentPlate=recordPlate.back();
                                recordPlate.pop_back();
                            }
                        break;
                    }
                }
                
            }
            checkCompletion();
            window.clear();
            // 绘制玩家界面（左半屏）
            drawBackground();
            drawPuzzle(currentPlate, 0);            
            // 绘制AI解答界面（右半屏）
            if (showSolution) {
                std::lock_guard<std::mutex> lock(aiMutex);
                if (aiFinished && currentStep < aiSteps.size()) {
                    drawPuzzle(aiSteps[currentStep], 512);
                }
            }
            if(completed&&printed<6){
                drawVictory();
                drawCompletionEffect();
                printf("\nWIIIIIIIIIIIIIIIIN!\n");
                printed++;
            }
            if(completed&&printed==6){
                drawVictory();
            }
            window.display();
            sf::sleep(sf::milliseconds(500));
        }
    }
};

int main() {
    PuzzleGame game;
    game.run();
    return 0;
}