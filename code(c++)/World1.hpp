#ifndef WORLD1_HPP
#define WORLD1_HPP

#include <random>

#include "cospaceBasicSettings.hpp"
#include "judgeColorTools.hpp"

class World1
{
public:
    void setup();
    void loop();
    int shouldTeleport();
    void taskOnTeleport();
    bool GetMyColor();

  private:
      class RandInt
      {
      public:
          RandInt() : mt(std::random_device()()), dist(1, INT_MAX)
          {
          }

          inline int operator()()
          {
              return dist(mt);
          }
    private:
        std::mt19937 mt;
        std::uniform_int_distribution<int> dist;
    };
    RandInt rnd;

    const int kFindObjDuration = 47;
    bool wait(int);
    int US(int);
    void GetMyPosision(int,int);
};

#endif //!WORLD1_HPP
