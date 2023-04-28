#include "data.h"
#include "game.h"

class interfaces{
public:
    WINDOW * mainwin;
    WINDOW* menu;
    WINDOW* pause_win;
     WINDOW* game_over_win;
    int LINES  = 27, COLUMNS = 80;
    int x = COLUMNS / 2;
    int y = LINES / 2;
    game gm;

    interfaces() : gm(x, y - 10) {}


    void createMainWin(){
        if ( (this->mainwin = initscr()) == NULL ) {
        fprintf(stderr, "Error initialising ncurses.\n");
        exit(EXIT_FAILURE);
        }
    }

    void createPauseWin(){
         this->pause_win = newwin(LINES, COLUMNS, y, x);
        wrefresh(this->pause_win);
        if ( (this->pause_win = initscr()) == NULL ) {
            fprintf(stderr, "Error initialising ncurses.\n");
            exit(EXIT_FAILURE);
        }

    }

    void createMenuWin(){
        this->menu = newwin(LINES, COLUMNS, y, x);
        if(((this->menu = initscr())) == NULL){
        fprintf(stderr, "Error initialising ncurses.\n");
        exit(EXIT_FAILURE);
        }
    }

    void runInterfaces()
    {       
        int ch;    /*  Switch of echoing and enable keypad (for arrow keys)  */
        noecho();
        keypad(this->mainwin, TRUE);
        keypad(this->menu, TRUE);
        keypad(pause_win, TRUE);
        curs_set(0);

        ////////////
        data* database = new data();
        database->initHighScore();

        mvwprintw(this->menu, 1, x, "High score: %u", database->high_score);
        mvwprintw(this->menu, 3, x, "WELCOME TO SPACE INVADERS");
        mvwprintw(this->menu, y - 2, x, "Press e for easy difficulty.");
        mvwprintw(this->menu, y - 1, x, "Press m for medium difficulty.");
        mvwprintw(this->menu, y, x, "Press h for hard difficulty.");
        mvwprintw(this->menu, y + 1, x, "Press q to quit.");
        mvwprintw(this->menu, y + 3, x, "CONTROLS: ");
        mvwprintw(this->menu, y + 4, x, "Press left arrow key or right arrow key to move. ");
        mvwprintw(this->menu, y + 5, x, "Press spacebar to shoot.");
        wrefresh(this->menu);

        
        int character; 
        while(((character = wgetch(this->menu)) != 'e') && ((character = wgetch(this->menu)) != 'm') && ((character = wgetch(this->menu)) != 'h') && ((character = wgetch(this->menu)) != 'q'))
        {
            ;
        }

        werase(this->menu);
        if(character == 'e')
        {
            gm.setAlienBulletDelta(1);
        } 
        else if(character == 'm')
        {
            gm.setAlienBulletDelta(2);
        }
        else if(character == 'h')
        {
            gm.setAlienBulletDelta(3);
        }
        else if(character == 'q')
        {
            delwin(this->menu);
            delwin(this->mainwin);
            delwin(pause_win);
            endwin();
            exit(1);
        }
    
        
        gm.player.setY(LINES);
        gm.manager.setX(19);
        gm.setOriginalY(5);
        gm.manager.setY(5);

        gm.manager.initWave();
        gm.manager.drawWave();

        gm.initBarriers();
        gm.drawBarriers();
        
        gm.drawPlayer();
        gm.updateScoreAndLives();
    
        wrefresh(this->mainwin);

        halfdelay(3);

        /*  Loop until user hits 'q' to quit  */
        std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();

        gm.manager.moveWave();
        auto old_now = now.time_since_epoch();
        auto time_since_last_move_ms = std::chrono::duration_cast<std::chrono::milliseconds>(old_now).count();
    
        while ( (ch = getch()) != 'q' ) {
            now = std::chrono::system_clock::now();

            auto new_now = now.time_since_epoch();
            auto new_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(new_now).count();

            auto delta_time_ms = new_time_ms - time_since_last_move_ms;

            switch ( ch ) {
                case KEY_LEFT:
                    if ( gm.player.getX() > 0 )
                    gm.player.setX(gm.player.getX() - 1);
                    break;
            
                case KEY_RIGHT:
                    if ( gm.player.getX() < COLUMNS )
                    gm.player.setX(gm.player.getX() + 1);
                    break;
            
                case KEY_HOME:
                    x = 0;
                    y = 0;
                    break;
            
                case KEY_END:
                    x = COLUMNS;
                    y = LINES;
                    break;

                case ' ':
                    if(gm.player.getCanFire())
                        gm.player_bullet.push_back(gm.player.shoot());
                    break;
                case 'p':
                    werase(this->mainwin);
                    wrefresh(this->mainwin);
                    mvwprintw(pause_win, y - 1, x, "Game paused.");
                    mvwprintw(pause_win, y, x, "Press p to unpause or q to quit.");
                    wrefresh(pause_win);
                    int c;

                    while(((c = getch()) != 'q') && ((c = getch()) != 'p'))
                    {
                        ;
                    }

                    if(c == 'q')
                    {
                        werase(pause_win);
                        wrefresh(pause_win);
                        wrefresh(this->mainwin);
                        goto breakFromNestedLoops;
                    }
                        
                    else if(c == 'p')
                    {
                        werase(pause_win);
                        wrefresh(pause_win);
                        wrefresh(this->mainwin);
                        break;     
                    }
                }

            clear();
            gm.drawPlayer();

            if(delta_time_ms >= 200)
            {
                gm.manager.moveWave();
                if(gm.player_bullet.size() > 0)
                {
                    gm.drawPlayerBullet();
                    gm.movePlayerBullet();
                }
                gm.checkAlienCollision();

                gm.alienWaveShoot();
                if(gm.alien_bullets.size() > 0)
                {
                    gm.drawAlienBullets();
                    gm.moveAlienBullets();
                }

                gm.checkBarrierCollision();
                gm.drawBarriers();

                gm.checkPlayerCollision();

                if(gm.checkGameEnd() == true)
                    break;
                gm.updateScoreAndLives();

                old_now = now.time_since_epoch();
                time_since_last_move_ms = std::chrono::duration_cast<std::chrono::milliseconds>(old_now).count();
            }
            else
            {
                if(gm.player_bullet.size() > 0)
                    gm.drawPlayerBullet();

                gm.checkAlienCollision();
                gm.manager.drawWave();

                gm.alienWaveShoot();
                if(gm.alien_bullets.size() > 0)
                {
                    gm.drawAlienBullets();
                }

                gm.checkBarrierCollision();
                gm.drawBarriers();

                gm.checkPlayerCollision();
                if(gm.checkGameEnd() == true)
                    break;
                gm.updateScoreAndLives();
            }
            wrefresh(this->mainwin);
        }

        breakFromNestedLoops:
    
        /*  Clean up after ourselves  */
    
        werase(this->mainwin);
        wrefresh(this->mainwin);
        

        WINDOW * game_over_win = newwin(LINES, COLUMNS, y, x);
        wrefresh(game_over_win);
        game_over_win = initscr();
        noecho();
        keypad(game_over_win, TRUE);
        curs_set(0);
        wrefresh(game_over_win);

        mvwprintw(game_over_win, y - 1, x, "GAME OVER!");
        mvwprintw(game_over_win, y, x, "Your score: %d", gm.getScore());
        mvwprintw(game_over_win, y + 2, x, "Press q to quit.");
        while ( (ch = getch()) != 'q' ) 
        {
            ;
        }
 
        database->writeHighScore(gm.getScore());

        delwin(this->mainwin);
        delwin(this->pause_win);
        delwin(this->game_over_win);
        endwin();
        refresh();
    }

};
