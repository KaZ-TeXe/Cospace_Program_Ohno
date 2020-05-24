#include "judgeColorTools.hpp"

int coloror_width = 10;

int red_obj[3][2] = {{232, 255}, {29, 39}, {29, 39}};
int cyan_obj[3][2] = {{29, 39}, {249, 255}, {249, 255}};
int black_obj[3][2] = {{29, 39}, {29, 39}, {29, 39}};
int trap_line[3][2] = {{200, 235}, {215, 250}, {0, 0}};
int blue_zone[3][2] = {{0, 0}, {150, 175}, {255, 255}};
int object_box[3][2] = {{203, 236}, {130, 148}, {0, 0}};
int gray_zone[3][2] = {{165, 190}, {176, 201}, {233, 255}};
int sp_obj[3][2] = {{180, 255}, {30, 50}, {200, 255}};
int purple_line[3][2] = {{150, 180}, {80, 100}, {180, 220}};
int white_zone[3][2] = {{204, 235}, {217, 248}, {255, 255}};
int world1_maker[3][2] = {{180, 206}, {29, 39}, {198, 188}};
int blue_trap[3][2] = {{53, 62}, {96, 111}, {221, 245}};

int ColorJudgeLeft(int color[3][2])
{
    return (color[0][0] - coloror_width <= CSLeft_R && CSLeft_R <= color[0][0] + coloror_width && color[1][0] - coloror_width <= CSLeft_G && CSLeft_G <= color[1][0] + coloror_width && color[2][0] - coloror_width <= CSLeft_B && CSLeft_B <= color[2][0] + coloror_width) ||
           (color[0][1] - coloror_width <= CSLeft_R && CSLeft_R <= color[0][1] + coloror_width && color[1][1] - coloror_width <= CSLeft_G && CSLeft_G <= color[1][1] + coloror_width && color[2][1] - coloror_width <= CSLeft_B && CSLeft_B <= color[2][1] + coloror_width);
}
int ColorJudgeRight(int color[3][2])
{
    return (color[0][0] - coloror_width <= CSRight_R && CSRight_R <= color[0][0] + coloror_width && color[1][0] - coloror_width <= CSRight_G && CSRight_G <= color[1][0] + coloror_width && color[2][0] - coloror_width <= CSRight_B && CSRight_B <= color[2][0] + coloror_width) ||
           (color[0][1] - coloror_width <= CSRight_R && CSRight_R <= color[0][1] + coloror_width && color[1][1] - coloror_width <= CSRight_G && CSRight_G <= color[1][1] + coloror_width && color[2][1] - coloror_width <= CSRight_B && CSRight_B <= color[2][1] + coloror_width);
}

int EitherColorJudge(int color[3][2])
{
    return ColorJudgeLeft(color) || ColorJudgeRight(color);
}
int BothColorJudge(int color[3][2])
{
    return ColorJudgeLeft(color) && ColorJudgeRight(color);
}
