#pragma once
#include <vector>
#include <cstdlib>
#include "bullet.h"
#include"barrier.h"

class game{
    private:
        int score = 0;
        int x_position = 0;
        int y_position = 0;
        int original_y_position = 0;
        int y_position_delta = 0;
        int alien_bullet_delta = 0;
        bool game_ended;
    
    public:
        invaderManager manager;
        playerShip player;
        vector<bullet> alien_bullets;
        vector<bullet> player_bullet;
        vector<barrier> barriers;
        
        
        game(int x, int y) : manager{x, y}, player{x, y}
        {
            this->score = 0;
            this->x_position = x;
            this->y_position = y;
        }

        int getScore()
        {
            return this->score;
        }

        void setScore(int x)
        {
            this->score = x;
        }

        void setOriginalY(int y)
        {
            this->original_y_position = y;
        }

        void setAlienBulletDelta(int delta){
            this->alien_bullet_delta = delta;
        }

        void drawPlayer()
        {
            mvprintw(player.getY(), player.getX(), " __/\\__");
            mvaddstr(player.getY() + 1, player.getX(), "/______\\");
        }

        void drawPlayerBullet()
        {
            mvprintw(player_bullet[0].getY(), player_bullet[0].getX(), "'");
        }

        void movePlayerBullet()
        {
            player_bullet[0].setY(player_bullet[0].getY() - 1);
        }

        void checkAlienCollision()
        {
            if (player_bullet.size() > 0)
            {
                for(long unsigned int  i = 0; i < manager.alienWave.size(); i++)
                {
                    if ((player_bullet[0].getY() <= manager.alienWave[i].getY() + 1)&& ((player_bullet[0].getX() >= manager.alienWave[i].getX()) && (player_bullet[0].getX() <= manager.alienWave[i].getX() + 5)))
                    {
                        manager.alienWave.erase(manager.alienWave.begin() + i);
                        player_bullet.erase(player_bullet.begin());
                        player.setCanFire(true);
                        this->score += 10;
                        break;
                    }
                    else if(player_bullet[0].getY() <= 0 )      // if bullet reaches to border of window
                    {
                        player_bullet.erase(player_bullet.begin());
                        player.setCanFire(true);
                        break;
                    }
                }
            }
            if(manager.alienWave.size() == 0)
            {
                manager.setX(19);
                y_position_delta += 2;
                manager.setY(this->original_y_position + y_position_delta);
                manager.initWave();
            }
        }

        void alienWaveShoot()
        {
            if(alien_bullets.size() < 3)
            {
                 long unsigned int random_index = (rand() % manager.alienWave.size()) + 0;
                alien_bullets.push_back(manager.alienWave[random_index].shoot());
            }
        }

        void drawAlienBullets()
        {
            for(int i = 0; i < alien_bullets.size(); i++)
            {
                mvprintw(alien_bullets[i].getY(), alien_bullets[i].getX(), "'");
            }
        }

        void moveAlienBullets()
        {
            for(int i = 0; i < alien_bullets.size(); i++)
            {
                 alien_bullets[i].setY(alien_bullets[i].getY() + this->alien_bullet_delta);
            }
        }

        void checkPlayerCollision()
        {
            if (alien_bullets.size() > 0)
            {
                for(long unsigned int i = 0; i < alien_bullets.size(); i++)
                {
                    if((alien_bullets[i].getY() > player.getY()) &&  ((alien_bullets[i].getX() >= player.getX()) && (alien_bullets[i].getX() <= player.getX() + 8)))
                    {
                        player.setNumOfLives(player.getNumOfLives() - 1);
                        alien_bullets.erase(alien_bullets.begin() + i);
                        continue;
                    }
                    else if(alien_bullets[i].getY() > player.getY())
                    {
                        alien_bullets.erase(alien_bullets.begin() + i);
                        continue;

                    }
                }
            }
        }

        bool checkGameEnd()
        {
            if(player.getNumOfLives() <= 0)
                return true;
            else
            {
                for(long unsigned int i = 0; i < manager.alienWave.size(); i++)
                {
                    if(manager.alienWave[i].getY() >= player.getY())
                        return true;
                }

            }
            
            return false;
        }

        void updateScoreAndLives()
        {
            mvprintw(0, this->x_position, "SCORE: %u    LIVES: %u", getScore(), player.getNumOfLives());
        }

        void initBarriers()
        {
            int x = 11;
            int y = player.getY() - 5;

           
            for(int i = 0; i < 4; i++)
            {
                barrier bar(x, y);
                barriers.push_back(bar);
                x = x + 20;
            }
        }

        void drawBarriers()
        {
            for(int i = 0; i < 4; i++)
            {
                if(barriers[i].getHitCount() == 0)
                {
                    mvprintw(barriers[i].getY(), barriers[i].getX(), "++++++");
                    mvprintw(barriers[i].getY() + 1, barriers[i].getX(), "++++++");
                    mvprintw(barriers[i].getY() + 2, barriers[i].getX(), "++++++");
                    mvprintw(barriers[i].getY() + 3, barriers[i].getX(), "++++++");
                }
                else if(barriers[i].getHitCount() == 1)
                {
                    mvprintw(barriers[i].getY() + 1, barriers[i].getX(), "++++++");
                    mvprintw(barriers[i].getY() + 2, barriers[i].getX(), "++++++");
                    mvprintw(barriers[i].getY() + 3, barriers[i].getX(), "++++++");   
                }
                else if(barriers[i].getHitCount() == 2)
                {
                    mvprintw(barriers[i].getY() + 2, barriers[i].getX(), "++++++");
                    mvprintw(barriers[i].getY() + 3, barriers[i].getX(), "++++++");   
                }
                else if(barriers[i].getHitCount() == 3)
                    mvprintw(barriers[i].getY() + 3, barriers[i].getX(), "++++++");   
                
            }
        }

        void checkBarrierCollision()
        {
            for(int i = 0; i < alien_bullets.size(); i ++)
            {
                for(int j = 0; j < barriers.size(); j++)
                {
                    if((alien_bullets[i].getX() >= barriers[j].getX()) && (alien_bullets[i].getX() <= barriers[j].getX() + 6))
                    {
                        if((barriers[j].getHitCount() == 0) && (alien_bullets[i].getY() > barriers[j].getY()))
                        {
                            barriers[j].setHitCount(barriers[j].getHitCount() + 1);
                            alien_bullets.erase(alien_bullets.begin() + i);
                            if(barriers[j].getHitCount() >= 4)
                                barriers.erase(barriers.begin() + j);
                        }   
                        else if((barriers[j].getHitCount() == 1) && (alien_bullets[i].getY() > barriers[j].getY() + 1))
                        {
                            barriers[j].setHitCount(barriers[j].getHitCount() + 1);
                            alien_bullets.erase(alien_bullets.begin() + i);
                            if(barriers[j].getHitCount() >= 4)
                                barriers.erase(barriers.begin() + j);
                        }
                        else if((barriers[j].getHitCount() == 2) && (alien_bullets[i].getY() > barriers[j].getY() + 2))
                        {
                            barriers[j].setHitCount(barriers[j].getHitCount() + 1);
                            alien_bullets.erase(alien_bullets.begin() + i);
                            if(barriers[j].getHitCount() >= 4)
                                barriers.erase(barriers.begin() + j);
                        }
                        else if((barriers[j].getHitCount() == 3) && (alien_bullets[i].getY() > barriers[j].getY() + 3))
                        {
                            barriers[j].setHitCount(barriers[j].getHitCount() + 1);
                            alien_bullets.erase(alien_bullets.begin() + i);
                            if(barriers[j].getHitCount() >= 4)
                                barriers.erase(barriers.begin() + j);
                        }
                    }

                }
            }
        }
};
