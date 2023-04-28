#pragma once

class barrier{
    private:
        int x_position;
        int y_position;
        int hit_count = 0;

    public:
        char* layer = "++++++";
        barrier(int x, int y)
        {
            this->x_position = x;
            this->y_position = y;
        }

        int getX(){
            return x_position;
        }

        int getY(){
            return y_position;
        }

        void setX(int x){
            this->x_position = x;
        }

        void setY(int y){
            this->y_position = y;
        }

        void setHitCount(int count){
            this->hit_count = count;
        }

        int getHitCount(){
            return this->hit_count;
        }

};