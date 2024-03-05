#ifndef SKILL_H
#define SKILL_H

#include "Player.h"
#include "raylib.h"
#include "Ball.h"
#include <iostream>



class Skill {
    public:
        int id;
        int cd;
        int timeremaining;
        int skill_time;
        Player *p_aliado;
        Player *p_inimigo;
        Ball *ball;
        bool isActive;

        void increaseSpeed();
        void changeDirection();
        void changeEnemyControl();
        void updateSkill();

        Skill(int id, Player *p_aliado, Player *p_inimigo, Ball *ball);
        Skill();
};








#endif