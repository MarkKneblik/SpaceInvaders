#pragma once

class bullet{
    private:
        int x_position;
        int y_position;

    public:
        char* bullet_drawing = "'";
        bullet(int x, int y)
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
};