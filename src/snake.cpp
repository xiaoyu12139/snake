#include "snake.h"
#ifdef _WIN32
#include <conio.h>
#else
#include "conio_linux.h"
#endif
#include "tools.h"
#include <iostream>

#ifdef __linux__

#endif

void Snake::InitSnake()//��ʼ����
{
    for (auto& point : snake)
    {
        point.PrintCircular();
    }
}

void Snake::Move()//������
{
    switch (direction)
    {
    case Direction::UP:
        snake.emplace_back(Point(snake.back().GetX(), snake.back().GetY() - 1 ));
        break;
    case Direction::DOWN:
        snake.emplace_back(Point(snake.back().GetX(), snake.back().GetY() + 1 ));
        break;
    case Direction::LEFT:
        snake.emplace_back(Point(snake.back().GetX() - 1, snake.back().GetY() ));
        break;
    case Direction::RIGHT:
        snake.emplace_back(Point(snake.back().GetX() + 1, snake.back().GetY() ));
        break;
    default:
        break;
    }
    SetColor(14);
    snake.back().PrintCircular();
    
}

void Snake::NormalMove()//�������ƶ���ͷ������β����
{
    Move();
    snake.front().Clear();
    snake.pop_front();
}

bool Snake::OverEdge()//�����߽�
{
    return snake.back().GetX() < 30 &&
           snake.back().GetY() < 30 &&
           snake.back().GetX() > 1  &&
           snake.back().GetY() > 1;
}

bool Snake::HitItself()//ײ������
{
    std::deque<Point>::size_type cnt = 1;
    Point *head = new Point(snake.back().GetX(), snake.back().GetY());//���ͷ������
    for (auto& point : snake) //���������������ͷ����ͬ�����겻�����߳�������ζ����ͷ��ײ������
    {
        if ( !(point == *head) )
            ++cnt;
        else
            break;
    }
    delete head;
    if(cnt == snake.size())
        return true;
    else
        return false;
}

bool Snake::ChangeDirection()//�ı䷽��
{
    char ch;
    if (kbhit())//kbhit��������ֵΪ��������ע��
    {
        // SetColor(3);
        // SetCursorPosition(snake.at(0).GetX(),snake.at(0).GetY() - 1);
        // std::cout << "  ";
        ch = getKeyCode();
        switch (ch)
        {
            case KEY_UP:
                if (direction != Direction::DOWN)//��������뵱ǰ�˶������෴����Ч
                    direction = Direction::UP;
                    
                break;
            case KEY_DOWN:
                if (direction != Direction::UP)
                    direction = Direction::DOWN;
                break;
            case KEY_LEFT:
                if (direction != Direction::RIGHT)
                    direction = Direction::LEFT;
                break;
            case KEY_RIGHT:
                if (direction != Direction::LEFT)
                    direction = Direction::RIGHT;
                break;
            case KEY_ESC://ESC
                return false;

            default:
                return true;

        }
    }
    return true;
}

bool Snake::GetFood(const Food& cfood)
{
    if (snake.back().GetX() == cfood.x && snake.back().GetY() == cfood.y)
        return true;
    else
        return false;
}

bool Snake::GetBigFood(Food& cfood)
{
    if (snake.back().GetX() == cfood.big_x && snake.back().GetY() == cfood.big_y)
    {
        cfood.big_flag = false;
        cfood.big_x = 0;
        cfood.big_y = 0;
        SetCursorPosition(1, 0);
        std::cout << "                                                            " ;
        return true;
    }
    else
        return false;
}
