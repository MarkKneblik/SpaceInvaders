#pragma once
#include "ship.h"
#include "bullet.h"

class playerShip : public ship{
    private:
        bool can_fire = true;
        int num_of_lives = 3;
        
    public:
        char* top_layer =  " __/\\__";
        char* bottom_layer =  "/______\\";

        playerShip(int x, int y) : ship(x, y){
            this->x_position = x;
            this->y_position = y;
        }

        void setCanFire(bool fire){
            this->can_fire = fire;
        }

        bullet shoot()
        {
            bullet bul(this->x_position + 3, this->y_position);
            can_fire = false;
            return bul;
        }

        bool getCanFire(){
            return this->can_fire;
        }

        int getNumOfLives(){
            return this->num_of_lives;
        }

        int setNumOfLives(int x){
            this->num_of_lives = x;
        }
};