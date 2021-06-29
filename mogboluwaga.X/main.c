/*
 * File:   main.c
 * Author: Emmanuel Olateju
 *
 * Created on 10 June 2021, 20:44
 */


#include <xc.h>
// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF         // Data EEPROM Memory Code Protection bit (Data EEPROM code-protected)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF          // Flash Program Memory Code Protection bit (All program memory code-protected)

#define _XTAL_FREQ 20000000
#include "LCDLIBRARY1.h"

int A_value,B_value;

void main(void) {
    ADCON1=0xC2;
    ADCON0=0xC1;
    TRISA=0xFF;
    TRISB=0x00;
    TRISC=0x00;
    TRISD=0x00;
    PORTB=PORTC=PORTD=0x00;
    config();
    CLRDISP();
    CURSOR(FIRSTROW,1);
    LCDWRITE("SOURCE SELECTOR");
    
    while(1){
        ADCON0bits.CHS=0;
         __delay_us(20);
        ADCON0bits.GO_nDONE=1;
        while(ADCON0bits.GO_nDONE);
        A_value=(ADRESH<<8)+ADRESL;
        __delay_us(100);

        ADCON0bits.CHS=1;
         __delay_us(20);
        ADCON0bits.GO_nDONE=1;
        while(ADCON0bits.GO_nDONE);
        B_value=(ADRESH<<8)+ADRESL;
        __delay_us(100);
        
        if(B_value>910){
            RB4=0;RB5=1;
            CURSOR(SECONDROW,1);
            LCDWRITE("INVERTER");
            LCDWRITE(" ");
        }else if(A_value>910){
            RB4=1;RB5=0;
            CURSOR(SECONDROW,1);
            LCDWRITE("AC SOURCE");
        }else{
            RB4=0;RB5=0;
            CURSOR(SECONDROW,1);
            LCDWRITE("NO SOURCE");
        }
    }
    return;
}
