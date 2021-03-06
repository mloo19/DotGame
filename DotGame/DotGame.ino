/*
  DotGame.ino
  Marisa Loo
 
 Example file using the The Meggy Jr Simplified Library (MJSL)
  from the Meggy Jr RGB library for Arduino
   
 Blink a damned LED.
   
   
 
 Version 1.25 - 12/2/2008
 Copyright (c) 2008 Windell H. Oskay.  All right reserved.
 http://www.evilmadscientist.com/
 
 This library is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this library.  If not, see <http://www.gnu.org/licenses/>.
     
 */

 
 
 
 

/*
 * Adapted from "Blink,"  The basic Arduino example.  
 * http://www.arduino.cc/en/Tutorial/Blink
 */

#include <MeggyJrSimple.h>    // Required code, line 1 of 2.

int x;
int y;
int wallx;
int wally;
int holey = random(8);
boolean passed = false;
int loops;

void setup()                    // run once, when the sketch starts
{
  MeggyJrSimpleSetup();      // Required code, line 2 of 2.
  x = 0;
  y = 4;
  wallx = 7;
}

void loop()
{
  wall();
  hole();
  Die();
  drawPlayer();
  pass();
  DisplaySlate();
  ClearSlate();
  movePlayer();
  loops++;
  if (loops % 600 == 0)
  {
    ClearSlate();
    updateWall();
    DisplaySlate();
  }
}

void drawPlayer()
{
  DrawPx(x, y, Red);
}

void movePlayer()
{
  CheckButtonsPress();
  if (Button_Up)
  {
    if (y < 7)
    {
      y++;
    }
  }
  if (Button_Down)
  {
    if (y > 0)
    {
      y--;
    }
  }
}

void wall()
{
  for (wally = 0; wally < 8; wally++)
  {
    DrawPx(wallx, wally, Green);
  }
  if (wallx == -1)
  {
    wallx = 7;
  }
}

void hole()
{
  DrawPx(wallx, holey, Dark);
}

void updateWall()
{
  wallx = wallx - 1;
}

void pass()
{
  if (x == wallx && y == holey)
  {
    passed = true;
    Tone_Start(ToneA3, 50);
  }
  else
  {
    passed = false;
  }
  if (passed == true)
  {
    holey = random(8);
  }
}

void Die()
{
  if (x == wallx && y != holey)
  {
    ClearSlate();
    x = 0;
    y = 4;
    wallx = 7;
    DisplaySlate();
    Tone_Start(ToneF3, 50);
  }
}
