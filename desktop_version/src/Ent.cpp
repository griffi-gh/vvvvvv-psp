#include "Ent.h"

#include "Game.h"
#include "Graphics.h"

entclass::entclass(void)
{
    clear();
}

void entclass::clear(void)
{
    invis = false;
    type = EntityType_PLAYER;
    size = 0;
    tile = 0;
    rule = 0;
    state = 0;
    statedelay = 0;
    life = 0;
    colour = EntityColour_CREW_CYAN;
    para = 0;
    behave = 0;
    animate = 0;

    xp = 0;
    yp = 0;
    ax = 0;
    ay = 0;
    vx = 0;
    vy = 0;
    w = 16;
    h = 16;
    cx = 0;
    cy = 0;
    newxp = 0;
    newyp = 0;
    oldxp = 0;
    oldyp = 0;

    x1 = 0;
    y1 = 0;
    x2 = 320;
    y2 = 240;

    gravity = false;
    onground = 0;
    onroof = 0;
    collisionframedelay = 0;
    collisiondrawframe = 0;
    collisionwalkingframe = 0;
    visualonground = 0;
    visualonroof = 0;

    onentity = 0;
    harmful = false;
    onwall = 0;
    onxwall = 0;
    onywall = 0;
    isplatform = false;

    framedelay = 0;
    drawframe = 0;
    walkingframe = 0;
    dir = 0;
    actionframe = 0;

    SDL_zero(realcol);
    lerpoldxp = 0;
    lerpoldyp = 0;
}

bool entclass::outside(void)
{
    // Returns true if any point of the entity is outside the map.
    // Adjusts velocity for a clean collision.
    if (xp < x1)
    {
        xp = x1;
        return true;
    }
    if (yp < y1)
    {
        yp = y1;
        return true;
    }
    if (xp + w > x2)
    {
        xp = x2 - w;
        return true;
    }
    if (yp + h > y2)
    {
        yp = y2 - h;
        return true;
    }
    return false;
}

void entclass::setenemy( int t )
{
    switch(t)
    {
    case 0:
        //lies emitter
        switch ((int) para)
        {
        case 0:
            tile = 60;
            animate = 2;
            colour = EntityColour_ENEMY_RED;
            behave = 10;
            w = 32;
            h = 32;
            x1 = -200;
            break;
        case 1:
            yp += 10;
            lerpoldyp += 10;
            tile = 63;
            animate = 100; //LIES
            colour = EntityColour_ENEMY_RED;
            behave = 11;
            para = 9; //destroyed when outside
            x1 = -200;
            x2 = 400;
            w = 26;
            h = 10;
            cx = 1;
            cy = 1;
            break;
        case 2:
            tile = 62;
            animate = 100;
            colour = EntityColour_ENEMY_RED;
            behave = -1;
            w = 32;
            h = 32;
            break;
        }
        break;
    case 1:
        //FACTORY emitter
        switch ((int) para)
        {
        case 0:
            tile = 72;
            animate = 3;
            size = 9;
            colour = EntityColour_ENEMY_RED;
            behave = 12;
            w = 64;
            h = 40;
            cx = 0;
            cy = 24;
            break;
        case 1:
            xp += 4;
            lerpoldxp += 4;
            yp -= 4;
            lerpoldyp -= 4;
            tile = 76;
            animate = 100; // Clouds
            colour = EntityColour_ENEMY_RED;
            behave = 13;
            para = -6; //destroyed when outside
            x2 = 400;
            w = 32;
            h = 12;
            cx = 0;
            cy = 6;
            break;
        case 2:
            tile = 77;
            animate = 100;
            colour = EntityColour_ENEMY_RED;
            behave = -1;
            w = 32;
            h = 16;
            break;
        }
        break;
    default:
        break;
    }
}

void entclass::setenemyroom( int rx, int ry )
{
    //Simple function to initilise simple enemies
    rx -= 100;
    ry -= 100;
    switch(rn(rx, ry))
    {
        //Space Station 1
    case rn(12, 3):  //Security Drone
        tile = 36;
        colour = EntityColour_ENEMY_PINK;
        animate = 1;
        break;
    case rn(13, 3):  //Wavelengths
        tile = 32;
        colour = EntityColour_ENEMY_GREEN;
        animate = 1;
        w = 32;
        break;
    case rn(15, 3):  //Traffic
        tile = 28;
        colour = EntityColour_ENEMY_RED;
        animate = 1;
        w = 22;
        h = 32;
        break;
    case rn(12, 5):  //The Yes Men
        tile = 40;
        colour = EntityColour_ENEMY_YELLOW;
        animate = 1;
        w = 20;
        h = 20;
        break;
    case rn(13, 6):  //Hunchbacked Guards
        tile = 44;
        colour = EntityColour_ENEMY_PINK;
        animate = 1;
        w = 16;
        h = 20;
        break;
    case rn(13, 4):  //Communication Station
        harmful = false;
        if (xp == 256)
        {
            //transmittor
            tile = 104;
            colour = EntityColour_INACTIVE_ENTITY;
            animate = 7;
            w = 16;
            h = 16;
            xp -= 24;
            lerpoldxp -= 24;
            yp -= 16;
            lerpoldyp -= 16;
        }
        else
        {
            //radar dish
            tile =124;
            colour = EntityColour_INACTIVE_ENTITY;
            animate = 6;
            w = 32;
            h = 32;
            cx = 4;
            size = 9;
            xp -= 4;
            lerpoldxp -= 4;
            yp -= 32;
            lerpoldyp -= 32;
        }

        break;
        //The Lab
    case rn(4, 0):
        tile = 78;
        colour = EntityColour_ENEMY_GREEN;
        animate = 1;
        w = 16;
        h = 16;
        break;
    case rn(2, 0):
        tile = 88;
        colour = EntityColour_ENEMY_CYAN;
        animate = 1;
        w = 16;
        h = 16;
        break;
        //Space Station 2
    case rn(14, 11):
        colour = EntityColour_ENEMY_ORANGE;
        break; //Lies
    case rn(16, 11):
        colour = EntityColour_ENEMY_PINK;
        break; //Lies
    case rn(13, 10):
        colour = EntityColour_ENEMY_CYAN;
        break; //Factory
    case rn(13, 9):
        colour = EntityColour_ENEMY_YELLOW;
        break; //Factory
    case rn(13, 8):
        colour = EntityColour_ENEMY_PINK;
        break; //Factory
    case rn(11, 13): //Truth
        tile = 64;
        colour = EntityColour_ENEMY_GREEN;
        animate = 100;
        w = 44;
        h = 10;
        size = 10;
        break;
    case rn(17, 7): //Brass sent us under the top
        tile =82;
        colour = EntityColour_ENEMY_PINK;
        animate = 5;
        w = 28;
        h = 32;
        cx = 4;
        break;
    case rn(10, 7): // (deception)
        tile = 92;
        colour = EntityColour_ENEMY_RED;
        animate = 1;
        w = 16;
        h = 16;
        break;
    case rn(14, 13): // (chose poorly)
        tile = 56;
        colour = EntityColour_ENEMY_RED;
        animate = 1;
        w = 15;
        h = 24;
        break;
    case rn(13, 12): // (backsliders)
        tile = 164;
        colour = EntityColour_ENEMY_GREEN;
        animate = 1;
        w = 16;
        h = 16;
        break;
    case rn(14, 8): // (wheel of fortune room)
        tile = 116;
        colour = EntityColour_ENEMY_BLUE;
        animate = 1;
        w = 32;
        h = 32;
        break;
    case rn(16, 9): // (seeing dollar signs)
        tile = 68;
        colour = EntityColour_ENEMY_GREEN;
        animate = 1;
        w = 16;
        h = 16;
        break;
    case rn(16, 7): // (tomb of mad carew)
        tile = 106;
        colour = EntityColour_ENEMY_GREEN;
        animate = 2;
        w = 24;
        h = 25;
        break;
        //Warp Zone
    case rn(15, 2): // (numbers)
        tile = 100;
        colour = EntityColour_ENEMY_RED;
        animate = 1;
        w = 32;
        h = 14;
        yp += 1;
        lerpoldyp += 1;
        break;
    case rn(16, 2): // (Manequins)
        tile = 52;
        colour = EntityColour_ENEMY_GREEN;
        animate = 5;
        w = 16;
        h = 25;
        yp -= 4;
        lerpoldyp -= 4;
        break;
    case rn(18, 0): // (Obey)
        tile = 51;
        colour = EntityColour_ENEMY_CYAN;
        animate = 100;
        w = 30;
        h = 14;
        break;
    case rn(19, 1): // Ascending and Descending
        tile = 48;
        colour = EntityColour_ENEMY_YELLOW;
        animate = 5;
        w = 16;
        h = 16;
        break;
    case rn(19, 2): // Shockwave Rider
        tile = 176;
        colour = EntityColour_ENEMY_RED;
        animate = 1;
        w = 16;
        h = 16;
        break;
    case rn(18, 3): // Mind the gap
        tile = 168;
        colour = EntityColour_ENEMY_GREEN;
        animate = 1;
        w = 16;
        h = 16;
        break;
    case rn(17, 3): // Edge Games
        if (yp ==96)
        {
            tile = 160;
            colour = EntityColour_ENEMY_PINK;
            animate = 1;
            w = 16;
            h = 16;
        }
        else
        {
            tile = 156;
            colour = EntityColour_ENEMY_PINK;
            animate = 1;
            w = 16;
            h = 16;
        }
        break;
    case rn(16, 0): // I love you
        tile = 112;
        colour = EntityColour_ENEMY_PINK;
        animate = 5;
        w = 16;
        h = 16;
        break;
    case rn(14, 2): // That's why I have to kill you
        tile = 114;
        colour = EntityColour_ENEMY_RED;
        animate = 5;
        w = 16;
        h = 16;
        break;
    case rn(18, 2): // Thinking with Portals
        //depends on direction
        if (xp ==88)
        {
            tile = 54+12;
            colour = EntityColour_ENEMY_BLUE;
            animate = 100;
            w = 60;
            h = 16;
            size = 10;
        }
        else
        {
            tile = 54;
            colour = EntityColour_ENEMY_BLUE;
            animate = 100;
            w = 60;
            h = 16;
            size = 10;
        }
        break;
        //Final level
    case rn(50-100, 53-100):  //The Yes Men
        tile = 40;
        colour = EntityColour_ENEMY_YELLOW;
        animate = 1;
        w = 20;
        h = 20;
        break;
    case rn(48-100, 51-100):  //Wavelengths
        tile = 32;
        colour = EntityColour_ENEMY_GREEN;
        animate = 1;
        w = 32;
        break;
    case rn(43-100,52-100): // Ascending and Descending
        tile = 48;
        colour = EntityColour_ENEMY_YELLOW;
        animate = 5;
        w = 16;
        h = 16;
        break;
    case rn(46-100,51-100): //kids his age
        tile = 88;
        colour = EntityColour_ENEMY_CYAN;
        animate = 1;
        w = 16;
        h = 16;
        break;
    case rn(43-100,51-100): // Mind the gap
        tile = 168;
        colour = EntityColour_ENEMY_GREEN;
        animate = 1;
        w = 16;
        h = 16;
        break;
    case rn(44-100,51-100): // vertigo?
        tile = 172;
        colour = EntityColour_ENEMY_GREEN;
        animate = 100;
        w = 32;
        h = 32;
        break;
    case rn(44-100,52-100): // (backsliders)
        tile = 164;
        colour = EntityColour_ENEMY_GREEN;
        animate = 1;
        w = 16;
        h = 16;
        break;
    case rn(43-100, 56-100): //Intermission 1
        tile = 88;
        colour = EntityColour_ENEMY_GRAVITRON;
        animate = 1;
        w = 16;
        h = 16;
        break;
    case rn(45-100, 56-100): //Intermission 1
        tile = 88;
        colour = EntityColour_ENEMY_GRAVITRON;
        animate = 1;
        w = 16;
        h = 16;
        break;
        //The elephant
    case rn(11, 9):
    case rn(12, 9):
    case rn(11, 8):
    case rn(12, 8):
        tile = 0;
        colour = EntityColour_TELEPORTER_FLASHING;
        animate = 0;
        w = 464;
        h = 320;
        size = 11;
        harmful = false;
        break;
    }
}

void entclass::settreadmillcolour( int rx, int ry )
{
    rx -= 100;
    ry -= 100;
    rx += 50 - 12;
    ry += 50 - 14;   //Space Station

    tile = 20; //default as blue
    switch(rn(rx, ry))
    {
    case rn(52, 48):
        tile = 791;
        break; //Cyan

    case rn(49, 47):
        tile = 24;
        break; //Yellow
    case rn(56, 44):
        tile = 24;
        break; //Yellow
    case rn(54, 49):
        tile = 24;
        break; //Yellow

    case rn(49, 49):
        tile = 36;
        break; //Green
    case rn(55, 44):
        tile = 36;
        break; //Green
    case rn(54, 43):
        tile = 36;
        break; //Green
    case rn(53, 49):
        tile = 36;
        break; //Green
    case rn(54, 45):
        tile = 711;
        break; //Green (special)
    case rn(51, 48):
        tile = 711;
        break; //Green (special)

    case rn(50, 49):
        tile = 28;
        break; //Purple
    case rn(54, 44):
        tile = 28;
        break; //Purple
    case rn(49, 42):
        tile = 28;
        break; //Purple
    case rn(55, 43):
        tile = 28;
        break; //Purple
    case rn(54, 47):
        tile = 28;
        break; //Purple
    case rn(53, 48):
        tile = 28;
        break; //Purple

    case rn(51, 47):
        tile = 32;
        break; //Red
    case rn(52, 49):
        tile = 32;
        break; //Red
    case rn(48, 43):
        tile = 32;
        break; //Red
    case rn(55, 47):
        tile = 32;
        break; //Red
    case rn(54, 48):
        tile = 32;
        break; //Red
    default:
        return;
        break;
    }
}

void entclass::updatecolour(void)
{
    switch (size)
    {
    case 0: // Sprites
    case 3: // Big chunky pixels!
    case 4: // Small pickups
    case 7: // Teleporter
    case 9: // Really Big Sprite! (2x2)
    case 10: // 2x1 Sprite
    case 13: // Special for epilogue: huge hero!
        realcol = graphics.getcol(colour);
        break;
    case 5: // Horizontal gravity line
    case 6: // Vertical gravity line
        if (life == 0)
        {
            realcol = graphics.getcol(colour);
        }
        else
        {
            realcol = graphics.getcol(24);
        }
        break;
    case 11: // The fucking elephant
        if (game.noflashingmode)
        {
            realcol = graphics.getcol(22);
        }
        else
        {
            realcol = graphics.getcol(colour);
        }
        break;
    case 12: // Regular sprites that don't wrap
        // if we're outside the screen, we need to draw indicators
        if ((xp < -20 && vx > 0) || (xp > 340 && vx < 0))
        {
            realcol = graphics.getcol(23);
        }
        else
        {
            realcol = graphics.getcol(colour);
        }
    }
}

bool entclass::ishumanoid(void)
{
    return type == EntityType_PLAYER
        || type == EntityType_CREWMATE
        || type == EntityType_SUPERCREWMATE
        || type == EntityType_COLLECTABLE_CREWMATE;
}
