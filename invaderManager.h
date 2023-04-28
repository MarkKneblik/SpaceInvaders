#pragma once
#include <vector>
#include "alienShip.h"

using namespace std;

const int RIGHT_BOUNDARY = 80;
const int LEFT_BOUNDARY = 0;

class invaderManager{
    private:
        int x_position;
        int y_position;
        bool hit_left_boundary = false;
        bool hit_right_boundary = false;

    public:

        vector<alienShip> alienWave;
       
        invaderManager(int x, int y){
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

        void initWave(){
            int columns = 1;

            for(int i = 0; i < 24; i++){
                
                if(i % 2 == 0)
                {
                    alienShip alien(this->x_position, this->y_position, 1);
                    alienWave.push_back(alien);
                }            
                else
                {
                    alienShip alien(this->x_position, this->y_position, 2);
                    alienWave.push_back(alien);
                }
                    
                
                if(columns < 8){
                    this->x_position += 7;
                    columns++;
                }
                else{
                    this->x_position -= 49;
                    this->y_position -= 2;
                    columns = 1;
                }
            }
        }

        void drawWave(){
            for(long unsigned int i = 0; i < alienWave.size(); i++){
                if(alienWave[i].alien_type == 1)
                {
                    mvprintw(alienWave[i].getY(), alienWave[i].getX(), alienWave[i].first_alien_bottom_layer); 
                    mvprintw(alienWave[i].getY() - 1, alienWave[i].getX(), alienWave[i].first_alien_top_layer);
                }
                else
                {
                    mvprintw(alienWave[i].getY(), alienWave[i].getX(), alienWave[i].second_alien_bottom_layer); 
                    mvprintw(alienWave[i].getY() - 1, alienWave[i].getX(), alienWave[i].second_alien_top_layer);
                }
                
            }       
        }

        int checkWaveSize(){
            return alienWave.size();
        }

        void moveWave()
        {
            if(hit_right_boundary == false && hit_left_boundary == false)
            {
                for(long unsigned int i = 0; i < alienWave.size(); i++)
                {
                    alienWave[i].setX(alienWave[i].getX() + 1);

                    if(alienWave[i].getX() == RIGHT_BOUNDARY)
                    {
                        hit_right_boundary = true;
                        for(long unsigned int i = 0; i < alienWave.size(); i++)
                            alienWave[i].setY(alienWave[i].getY() + 1);
                    } 
                }
            }

            else if(hit_right_boundary == true && hit_left_boundary == false)
            {
                for(long unsigned int i = 0; i < alienWave.size(); i++)
                {
                    alienWave[i].setX(alienWave[i].getX() - 1);
                    

                    if(alienWave[i].getX() == LEFT_BOUNDARY)
                    {
                        hit_left_boundary = true;
                        for(long unsigned int i = 0; i < alienWave.size(); i++)
                            alienWave[i].setY(alienWave[i].getY() + 1);
                    }
                        
                }

                if(hit_left_boundary == true)
                    hit_right_boundary = false;
            }

            else if(hit_left_boundary == true && hit_right_boundary == false)
            {
                for(long unsigned int i = 0; i < alienWave.size(); i++)
                {
                    alienWave[i].setX(alienWave[i].getX() + 1);

                    if(alienWave[i].getX() == RIGHT_BOUNDARY)
                    {
                        hit_right_boundary = true;
                        for(long unsigned int i = 0; i < alienWave.size(); i++)
                            alienWave[i].setY(alienWave[i].getY() + 1);
                    }     
                }
                if(hit_right_boundary == true)
                    hit_left_boundary = false;
            }

            drawWave();
        }
};