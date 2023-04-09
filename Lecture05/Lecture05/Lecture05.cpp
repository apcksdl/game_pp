//#define DEBUG
#include <iostream>
#include <conio.h>
#include <Windows.h>


const int STAGE_WIDTH = 15; // Width of the game stage
const int STAGE_HEIGHT = 10;

// game_state == 0 일때
int print_title_screen()
{
    std::cout << "******************************************" << std::endl;
    std::cout << "*                                        *" << std::endl;
    std::cout << "*                                        *" << std::endl;
    std::cout << "*              지렁이 게임               *" << std::endl;
    std::cout << "*             (Snake  Bite)              *" << std::endl;

#ifdef DEBUG
    std::cout << "*            - 디버그 모드 -             *" << std::endl;
#else
    std::cout << "*                                        *" << std::endl;
#endif  
    std::cout << "*                                        *" << std::endl;
    std::cout << "*                                        *" << std::endl;
    std::cout << "*                                        *" << std::endl;
    std::cout << "*                                        *" << std::endl;
    std::cout << "*                                        *" << std::endl;
    std::cout << "*                                        *" << std::endl;
    std::cout << "*                                        *" << std::endl;
    std::cout << "*   1. 게임 시작                         *" << std::endl;
    std::cout << "*   2. 게임 설명                         *" << std::endl;
    std::cout << "*   3. 게임 랭킹 보기                    *" << std::endl;
    std::cout << "*   4. 게임 종료 (esc)                   *" << std::endl;
    std::cout << "******************************************" << std::endl;

    return 0;
}

void gotoxy(int x, int y) {
    //x, y 좌표 설정
    COORD pos = { x,y };
    //커서 이동
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int print_game_screen(int stage_width, int stage_height)
{
    gotoxy(12, 6);
    std::cout << "+";
    for (int i = 0; i < STAGE_WIDTH; i++) {
        std::cout << "-";
    }
    std::cout << "+" << std::endl;
    gotoxy(12, 7);
    for (int i = 0; i < STAGE_HEIGHT; i++) {
        
        std::cout << "|";
        for (int j = 0; j < STAGE_WIDTH; j++) {
            std::cout << " ";
        }
        std::cout << "|" << std::endl;
        gotoxy(12, 8);

        std::cout << "|";
        for (int j = 0; j < STAGE_WIDTH; j++) {
            std::cout << " ";
        }
        std::cout << "|" << std::endl;
        gotoxy(12, 9);



    }

    gotoxy(12, 10);
    // Print the bottom border
    std::cout << "+";
    for (int i = 0; i < STAGE_WIDTH; i++) {
        std::cout << "-";
    }
    std::cout << "+" << std::endl;
    

    return 0;
}

// game_state == 2 일때
int print_introduction_screen()
{
    std::cout << "******************************************" << std::endl;
    std::cout << "타이틀화면으로 돌아갈까요? (Y/N)" << std::endl;
    return 0;
}

int main()
{

    int game_state = 0;
    int is_game_running = 1;

    while (is_game_running)
    {
        char key_input = '0';
        switch (game_state)
        {
        case 0:
            print_title_screen();
            key_input = _getch();
            switch (key_input)
            {
            case '1':
                game_state = 1;
                break;
            case '2':
                game_state = 2;
                break;
            case '3':
                break;
            case '4':
                is_game_running = 0;
                break;
            case 27:
                is_game_running = 0;
                break;
            default:
                break;
            }
            break;
        case 1:
            print_game_screen(10, 10);
            key_input = _getch();
        case 2:
            print_introduction_screen();
            key_input = _getch();
            switch (key_input)
            {
            case 'y':
                game_state = 0;
                break;
            case 'n':
                break;
            default:
                break;
            }
            break;

        default:
            break;
        }


    }

    return 0;
}