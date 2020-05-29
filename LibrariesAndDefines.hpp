#ifndef _LibrariesAndDefines_
#define _LibrariesAndDefines_

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "rsdl.hpp"
#include <math.h>


#define LL long long int
#define FIELD_RUNNERS "FIELD RUNNERS"
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define BLANK ""
#define EMPTY {}
#define ZERO_POINT_NINE 0.9
#define ZERO_POINT_ONE 0.1
#define SEND_ENEMY_PERIOD 500
#define TIME_OUT 3000
#define BASE_HEALTH 20
#define BASE_MONEY 200
#define WINDOW_HEIGHT 1024
#define WINDOW_WIDTH 1365
#define BACKGROUND_IMG_PATH "Assets/background.png"
#define RUNNER_IN_INPUT 0
#define STUBBORN_IN_INPUT 1
#define SUPERTROOPER_IN_INPUT 2
#define SCRAMBLER_IN_INPUT 3
#define HALF_SECOND 500
#define SQUARE_LENGTH 60
#define TOP_LEFT_X 121
#define TOP_LEFT_Y 173
#define SPACE ' '
#define PATH_IN_DATA 0
#define DELAY_TIME 25
#define GET_TIME chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count()
#define MAP_HEIGHT_SQUARES 11
#define MAP_WIDTH_SQUARES 19
#define OUT_POINT Point(-1,-1)
#define MAX_LEVEL 3
#define INF 1e5
#define HUNDRED 100.0
#define THOUSAND 1000.0
#define BULLET_RAD 4
#define LIVES "LIVES : "
#define LIVES_POINT Point(150,100)
#define FONT_PATH "Assets/OpenSans.ttf"
#define TEXT_SIZE 25
#define MONEY "MONEY : "
#define MONEY_POINT Point(380,100)
#define WIN "YOU WIN"
#define LOOSE "YOU LOOSE"
#define LOOSE_MSG_POINT Point(360,400)
#define WIN_MSG_POINT Point(425,400)
#define END_MSG_SIZE 120
#define ALIVE 0
#define SHOULD_LOOT 1
#define LOOTED 2
#define LOST_MUSIC "Assets/lost.mp3"
#define WIN_MUSIC "Assets/win.mp3"
#define BACKGROUND_MUSIC "Assets/background_music.mp3"
#define RUN_MUSIC "Assets/run.mp3"
#define GOLD RGB(251,229,8)
#define GATTLING_KEY 'g'
#define MISILE_KEY 'm'
#define TESLA_KEY 't'
#define GLUE_KEY 'l'
#define UPGRADE_KEY 'u'
#define GATTLING_NUMBER 0
#define MISILE_NUMBER 1
#define TESLA_NUMBER 2
#define GLUE_NUMBER 3
#define SHOOTING_RANGE 150
#define ENEMIES "Assets/enemies/"
#define BUILDINGS "Assets/towers/"
#define PNG ".png"
#define MP3 ".mp3"
#define UP "0"
#define RIGHT "1"
#define DOWN "2"
#define LEFT "3"
#define PIC_MODES 4
#define CHANGE_PIC_FRAME 4
#define STRAIT_ANGLE 180.0
#define PI 3.1415
#define COMPLETE_ANGLE 360.0
#define RIGHT_ANGLE 90.0
#define REFLEX_ANGLE 270.0
#define ANGLE_DIFFERENCE 22.5
#define MID_ANGLE 45.0
#define DIE "die"
#define SOUND "_sound.mp3"
#define ASSETS "Assets/"
#define SHOT "shot"
#define SILVER RGB(170, 169, 173)
#define UPGRADE_IMG "Assets/upgrade.png"
#define START_IMG "Assets/start.jpg"
#define START_MUSIC "Assets/startmusic.wav"
#define START_MASAGE "PRESS ANY KEY TO BEGIN ..."
#define START_MASAGE_POINT Point(450,130)
#define START_MASAGE_SIZE 40
#define ROUND "ROUND : "
#define SLASH " / "
#define ROUND_POINT Point(650,100)

#define GATTLING_BASE_DAMAGE 35
#define GATTLING_SHOT_PERIOD 1000
#define GATTLING_DAMAGE_RAD 0
#define GATTLING_BUILD_COST 55
#define GATTLING_UPGRADE_COST 40
#define GATTLING_UPGRADE_DAMAGE 35
#define GATTLING1_IMG_PATH "Assets/towers/gattling10.png"
#define GATTLING2_IMG_PATH "Assets/towers/gattling20.png"
#define GATTLING3_IMG_PATH "Assets/towers/gattling30.png"
#define GATTLING "gattling"
#define GATTLING_BULLET_SPEED 18
#define GATTLING_BULLET_COLOR BLACK

#define MISILE_BASE_DAMAGE 75
#define MISILE_SHOT_PERIOD 3000
#define MISILE_DAMAGE_RAD 50
#define MISILE_BUILD_COST 70 
#define MISILE_UPGRADE_COST 60
#define MISILE_UPGRADE_DAMAGE 75
#define MISILE1_IMG_PATH "Assets/towers/missile10.png"
#define MISILE2_IMG_PATH "Assets/towers/missile20.png"
#define MISILE3_IMG_PATH "Assets/towers/missile30.png"
#define MISILE "missile"
#define MISILE_BULLET_SPEED 15
#define MISILE_BULLET_COLOR RED

#define TESLA_BASE_DAMAGE 700
#define TESLA_SHOT_PERIOD 1500
#define TESLA_DAMAGE_RAD 0
#define TESLA_BUILD_COST 120
#define TESLA_UPGRADE_COST 100
#define TESLA_UPGRADE_DAMAGE 1000
#define TESLA1_IMG_PATH "Assets/towers/tesla10.png"
#define TESLA2_IMG_PATH "Assets/towers/tesla20.png"
#define TESLA3_IMG_PATH "Assets/towers/tesla30.png"
#define TESLA "tesla"
#define TESLA_BULLET_SPEED 20
#define TESLA_BULLET_COLOR BLUE

#define GLUE_BASE_PERCENT 40
#define GLUE_SHOT_PERIOD 2000
#define GLUE_DAMAGE_RAD 30
#define GLUE_INFECTION_TIME 2500
#define GLUE_BUILD_COST 60
#define GLUE_UPGRADE_COST 45
#define GLUE_UPGRADE_PERCENT 10
#define GLUE_UPGRADE_INFECTION_TIME 500
#define GLUE1_IMG_PATH "Assets/towers/glue10.png"
#define GLUE2_IMG_PATH "Assets/towers/glue20.png"
#define GLUE3_IMG_PATH "Assets/towers/glue30.png"
#define GLUE "glue"
#define GLUE_BULLET_SPEED 15
#define GLUE_BULLET_COLOR GREEN

#define RUNNER_NUMBER 0
#define STUBBORN_NUMBER 1
#define SUPER_TROOPER_NUMBER 2
#define SCRAMBLER_NUMBER 3

#define RUNNER_BASE_HEALTH 250
#define RUNNER_SPEED 50
#define RUNNER_PRICE 6
#define RUNNER_DAMAGE 1
#define RUNNER_IMG_PATH "Assets/enemies/runner00.png"
#define RUNNER_PIC_SIZE 30
#define RUNNER "runner"

#define STUBBORN_BASE_HEALTH 400
#define STUBBORN_SPEED 30
#define STUBBORN_PRICE 10
#define STUBBORN_DAMAGE 4
#define STUBBORN_IMG_PATH "Assets/enemies/stubborn-runner00.png"
#define STUBBORN_PIC_SIZE 40
#define STUBBORN "stubborn-runner"

#define SUPER_TROOPER_BASE_HEALTH 500
#define SUPER_TROOPER_SPEED 25
#define SUPER_TROOPER_PRICE 8
#define SUPER_TROOPER_DAMAGE 4
#define SUPER_TROOPER_IMG_PATH "Assets/enemies/supertrooper00.png"
#define SUPER_TROOPER_PIC_SIZE 50
#define SUPER_TROOPER "supertrooper"

#define SCRAMBLER_BASE_HEALTH 100
#define SCRAMBLER_SPEED 90
#define SCRAMBLER_PRICE 4
#define SCRAMBLER_DAMAGE 2
#define SCRAMBLER_IMG_PATH "Assets/enemies/scrambler00.png"
#define SCRAMBLER_PIC_SIZE 50
#define SCRAMBLER "scrambler"

#define TOWER_TYPE_TEXT "Tower Type"
#define GATTLING_IMG "Assets/towers/gattling.png"
#define MISILE_IMG "Assets/towers/missile.png"
#define TESLA_IMG "Assets/towers/tesla.png"
#define GLUE_IMG "Assets/towers/glue.png"
#define TOWER_TYPE_POINT Point(650,850);
#define TOWER_OPTION_RECT Rectangle(835, 850, 60, 60);
#define PICS_DISTANCE 100
#define FIVE 5

#define BUILD_COST_TEXT "Build Cost"
#define BUILD_COST_POINT Point(650, 900)
#define TEXTS_DISTANCE 100

#define UPGRADE_COST_TEXT "Upgrade Cost"
#define UPGRADE_COST_POINT Point(650, 950)


#endif
