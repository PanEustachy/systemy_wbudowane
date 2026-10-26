#include <targets\AT91SAM7.h>
#include "pcf8833u8_lcd.h"

#define LCD_BACKLIGHT PIOB_SODR_P20
#define AUDIO_OUT PIOB_SODR_P19

#define SW_1 PIOB_SODR_P24
#define SW_2 PIOB_SODR_P25

#define JOY_LEFT PIOA_SODR_P7 
#define JOY_DOWN PIOA_SODR_P8
#define JOY_UP PIOA_SODR_P9
#define JOY_RIGHT PIOA_SODR_P14
#define JOY_ENTER PIOA_SODR_P15

enum Mode{
  MENU,
  MOVE
 };

void toggleMode(enum Mode* m){
  if (*m == MENU)  {*m=MOVE; return;}
  else *m = MENU;
  return;
}


int main (){
PMC_PCER=PMC_PCER_PIOB;
PIOB_OER=LCD_BACKLIGHT | AUDIO_OUT;
PIOB_PER=LCD_BACKLIGHT | AUDIO_OUT;


PMC_PCER=PMC_PCER_PIOA;

enum Mode mode = MENU;

InitLCD();
LCDSettings();
LCDClearScreen();
PIOB_SODR|=LCD_BACKLIGHT;
LCDPutStr("test",20,20,LARGE,WHITE,BLACK);

unsigned int x=60,y=60;


while(1) {

  switch(mode){
    case MENU:
      
      
      
  if ((PIOB_PDSR & SW_1)==0)
  {
    PIOB_SODR|= LCD_BACKLIGHT; 

    Delaya(500);

    PIOB_CODR|= AUDIO_OUT;
    Delaya(1);

    LCDClearScreen();
    LCDPutStr("SW_1",100,20,LARGE,RED,BLACK) ;
 }

  if ((PIOB_PDSR & SW_2)==0) {
    PIOB_CODR|= LCD_BACKLIGHT;

    Delaya(700);

    PIOB_CODR|= AUDIO_OUT;

    
    LCDClearScreen();
    LCDPutStr("SW_2",100,80,LARGE,RED,BLACK) ;
   }

    if ((PIOA_PDSR & JOY_LEFT)==0) {

      LCDClearScreen();
      LCDPutStr("left",60,20,LARGE,WHITE,BLACK) ;
   }

   
    if ((PIOA_PDSR & JOY_RIGHT)==0) {
      LCDClearScreen();
      LCDPutStr("right",60,80,LARGE,WHITE,BLACK) ;
   }

    if ((PIOA_PDSR & JOY_UP)==0) {
      LCDClearScreen();
      LCDPutStr("up",20,60,LARGE,WHITE,BLACK) ;
   }


    if ((PIOA_PDSR & JOY_DOWN)==0) {
      LCDClearScreen();
      LCDPutStr("down",100,50,LARGE,WHITE,BLACK) ;
   }
      
      
      break;
    case MOVE:
      
   if ((PIOA_PDSR & JOY_LEFT)==0) {

      y-=10;
   }

   
    if ((PIOA_PDSR & JOY_RIGHT)==0) {
      y+=10;
   }

    if ((PIOA_PDSR & JOY_UP)==0) {
      x-=10;
   }


    if ((PIOA_PDSR & JOY_DOWN)==0) {
      x+=10;
      }
      LCDClearScreen();

            LCDPutStr("X",x,y,LARGE,WHITE,BLACK) ;

      
      break;  
    default:
      break;
  }



   
    if ((PIOA_PDSR & JOY_ENTER)==0) {
      toggleMode(&mode);
      }


}

}