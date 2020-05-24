#define _USE_MATH_DEFINES
#include <cmath>
#include "World2.hpp"

void World2::setup()
{
}

void World2::loop()
{
    // for position lost area
    if (PositionX != 0 || PositionY != 0)
    {
        pos_x = PositionX;
        pos_y = PositionY;
    }
    else
    {
        // in position lost area
        PositionX = -1;
    }

    if (SuperObj_Num != 0)
    {
        log_super_x = SuperObj_X;
        log_super_y = SuperObj_Y;
    }
    if (!(EitherColorJudge(object_box))) {
      LED_1 = 0;
    }
    if (SuperDuration > 0)
    {
        SuperDuration--;
    }
    else if (EitherColorJudge(blue_trap)) {
      loaded_objects[RED_LOADED_ID] = 0;
      loaded_objects[CYAN_LOADED_ID] = 0;
      loaded_objects[BLACK_LOADED_ID] = 0;
      loaded_objects[SUPER_LOADED_ID] = 0;
      LoadedObjects = 0;
    }
    else if (EitherColorJudge(red_obj) && loaded_objects[RED_LOADED_ID] < 2 && LoadedObjects < 6)
    {
        action = FIND_OBJ;
        SuperDuration = kFindObjDuration;
        loaded_objects[RED_LOADED_ID]++;
    }
    else if (EitherColorJudge(cyan_obj) && loaded_objects[CYAN_LOADED_ID] < 2 && LoadedObjects < 6)
    {
        action = FIND_OBJ;
        SuperDuration = kFindObjDuration;
        loaded_objects[CYAN_LOADED_ID]++;
    }
    else if (EitherColorJudge(black_obj) && loaded_objects[BLACK_LOADED_ID] < 2 && LoadedObjects < 6)
    {
        action = FIND_OBJ;
        SuperDuration = kFindObjDuration;
        loaded_objects[BLACK_LOADED_ID]++;
    }
    else if (EitherColorJudge(sp_obj) && LoadedObjects < 6) // get super obj
    {
        GoToSuperObj(1);
        action = FIND_OBJ;
        SuperDuration = kFindObjDuration;
        loaded_objects[SUPER_LOADED_ID]++;
    }
    else if (EitherColorJudge(object_box)&&LoadedObjects>=4)
    {
        if (BothColorJudge(object_box))
        {
            action = DEPOSIT_OBJ;
            SuperDuration = 50;
        }
        else if (ColorJudgeLeft(object_box))
        {
            motor(3, 0);
        }
        else
        {
            motor(0, 3);
        }
    }
    else if (EitherColorJudge(trap_line)&&LoadedObjects!=0)
    {
      if (BothColorJudge(trap_line))
      {
        motor(-5,-5);
      }
      else if (ColorJudgeLeft(trap_line))
      {
        motor(5,-5);
      }
      else
      {
        motor(-5,5);
      }
    }
    else if (Duration > 0)
    {
        Duration--;
    }
    else if (log_super_x != -1)
    {
      GoToSuperObj(0);
    }
    else
    {
        if(process == 0)
        {
          if (GoToPosition(80, 230, 10, 10, 10))
          {
            ++ process;
          }
        }
        else if(process == 1)
        {
          if (GoToRandomPosition(20, 190, 120, 260, 10))
          {
            ++ process;
          }
        }
        else if(process == 2)
        {
          if (GoToPosition(30, 190, 10, 10, 10))
          {
            ++ process;
          }
        }
        else if(process == 3)
        {
          if (GoToPosition(30, 100, 10, 10, 10))
          {
            ++ process;
          }
        }
        else if (process == 4)
        {
            if (GoToPosition(60, 140, 10, 10, 10))
            {
              ++process;
            }
        }
        else if (process == 5)
        {
            if (GoToRandomPosition(90, 80, 150, 140,10))
            {
              ++process;
            }
        }
        else if (process == 6)
        {
            if (GoToPosition(130, 80, 10, 10, 10))
            {
                ++process;
            }
        }
        else if (process == 7)
        {
            if (GoToPosition(200, 30, 10, 10, 10))
            {
                ++process;
            }
        }
        else if (process == 8)
        {
            if (GoToPosition(320, 30, 10, 10,10))
            {
                ++process;
            }
        }
        else if (process == 9)
        {
            if (GoToPosition(330, 250, 10, 10, 10))
            {
                ++process;
            }
        }
        else if (process == 10)
        {
            if (GoToPosition(230,230,10,10,10)) {
                ++process;
            }
        }
        else if (process == 11)
        {
            if (GoToPosition(210,180,10,10,10)) {
                ++process;
            }
        }
        else if (process == 12)
        {
            if (GoToPosition(120,190,10,10,10)) {
                ++process;
            }
        }
        else
        {
            process = 0;
        }
    }

    switch (action)
    {
    case DEFINED:
        // defined by motor();
        break;
    case FIND_OBJ:
        if (Duration == kFindObjDuration || SuperDuration == kFindObjDuration)
        {
            LoadedObjects++;
        }
        LED_1 = 1;
        MyState = 0;
        WheelLeft = 0;
        WheelRight = 0;
        if (Duration == 0 && SuperDuration == 0)
        {
            LED_1 = 0;
        }
        break;
    case DEPOSIT_OBJ:
        WheelLeft = 0;
        WheelRight = 0;
        LED_1 = 2;
        MyState = 0;
        LoadedObjects = 0;
        loaded_objects[RED_LOADED_ID] = 0;
        loaded_objects[CYAN_LOADED_ID] = 0;
        loaded_objects[BLACK_LOADED_ID] = 0;
        loaded_objects[SUPER_LOADED_ID] = 0;
        if (Duration <= 6 && SuperDuration <= 6)
        {
            // When I finish Deposit, I back
            LED_1 = 0;
            motor(-5, -5);
        }
        else
        {
            // if I go out during the deposit, I set LoadedObjects as 6 and retry deposit
            if (!BothColorJudge(object_box))
            {
                LoadedObjects = 6;
                Duration = 0;
                SuperDuration = 0;
                for (int i = 1; i < 4; i++)
                {
                    loaded_objects[i] = 2;
                }
                action = DEFINED;
            }
        }
        break;

    default:
        break;
    }
}
void World2::GoToSuperObj(int a)
{
    GoToPosition(log_super_x, log_super_y, 10, 10, 10);
    if (a == 1)
    {
        log_super_x = -1;
        log_super_y = -1;
    }
}

void World2::GoToAngle(int angle)
{
    angle = angle - Compass;
    angle %= 360;
    if (angle < -180)
    {
        angle += 360;
    }
    if (angle > 180)
    {
        angle -= 360;
    }

    int classification = obstacle(10, 10, 10);
    switch (classification)
    {
    case 0:
        // abs(number) function gives the absolute value of number
        // abs(数字)関数は、数字の絶対値を返す
        if (abs(angle) < 10)
        {
            // If the target angle is on your front
            // 目的の方向が今向いている方向なら
            motor(5, 5);
        }
        else if (abs(angle) < 30)
        {
            if (angle < 0)
            {
                motor(5, 3);
            }
            else
            {
                motor(3, 5);
            }
        }
        else if (abs(angle) < 100)
        {
            if (angle < 0)
            {
                motor(5, 1);
            }
            else
            {
                motor(1, 5);
            }
        }
        else
        {
            if (angle < 0)
            {
                motor(5, -5);
            }
            else
            {
                motor(-5, 5);
            }
        }
        break;

    case 1: // left
        motor(5, 3);
        break;
    case 2: // front
        motor(-5, -5);
        break;
    case 3: //left & front
        motor(5, 1);
        break;
    case 4: // right
        motor(3, 5);
        break;
    case 5: // left & right
        motor(3, 3);
        break;
    case 6: // front & right
        motor(3, 5);
        break;
    case 7: // all
        motor(-5, 5);
        break;
    default:
        break;
    }

    // If the angle > 0, the target angle is on your left side
    // If the angle < 0, the traget angle is on your right side
    // angleが0より大きいなら、目的の方向はロボットからみて左側にある
    // angleが0より小さいなら、目的の方向はロボットから見て右側にある
}

// Problems 問題点
// If the robot is in Position Lost Area
// もし、ロボットが座標喪失エリアにいたら？

bool World2::GoToRandomPosition(int x,int y,int wide_x,int wide_y,int obj_Num)
{
  static int obj = 0;
  static int num = 0;
  wide_x = abs(wide_x - x);
  wide_y = abs(wide_x - y);
  if (obj_Num==1) {
    obj=loaded_objects[BLACK_LOADED_ID];
  }
  else if (obj_Num==2) {
    obj=loaded_objects[CYAN_LOADED_ID];
  }
  else {
    obj=loaded_objects[RED_LOADED_ID];
  }
  if ((obj<=2||LoadedObjects!=6)&&num<=5)
  {
    int x_rnd=rnd(),y_rnd=rnd();
    x_rnd = x_rnd % wide_x;
    y_rnd = y_rnd % wide_y;
    x = x + x_rnd;
    y = y + y_rnd;
    if(GoToPosition(x , y , 5 , 5 , 15))
    {
      ++ num;
    }
  }
  else
  {
    num=0;
    return true;
  }
  return false;
}
bool World2::GoToPosition(int x, int y, int wide_x, int wide_y, int wide_judge_arrived)
{
    static int absolute_x = -1, absolute_y = -1 , loop_num = 0;
    if (x - wide_judge_arrived < pos_x && pos_x < x + wide_judge_arrived && y - wide_judge_arrived < pos_y && pos_y < y + wide_judge_arrived)
    {
        motor(3, 3);
        return true;
    }

    if (!(x - wide_x < absolute_x && absolute_x < x + wide_x && y - wide_y < absolute_y && absolute_y < y + wide_y))
    {
        absolute_x = -1;
    }

    if (absolute_x == -1)
    {
        absolute_x = x - wide_x + rnd() % (wide_x * 2);
        absolute_y = y - wide_y + rnd() % (wide_y * 2);
    }

    x = absolute_x - pos_x;
    y = absolute_y - pos_y;
    // There is 90 degrees difference between math degree and cospace angle
    // 数学上での角と、Cospaceの角度には90度の差がある
    int angle = static_cast<int>((atan2(y, x) / M_PI * 180.0)) - 90;
    GoToAngle(angle);
    return false;
    // 20s * 1000 / 60 = ms
    if (loop_num >= (20 * 1000 / 60))
        {
          loop_num = 0;
          return true;
        }
    ++loop_num;
}

int World2::obstacle(int left, int front, int right)
{
    int ans = 0;
    if (left > US_Left)
    {
        ++ans;
    }
    if (front > US_Front)
    {
        ans += 2;
    }
    if (right > US_Right)
    {
        ans += 4;
    }
    return ans;
}
