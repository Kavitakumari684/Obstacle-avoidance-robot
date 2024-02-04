#include<reg51.h>
#include<string.h>

//for motor
sbit motor1_a = P0^0;
sbit motor1_b = P0^1;
sbit motor2_a = P0^2;
sbit motor2_b = P0^3;

//for sensors
sbit frontIR = P1^0;
sbit rightIR = P1^1;
sbit leftIR  = P1^2;
sbit backwardIR = P1^3;

// for lcd interfacing
void lcdcmd( char ch);
void lcddata( char ch);
void lcdstr(unsigned char  *str);
sbit rs = P3^0;
sbit en = P3^1;

#define lcd P2

void delay (void);


void main()
{
	// FOR LCD
	lcdcmd(0x38);
	lcdcmd(0x0c);
	lcdcmd(0x80);
	lcdstr("avoid obstacle ");
	
	// sensor
	
	frontIR = 0;
	rightIR =0;
	leftIR =0;
	backwardIR =0;
	
	lcdcmd(0x01);
	lcdcmd(0x80);

	
	while(1)
	{   //front obstacle and bacward obstacle  , then stop movement
		if(frontIR == 1 && rightIR == 0 && leftIR == 0 && backwardIR == 1 )
		{
			motor1_a = 0;
      motor1_b = 0;
      motor2_a = 0;
      motor2_b = 0;
			
			lcdcmd(0xc0);
			lcdstr(" Bacward/forward");
			delay();
			lcdcmd(0x01);
			lcdstr("STOP vehicle ");
			lcdcmd(0x01);
		}
		
	
			//forward obstacle
		
	else if(frontIR == 1 && rightIR == 0 && leftIR == 0 && backwardIR == 0)
		{
			motor1_a = 0;
      motor1_b = 1;
      motor2_a = 0;
      motor2_b = 1;
			
			lcdcmd(0x80);
			lcdstr("STOP IN");
	    
	
			lcdcmd(0xc0);
			lcdstr(" Forward SIDE");
			delay();
			lcdcmd(0x01);
		
			lcdstr("Move Backward");
			lcdcmd(0x01);
		}
		
			
		//right obstacle
		else if(frontIR == 0 && rightIR == 1 && leftIR == 0 && backwardIR == 0)
		{
			motor1_a = 0;
      motor1_b = 1;
      motor2_a = 1;
      motor2_b = 0;
			lcdcmd(0x80);
			lcdstr("STOP IN");
			
			lcdcmd(0xc0);
			lcdstr(" RIGHT SIDE");
			delay();
			lcdcmd(0x01);
			
			lcdstr("Move Left");
			lcdcmd(0x01);
		}
		
		
		//left obstacle
		else if(frontIR == 0 && rightIR == 0 && leftIR == 1 && backwardIR == 0)
		{
			motor1_a = 1;
      motor1_b = 0;
      motor2_a = 0;
      motor2_b = 1;
				
			lcdcmd(0x80);
			lcdstr("STOP IN");
			
			lcdcmd(0xc0);
			lcdstr(" LEFT SIDE");
			delay();
			lcdcmd(0x01);
			lcdstr("Move Right");
			lcdcmd(0x01);
			
		}
		
		
		//bacward direction
		else if(frontIR == 0 && rightIR == 0 && leftIR == 0 && backwardIR == 1)
		{
			motor1_a = 1;
      motor1_b = 0;
      motor2_a = 1;
      motor2_b = 0;
				
			lcdcmd(0x80);
			lcdstr("STOP IN");
			
			lcdcmd(0xc0);
			lcdstr(" BACKWARD");
			delay();
			lcdcmd(0x01);
			lcdstr("Move Forward");
			lcdcmd(0x01);
		}
		
		
		//no obstacle move forward
		else
		{
			motor1_a = 1;
      motor1_b = 0;
      motor2_a = 1;
      motor2_b = 0;
			lcdcmd(0x80);
			lcdstr("KEEP GOING");
			lcdcmd(0xc0);
		}
		
	}
}

void lcdcmd(char ch)
{
	lcd = ch ;
	rs = 0;
	en = 1;
	delay();
	en =0 ;
}

void lcddata(char ch)
{
	lcd = ch ;
	rs = 1;
	en = 1;
	delay();
	en = 0;
}

void lcdstr(unsigned char  *str)
{
	unsigned int loop;
	for(loop = 0 ; str[loop] != '\0' ; loop++)
	{
	lcddata(str[loop]);
	}
}

void delay(void)
{
	TMOD = 0x01;
	TL0  = 0xFE ;
	TH0  = 0x4B ;
	TR0 = 1;
	while(TF0 == 0);
	TR0 = 0;
	TF0 =0;
}
	
	


	
		
			

