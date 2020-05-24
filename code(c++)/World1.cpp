#include "World1.hpp"

#define FOR for
#define rep(i, n) FOR(int i = 0; i < n; i++)

using namespace std;

void World1::setup()
{
    LoadedObjects = 0;
    if (GetMyColor()) {
      mycolor=true;
    }
    else
    {
      mycolor=false;
    }
    //Is this Robot is blue?
    //このロボットが青なのか否か
}

void World1::loop()
{
    // the spare space of storeable objects if you have at least 1 object for each color
    // それぞれの色のオブジェクトを、最低1つもつときに、まだ余っているオブジェクトを積めるスペース
    int load_object_spare = 6;
    static int trap = 0;
    //static int GoToobjbox=0;
    load_object_spare -= LoadedObjects;
    if (loaded_objects[RED_LOADED_ID] == 0)
    {
        load_object_spare--;
    }
    if (loaded_objects[CYAN_LOADED_ID] == 0)
    {
        load_object_spare--;
    }
    if (loaded_objects[BLACK_LOADED_ID] == 0)
    {
        load_object_spare--;
    }

    if (SuperDuration > 0)
    {
        SuperDuration--;
    }
    else if(EitherColorJudge(blue_trap)){
        loaded_objects[RED_LOADED_ID] = 0;
        loaded_objects[CYAN_LOADED_ID] = 0;
        loaded_objects[BLACK_LOADED_ID] = 0;
        LoadedObjects = 0;
    }
    else if (EitherColorJudge(red_obj) && (loaded_objects[RED_LOADED_ID] < 2 || (Time >= 150 && loaded_objects[RED_LOADED_ID] < 3)) && LoadedObjects < 6)
    {
        action = FIND_OBJ;
        SuperDuration = kFindObjDuration;
        loaded_objects[RED_LOADED_ID]++;
    }
    else if (EitherColorJudge(cyan_obj) && (loaded_objects[CYAN_LOADED_ID] < 2 || (Time >= 150 && loaded_objects[CYAN_LOADED_ID] < 3)) && LoadedObjects < 6)
    {
        action = FIND_OBJ;
        SuperDuration = kFindObjDuration;
        loaded_objects[CYAN_LOADED_ID]++;
    }
    else if (EitherColorJudge(black_obj) && (loaded_objects[BLACK_LOADED_ID] < 2 || (Time >= 150 && loaded_objects[BLACK_LOADED_ID] < 3)) && LoadedObjects < 6)
    {
        action = FIND_OBJ;
        SuperDuration = kFindObjDuration;
        loaded_objects[BLACK_LOADED_ID]++;
    }
    else if (EitherColorJudge(object_box))
    {
        if(LoadedObjects >= 5 || (Time>=150 && LoadedObjects >= 3)) {
            if (BothColorJudge(object_box))
            {
                action = DEPOSIT_OBJ;
                SuperDuration = 50;
                //GoToobjbox=0;
            }
            else if (ColorJudgeLeft(object_box))
            {
                motor(0, 5);
            }
            else
            {
                motor(5, 0);
            }
        }
    }
    else if (EitherColorJudge(trap_line) && LoadedObjects != 0)
    {
      if (BothColorJudge(trap_line))
      {
        if (trap==1) {
          motor(-3, -5);
          Duration=5;
        }
        else{
          motor(-5,-3);
          Duration=5;
        }
      }
      else if (ColorJudgeLeft(trap_line))
      {
        motor(1, -3);
        trap = 1;
      }
      else
      {
        motor(-3, 1);
        trap = 2;
      }
    }
    else if (Duration > 0)
    {
      Duration--;
    }
    else{
      if(US_Left>30&&US_Right>30){
        motor(3,3);
      }
      else if(US_Left>30){
        motor(1,3);
      }
      else if(US_Right>30){
        motor(3,1);
      }
      else if (US_Left<20&&US_Right<20&&US_Front<15) {
        motor(3,-2);
      }
      else if (US_Left<20){
        motor(3,-1);
      }
      else if (US_Right<20){
        motor(-1,3);
      }
      else if (US_Front<15){
        motor(-3,3);
      }
      else if (US_Left<25&&US_Right<25&&US_Front<20){
        motor(3,-1);
      }
      else if (US_Left<25) {
        motor(3,0);
      }
      else if (US_Right<25) {
        motor(0,3);
      }
      else if (US_Front<20) {
        motor(3,-2);
      }
      else{
        motor(3,3);
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
        if (Duration <= 6 && SuperDuration <= 6)
        {
            // When I finish Deposit, I back
            LED_1 = 0;
            motor(-5, -5);
            LoadedObjects = 0;
            loaded_objects[RED_LOADED_ID] = 0;
            loaded_objects[CYAN_LOADED_ID] = 0;
            loaded_objects[BLACK_LOADED_ID] = 0;
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

int World1::shouldTeleport()
{
    return (180 < Time && !EitherColorJudge(object_box) && LoadedObjects == 0) || 239 < Time;
}

void World1::taskOnTeleport()
{
    LoadedObjects = 0;
    rep(i, static_cast<int>(extent<decltype(loaded_objects), 0>::value))
    {
        loaded_objects[i] = 0;
    }
    // teleport location
    Teleport = 3;
    CurGame = 1;
}
bool World1::GetMyColor()
{
  if(Compass<180)
  {
    return true;
  }
  else
  {
    return false;
  }
}
bool World1::wait(int time)
{
  static int loop_num=0;
  if (loop_num >= (time * 1000 / 60))
  {
    return true;
    loop_num=0;
  }
  loop_num++;
  return false;
}
