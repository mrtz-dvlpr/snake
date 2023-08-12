#include <conio.h>
#include <iostream>
#include<vector>
#include <thread>

class snakeGame{

    char** place=nullptr;
    int yOfPlace,xOfPlace;

    std::string snake="O";
    std::vector<int> y={8};
    std::vector<int> x={8};

    int selectLocation(int begin , int upperBound);

    void move(char ch);

    void fillScreen(const int &yTarget, const int &xTarget);

    void show(const int & score,std::string name);

    void getYam(int &xYam, int & yYam, int &score);

    bool gameOver();

public:
    snakeGame(int rows,int cols);

    ~snakeGame();

    void play(std::string name);
};

int main()
{
    snakeGame obj(20,10);
    obj.play("morteza");

    return 0;
}


int snakeGame::selectLocation(int lowerBound , int upperBound)
{
    return  lowerBound + rand() % (upperBound - lowerBound + 1);
}

snakeGame::snakeGame(int rows, int cols)
{
    this->yOfPlace=rows;
    this->xOfPlace=cols;

    place=new char*[rows];

    for(int i=0;i<rows;i++){
        place[i]=new char[cols];
    }

    for(int i=1;i<yOfPlace-1;i++){
        place[0][i]='#';
        place[xOfPlace-1][i]='#';
    }

    for(int j=0;j<xOfPlace;j++){
        place[j][0]='#';
        place[j][yOfPlace-1]='#';
    }
}

void snakeGame::move(char ch)
{
    for (int i = x.size() - 1; i > 0; i--) {
        x[i] = x[i - 1];
    }
    for (int i = y.size() - 1; i > 0; i--) {
        y[i] = y[i - 1];
    }

    switch (ch) {
    case 'w':
        x[0]--;
        break;
    case 'd':
        y[0]++;
        break;
    case 's':
        x[0]++;
        break;
    case 'a':
        y[0]--;
        break;
    }
}

void snakeGame::getYam(int &xYam, int &yYam, int &score)
{
    if(x[0]==xYam && y[0]==yYam){
        snake+='o';

        y.push_back(y[y.size()-1]);
        x.push_back(x[x.size()-1]);

        yYam=selectLocation(1 ,yOfPlace-2);
        xYam= selectLocation(1,xOfPlace-2);

        score++;
      }

}

bool snakeGame::gameOver()
{
    if(x[0]==0||x[0]==xOfPlace-1||y[0]==0||y[0]==yOfPlace-1){
        return true;
    }

    for(int i=1;i<y.size();i++){
        if(y[0]==y[i]&&x[0]==x[i])
        {
           return true;
        }
    }

    return false;
}

void snakeGame::play(std::string name)
{
    char ch = 'w';

    int lowerBound = 1;
    int upperBound = yOfPlace-2;
    int yOfYam=selectLocation(lowerBound ,upperBound);

    upperBound = xOfPlace-2;
    int xOfYam= selectLocation(lowerBound ,upperBound);

    int score=0;

    while (true) {

      if (_kbhit())
      {
          ch=_getch();

      }

      move(ch);
      fillScreen(yOfYam,xOfYam);
      show(score,name);

      if(gameOver()){
          system("cls");
          system("color 4");
          std::cout<<"\n\n\t game over\n\n\t score : "<<score<<"\n\n"<<std::endl;
          break;
      }

      getYam(xOfYam,yOfYam,score);

      std::this_thread::sleep_for(std::chrono::microseconds(1000));
    }


}

void snakeGame::fillScreen(const int & yTarget,const int & xTarget)
{
    for(int j=1;j<xOfPlace-1;j++){
      for(int i=1;i<yOfPlace-1;i++){

            place[j][i]=' ';
        }
    }

    for(int i=0;i<snake.size();i++){
        place[x[i]][y[i]]=snake[i];
    }

    place[xTarget][yTarget]='$';
}

void snakeGame::show(const int &score, std::string name)
{
    system("cls");

    for(int j=0;j<xOfPlace;j++){

        for(int i=0;i<yOfPlace;i++){

            std::cout<<place[j][i];
        }
        std::cout<<std::endl;
    }
    std::cout<<"\n\n\t"<<name<<" score :"<<score<<std::endl;
}



snakeGame::~snakeGame()
{
    for(int i=0;i<yOfPlace;i++){
        delete  place[i];
    }
    delete [] place;
}
