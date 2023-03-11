#include "tetromino_manager.h"

void simulate_tetrominos(void)
{
   /*
    * You don't need to break each module too finely.
    * If it's sequential, one person(process) can do many things.
    */

   /*
    *
    * A: who generates blocks and push it to the que until MAX_QUEUE_SIZE be FULL.
    *
    * B: who spawns the tetrominos from que then ask A for a next tetromino.
    *   (would be a manager in this module)
    * 
    * C: who reads input value from user(by keyboard) and then give someone(may be D?) the value.
    * 
    * D: who changes the position value of tetromino every cycle.
    *    1. from the moment it comes out on skyline(starting point), the tetromino falls down at a constant rate. 
    *    2. D should change the position when user's input comes. 
    *    3. If tetromino touches the floor (or others), ask B for a new tetromino.
    *    4. If tetromino stopped on the skyline, send a game over message to B.
    * 
    * E: who draw the spawned tetrominos's current position to the game screen every cycle.
    */
}
