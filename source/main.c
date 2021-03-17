/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <time.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


void ADC_init() {
ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn(){

TCCR1B = 0x0B;

OCR1A = 125;

TIMSK1 = 0x02;

TCNT1 = 0;

_avr_timer_cntcurr = _avr_timer_M;

SREG |= 0x80;

}

void TimerOff(){
	TCCR1B = 0x00;
}

void TimerISR(){
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect){
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0){
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M){
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}
// Pins on PORTA are used as input for A2D conversion
	//    The default channel is 0 (PA0)
	// The value of pinNum determines the pin on PORTA
	//    used for A2D conversion
	// Valid values range between 0 and 7, where the value
	//    represents the desired pin for A2D conversion
void Set_A2D_Pin(unsigned char pinNum) {
	ADMUX = (pinNum <= 0x07) ? pinNum : ADMUX;
	// Allow channel to stabilize
	static unsigned char i = 0;
	for ( i=0; i<15; i++ ) { asm("nop"); }
}



unsigned char pattern = 0x00;//0x80;
unsigned char row = 0x00;
unsigned char arr1[3] = {0x80,0x80,0x80};
unsigned char arr[5] = {0xFE,0xFD,0xFB,0xF7,0xEF};

unsigned char p1 = 0x00;
unsigned char r1 = 0x00;
unsigned char arr3[3] = {0x01,0x01,0x01};
unsigned char arr2[5] = {0xFE,0xFD,0xFB,0xF7,0xEF};


unsigned char left = 2;
unsigned char right = 2;
unsigned char temp = 1;
unsigned char temp1 = 2;
unsigned char temp2 = 3;

enum dis{a,b,c}state;
enum dis1{a1,a2,a3}s;
enum joy{start,wait,up,down,but1,but2}move;
enum but{up1,down1,wait1}m;
enum movement{st,wa,ups,downs,but3,but4}j;

unsigned short vak = 0x00;
unsigned char flag = 1;
unsigned char flag1 = 1;
//unsigned char glo = 0;
//unsigned char glo1 = 0;
unsigned char d = 0x00;
unsigned char u = 0x00;
//unsigned char ball = 0x08;
unsigned char glo = 1;
unsigned short ele = 0x00;
unsigned char checker = 1;

unsigned char sec = 1;
unsigned char sec1 = 2;
unsigned char sec2 = 3;



void bots(){
	int ra;
	ra = rand() % 3 + 1;
	if (ra == 1){
	
	}
	else if (ra == 2){

	}
	else if (ra == 3){

	}
}


void secondplayer(){
	Set_A2D_Pin(0x02);
	ele = ADC;
	switch (j){
	case st:
		j = wa;
		break;
	case wa: // 150 = down 700 = up
		if (ele > 700 && checker != 0){
		j = ups;
		}
		else if ( ele < 150 && checker != 2){
		j = downs;
		}
		else{
		j = wa;
		}
		break;
	case ups:
		if (checker == 2){
		sec = 1;
		sec1 = 2;
		sec2 = 3;
		checker--;
		j = but3;
		}
		else if (checker == 1){
		sec = 0;
		sec1 = 1;
		sec2 = 2;
		checker--;
		j = but3;
		}
		else if (checker == 0){
		j = wa;
		}
		break;
	case downs:
		if (checker == 1){
		sec = 2;
		sec1 = 3;
		sec2 = 4;
		checker++;
		j = but4;
		}
		else if (checker == 0){
		sec = 1;
		sec1 = 2;
		sec2 = 3;
		checker++;
		j = but4;
		}
		else if (checker == 2){
		j = wa;
		}
		break;
	case but3:
		if (ele > 700){
		j = but3;
		}
		else {
		j = wa;
		}
		break;
	case but4:
		if (ele < 150){
		j = but4;

		}
		else{
		j = wa;
		}
		break;

	default:
		j = st;
	}

}





void joystick(){
	
	d = ~PINA & 0x01;
	u = ~PINA & 0x02;
	switch(move){
		case start:
			move = wait;
			break;
		case wait:
			if (u){
				move = up;
			}
			else if (d){
				move = down;
			}
			else{
				move = wait;
			}
			break;
		case up:
		if (glo == 2){
			
			temp = 1;
			temp1 = 2;
			temp2 = 3;
			move = but1;
			}
		else if (glo == 1){
			temp = 0;
			temp1 = 1;
			temp2 = 2;
		move = but1;
		break;
		}
		
		else if (glo == 0){
		move = wait;
		}
			break;
		case down:

		 if (glo == 1){
		temp = 2;
		temp1 = 3;
		temp2 = 4;
		move = but2;
		break;
		}
		else if (glo == 0){
		temp = 1;
		temp1 = 2;
		temp2 = 3;
		move = but2;
		}	
		else if (glo == 2)
		move = wait;
			break;

		case but1:
			if (u){
			move = but1;
			}
			else if (!u){
				glo--;
			move = wait;
			}
			break;
		case but2:
			if (d){
			move = but2;
			}
			else if (!d){
				glo++;
			move = wait;
			}
		default:

			move = start;
	}
}
void led(){
	switch(state){
		case a:
			pattern = arr1[0];
			row = arr[temp];
			state = b;
		break;
		case b:
			pattern = arr1[1];
			row = arr[temp1];
			state = c;
		break;
		case c:
			pattern = arr1[2];
			row = arr[temp2];
			state = a;
			break;
	default:
		state = a;
	}
	PORTC = pattern;
	PORTD = row;

}

void show(){
//	TimerSet(1);
	switch(s){

		case a1:
			p1 = arr3[0];
			r1 = arr2[sec];
			s = a2;
			break;
		case a2:
			p1 = arr3[1];
			r1 = arr2[sec1];
			s = a3;
			break;
		case a3:
			p1 = arr3[2];
			r1 = arr2[sec2];
			s = a1;
			break;
		default:
			s = a1;
			break;
	}
	PORTC = p1;
	PORTD = r1;
}
unsigned char ballrow = 0xFB;//middlerow
unsigned char ballchecker = 0x04;
unsigned char ball = 0x08;
unsigned char test = 0x10;
unsigned char test1 = 0xBF;
//unsigned long balltime = 0x00;
unsigned char ballrowarr[5] = {0xFE,0xFD,0xFB,0xF7,0xEF};
unsigned char ballcol[6] = {0x02,0x04,0x08,0x10,0x20,0x40};
unsigned char col = 0x00;
unsigned char r = 0x00;
unsigned char itrow = 2;
unsigned char itcol = 2;
unsigned char bound = 2;
unsigned char ybounce = 0;
unsigned char top = 0;
unsigned char bot = 0;
enum balls{startball,bounce,bounce1,bounce2,bounce3,bounce4,bounce5,bounce6,bounce7,bounce8,bouncecheck,rightcheck,bounce9,bounce10,bounce11,bounce12,bounce13,reset} bal;
void ballm(){
	switch(bal){
	case startball:
		top = 0;
		bot = 0;
		ybounce = 0;
		itrow = 2;
		itcol = 2;
		bound = 2;
		bal = bounce;
		break;
	case bounce:
			r = ballrowarr[itrow];
			col = ballcol[itcol];
			itcol++;//3
			bal = bounce1;

		break;

	case bounce1:
		r = ballrowarr[itrow];
		col = ballcol[itcol];
		itcol++;//4
		bal = bounce2;
		break;
	case bounce2:
		r = ballrowarr[itrow];
		col = ballcol[itcol];
		itcol++;//5
		bal = bounce3;
		break;
	case bounce3:
		r = ballrowarr[itrow];
		col = ballcol[itcol];
		bal = bouncecheck;
		break;

	case bouncecheck:
		if (ballrowarr[itrow] == arr[temp1]){//middle
		top = 0;
		bot = 0;
		ybounce = 0;
		itcol--;
		bal = bounce4;
		}
		else if (ballrowarr[itrow] == arr[temp]){//top
		bot = 0;
		top = 1;
		ybounce = 1;
		bound--;
		itcol--;
		itrow--;
		bal = bounce4;
		}
		else if (ballrowarr[itrow] == arr[temp2]){//bottom
		top = 0;
		bot = 1;
		ybounce = 1;
		bound++;
		itcol--;
		itrow++;
		bal = bounce4;

		}
		else{
			bal = reset;
		}
		break;
	case bounce4:
		if (bound == 2 && ybounce == 0){
		
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		itcol--;
		bal = bounce5;
		}
		else if ( top == 1 && ybounce != 0){//moving up
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		bound--;
		itcol--;
		itrow--;
		bal = bounce5;
		}
		else if (bound == 0){//top down
		top = 0;
		bot = 1;
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		bound++;
		itcol--;
		itrow++;
		bal = bounce5;
		}
		else if (bot == 1 && ybounce != 0){
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		bound++;
		itcol--;
		itrow++;
		bal = bounce5;

		}

		break;
	case bounce5:
		if (bound == 2 && ybounce == 0){
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		itcol--;
		bal = bounce6;
		}
		else if (top == 1 && ybounce != 0 && bound != 0){
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		bound--;
		itcol--;
		itrow--;
		bal = bounce6;
		}
		else if (bound == 0 && ybounce != 0){
		top = 0;
		bot = 1;
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		bound++;
		itcol--;
		itrow++;
		bal = bounce6;
		}
		else if (bot == 1 && ybounce != 0 && bound != 4){
		
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		bound++;
		itcol--;
		itrow++;
		bal = bounce6;
		}
		else if (bound == 4 && ybounce!= 0){
		top = 1;
		bot = 0;
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		bound--;
		itcol--;
		itrow--;
		bal = bounce6;
		}
		break;
	case bounce6:
		if (bound == 2 && ybounce == 0){
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		itcol--;
		bal = bounce7;
		}
		else if (top == 1 && ybounce != 0 && bound != 0){
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		bound--;
		itcol--;
		itrow--;
		bal = bounce7;
		}
		else if (bound == 0 && ybounce != 0){
		top = 0;
		bot = 1;
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		bound++;
		itcol--;
		itrow++;
		bal = bounce7;
		}
		else if (bot == 1 && ybounce != 0 && bound != 4){
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		bound++;
		itcol--;
		itrow++;
		bal = bounce7;
		}
		else if (bound == 4 && ybounce != 0){
		top = 1;
		bot = 0;
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		bound--;
		itcol--;
		itrow--;
		bal = bounce7;
		}



		break;
	case bounce7:
		if (bound == 2 && ybounce == 0){
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		itcol--;
		bal = bounce8;
		}
		else if (bot == 1 && ybounce != 0){
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		bound++;
		itcol--;
		itrow++;
		bal = bounce8;
		}
		else if (top == 1 && ybounce != 0){
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		bound--;
		itcol--;
		itrow--;
		bal = bounce8;
		}
		break;
	case bounce8:
		if(bound == 2 && ybounce == 0){
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		itcol--;
		bal = rightcheck;
		}
		else if (bot == 1 && ybounce != 0){
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		bound++;
		itcol--;
		itrow++;
		bal = rightcheck;
		}
		else if (top == 1 && ybounce !=0){
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		bound--;
		itcol--;
		itrow++;
		bal = rightcheck;

		}
		break;
	case rightcheck:
		if (ballrowarr[itrow] == arr2[sec1]){
		itcol = 0;
		ybounce = 0;
		bal = bounce9;
		}
		else if (ballrowarr[itrow] == arr2[sec]){//top
		top = 1;
		bot = 0;
		itcol = 0;
		ybounce = 1;
		bound--;
		bal = bounce9;
		}
		/*
		else if (ballrowarr[itrow] == arr2[sec2]){//bot
		itcol = 1;
		bot = 1;
		top = 0;
		ybounce = 1;
		bound = 2;
		bound++;
		bal = bounce10;
		}
		*/
		else{
		bal = reset;
		}
		break;
	case bounce9:
		if (ybounce == 0){
			if(itcol !=5){
		++itcol;
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		bal = bounce9;
			}
			else{
			bal = bouncecheck;
			}
		}
		else if (top == 1){
			if( bound != 0 ){
			--itrow;	
			++itcol;
			--bound;
			top = 1;
			ybounce = 1;
			col = ballcol[itcol];
			r = ballrowarr[itrow];
			bal = bounce9;
			}
			else if (itcol == 5){
			bal = reset;
			}
			else if (bound == 0){
			bal = reset;
			}
		}
		/*
		else if (top == 1 && ybounce!= 0){
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		bound--;
		itcol++;
		itrow--;
		bal = bounce10;
		}
		else if (bound == 0){
		top = 0;
		bot = 1;
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		bound++;
		itcol++;
		itrow++;
		bal = bounce10;
		}
		else if (bot == 1 && ybounce != 0){
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		bound++;
		itcol++;
		itrow++;
		bal = bounce10;

		}
		*/
		break;
		
	case bounce10:
	//	itcol++;
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		itcol++;
		bal = bounce10;
	break;
	/*
	case bounce11:
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		itcol++;
		bal = bounce12;
		break;
	case bounce12:
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		itcol++;
		bal = bounce13;
		break;
	case bounce13:
		col = ballcol[itcol];
		r = ballrowarr[itrow];
		itcol++;
		bal = bouncecheck;
		break;
		*/
	case reset:
		bal = startball;
		break;
	default:
		bal = startball;
		break;
	}





	PORTC = col;
	PORTD = r;
}





int main(void) {
    /* Insert DDR and PORT initializations */
DDRA = 0x00; PORTA = 0xFF;
DDRB = 0x00; PORTB = 0xFF;
DDRC = 0xFF; PORTC = 0x00;
DDRD = 0xFF; PORTD = 0x00;
unsigned long balltime = 0;
unsigned long con = 0;
ADC_init();
TimerOn();
srand(time(NULL));


TimerSet(1);

    while (1) {
	
	show();
	led();
	joystick();
	if (con >= 5000){
	secondplayer();
	con = 0;
	}
	if(balltime >= 8000){
	ballm();
	balltime = 0;
	}
   while(!TimerFlag);
    TimerFlag = 0;
    balltime+=10;
    con+=10;
    }
    return 1;
}
