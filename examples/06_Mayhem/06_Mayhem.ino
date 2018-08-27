/*
 MIT License

Copyright (c) 2018 Phil Bowles <esparto8266@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
 *    Demonstrates usage of the Esparto timer libarary for common functions
 *    
 *    based on exampl 03_chaining, need to see that first.
 *    
 *      - randomTimes function calls function at fixed interval, but only a random number of times
 *      - randomTimesRandom function calls function a random number of times at random intervals
 *    
 */
#include <ESPArto.h>
ESPArto  Esparto;

void setupHardware() {
  static uint32_t simple;
  static uint32_t counter;
  
  Serial.begin(74880);
  Esparto.Output(LED_BUILTIN,LOW,HIGH);
  Esparto.flashLED(250);                                  // flash LED rapidly on/off every 250 ms (4x per second)

  ESPARTO_STD_FN  jackson5=[](){                          // make a function object we can use later
    Serial.print("The Jackson 5 sang: ");
    Esparto.nTimes(3,1500,[]()
      {
      static char c=0x41;
      Serial.printf("%c ",c++);       // run 3 times...A B C
      },
      []()                            // and then... chain function
        {
        Serial.print("\nIt's easy as: ");
        Esparto.nTimes(3,1500,[](){
          static int n=1;
          Serial.printf("%d ",n++);     // 1 2 3
          },                          // and then... chain function
          []()
            {
            Serial.print("\n...That's how easy it can be!\n");
            Esparto.once(5000,[](){ Serial.println("have a listen to the real thing: https://www.youtube.com/watch?v=ho7796-au8U"); });
            } // end 123 chain function
        ); // end 123 function
        } // end abc chain function
      ); // end "ABC" function
  }; // end fn declaration
//  sing it...some time in the future
  Esparto.randomTimes(1,5,30000,jackson5); // do it between 1 and 5 times (at least 30 seconds apart
  Esparto.randomTimesRandom(2,4,15000,35000,jackson5); // this is certain to overlap with the previous causing mayhem
  Esparto.nTimesRandom(2,20000,40000,[](){ Serial.printf("This could be the last time...\n"); },[](){ Serial.printf("Baby the last time, I don't know\n");});
}
