#pragma once
#include <fstream>

class data{
public:
    int high_score = 0;
    data(){;}

    void initHighScore(){
        ifstream read_file;
        read_file.open("highscore.txt");
        this->high_score = 0;
        if(read_file.is_open())
            read_file >> this->high_score;
        read_file.close();

    }
    
    void writeHighScore(int scr){
        if(scr > high_score)
        {
            ofstream write_file;
            write_file.open("highscore.txt");
            if(write_file.is_open())
                write_file << scr;
            write_file.close();
        }
    }
};






    