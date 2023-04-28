#pragma once

class ship
{
    protected:
        int x_position = 0;
        int y_position = 0;
    
    public:  
        ship(int x, int y){
            this->x_position = x;
            this->y_position = y;
        }

        void setX(int x){
            this->x_position = x;
        }
            
        void setY(int y){
            this->y_position = y;
        }

        int getX(){
            return this->x_position;
        }
    
        int getY(){
            return this->y_position;
        }
            
};