#pragma once
#include "ship.h"
#include "bullet.h"

class alienShip : public ship{
    public:
        char* first_alien_top_layer = "  _  ";
        char* first_alien_bottom_layer = "<o.o>";
        char* second_alien_top_layer = "  o  ";
        char* second_alien_bottom_layer = "[---]";
        int alien_type = 1;

        alienShip(int x, int y, int type) : ship(x, y)
        {
            this->alien_type = type;
        }

        bullet shoot()
        {
            bullet bul(this->x_position + 3, this->y_position);
            return bul;
        }
};