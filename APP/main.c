/*
 * main.c
 *
 *  Created on: Sep 28, 2021
 *      Author: Mark
 */
#include"../HAL/KeyPad_Handler_V1/KeyPad_int.h"
#include"../HAL/LCD_handler_v1/LCD_int.h"
#include"../HAL/LCD_handler_v1/LCD_Functions.h"
#include"util/delay.h"
#include"../MCAL/DIO_V1/DIO_int.h"
#define NO_KEY_PRESSED 255

void main()
{
	/*Initializations*/
	DIO_u8setPortDir(PORT_B,0x03);
	LCD_vidinit();
	KEYPAD_vidInit();
	/*Screen intro glitch*/
	LCD_u8goTo(0,4);
	LCD_vidwriteString("Mark Ehab");
	_delay_ms(30);
	LCD_vidclearDisplay();
	LCD_u8goTo(0,4);
	LCD_vidwriteString("bahE karM");
	_delay_ms(30);
	LCD_vidclearDisplay();
	LCD_u8goTo(0,4);
	LCD_vidwriteString("Mark Ehab");
	_delay_ms(1000);
	LCD_u8goTo(1,4);
	LCD_vidwriteString("Safe_Lock");
	_delay_ms(30);
	LCD_u8goTo(1,4);
	LCD_vidwriteString("kcoL_efaS");
	_delay_ms(30);
	LCD_u8goTo(1,4);
	LCD_vidwriteString("Safe_Lock");
	_delay_ms(1000);
	LCD_vidclearDisplay();
	/*Variables declaration*/
	LCD_vidbeginAtFirstLine();
	LCD_viddisplayOnCursorOn();
	u8 Local_u8Keypressed;
	u8 correct_pass[16]={9,8,9,5}; // Default Password
	u8 Local_u8ScreenCounter=0;
	u8 Local_u8PassMatchFlag=0;
	u8 Local_u8NewPassMatchFlag=1;
	u8 Local_u8TrialsNum=0;
	u8 password_organize[16];
	u8 password_reorganize[16];
	u8 Local_u8PassLength=0;
	Local_u8Keypressed = NO_KEY_PRESSED;
	while(1)
	{
		LCD_vidwriteString("Enter Password:");
		LCD_vidbeginAtSecondLine();
		//Enter the password
		while(Local_u8Keypressed!='E')
		{
			Local_u8Keypressed = KEYPAD_u8GetPressed();
			if(Local_u8Keypressed != NO_KEY_PRESSED)
			{
				if(Local_u8Keypressed<=9 || Local_u8Keypressed == '*' || Local_u8Keypressed == '#')
				{
					LCD_vidwriteCharacter('*');
					password_organize[Local_u8PassLength]=Local_u8Keypressed;
					Local_u8PassLength++;
				}
				else
				{
					switch(Local_u8Keypressed)
					{
					case 'E':
						LCD_vidclearDisplay();
						break;
					case 'C':
						Local_u8PassLength=0;
						LCD_vidclearDisplay();
						LCD_vidwriteString("Enter Password:");
						LCD_vidbeginAtSecondLine();
						break;
					case 'D':
						LCD_vidshiftLeftCursor();
						LCD_vidwriteCharacter(' ');
						LCD_vidshiftLeftCursor();
						password_organize[Local_u8PassLength]='0';
						Local_u8PassLength--;
						break;
					default:
						Local_u8Keypressed=NO_KEY_PRESSED;
					}
				}
			}
		}
		Local_u8Keypressed=NO_KEY_PRESSED;
		for(u8 char_counter = 0 ; char_counter<Local_u8PassLength ; char_counter++ )
		{
			if(correct_pass[char_counter]==password_organize[char_counter])
			{
				Local_u8PassMatchFlag=0;
			}
			else
			{
				Local_u8PassMatchFlag=1;
				break;
			}
		}
		Local_u8PassLength=0;
		if(Local_u8PassMatchFlag == 0)
		{
			DIO_u8setPinVal(PORT_B,PIN_1,LOW);
			DIO_u8setPinVal(PORT_B,PIN_0,HIGH);
			Local_u8TrialsNum=0;
			LCD_u8goTo(0,4);
			LCD_vidwriteString("WELCOME !");
			_delay_ms(2000);
			LCD_vidclearDisplay();
			LCD_vidwriteString("Press #");
			LCD_u8goTo(1,0);
			LCD_vidwriteString("For New Pass");
			_delay_ms(1000);
			LCD_vidclearDisplay();
			LCD_vidwriteString("OR Press C");
			LCD_u8goTo(1,0);
			LCD_vidwriteString("To Back");
			_delay_ms(1000);
			LCD_vidclearDisplay();
			while(Local_u8Keypressed != '#' && Local_u8Keypressed != 'C')
			{
				Local_u8Keypressed = KEYPAD_u8GetPressed();
			}
			if(Local_u8Keypressed=='#')
			{
				LCD_vidwriteString("New Password:");
				LCD_vidbeginAtSecondLine();
				while(Local_u8Keypressed!='E')
				{
					Local_u8Keypressed = KEYPAD_u8GetPressed();
					if(Local_u8Keypressed != NO_KEY_PRESSED)
					{
						if(Local_u8Keypressed<=9 || Local_u8Keypressed == '*' || Local_u8Keypressed == '#')
						{
							LCD_vidwriteCharacter('*');
							password_organize[Local_u8PassLength]=Local_u8Keypressed;
							Local_u8PassLength++;
						}
						else
						{
							switch(Local_u8Keypressed)
							{
							case 'E':
								LCD_vidclearDisplay();
								Local_u8PassLength=0;
								break;
							case 'C':
								Local_u8PassLength=0;
								LCD_vidclearDisplay();
								LCD_vidwriteString("New Password:");
								LCD_vidbeginAtSecondLine();
								break;
							case 'D':
								LCD_vidshiftLeftCursor();
								LCD_vidwriteCharacter(' ');
								LCD_vidshiftLeftCursor();
								password_organize[Local_u8PassLength]='0';
								Local_u8PassLength--;
								break;
							default:
								Local_u8Keypressed=NO_KEY_PRESSED;
							}
						}
					}
				}
				Local_u8Keypressed=NO_KEY_PRESSED;
				while(Local_u8NewPassMatchFlag != 0)
				{
					Local_u8PassLength=0;
					LCD_vidwriteString("Re-enter Pass:");
					LCD_vidbeginAtSecondLine();
					while(Local_u8Keypressed!='E')
					{
						Local_u8Keypressed = KEYPAD_u8GetPressed();
						if(Local_u8Keypressed != NO_KEY_PRESSED)
						{
							if(Local_u8Keypressed<=9 || Local_u8Keypressed == '*' || Local_u8Keypressed == '#')
							{
								LCD_vidwriteCharacter('*');
								password_reorganize[Local_u8PassLength]=Local_u8Keypressed;
								Local_u8PassLength++;
							}
							else
							{
								switch(Local_u8Keypressed)
								{
								case 'E':
									LCD_vidclearDisplay();
									break;
								case 'C':
									Local_u8PassLength=0;
									LCD_vidclearDisplay();
									LCD_vidwriteString("Re-enter Password:");
									LCD_vidbeginAtSecondLine();
									break;
								case 'D':
									LCD_vidshiftLeftCursor();
									LCD_vidwriteCharacter(' ');
									LCD_vidshiftLeftCursor();
									password_organize[Local_u8PassLength]='0';
									Local_u8PassLength--;
									break;
								default:
									Local_u8Keypressed=NO_KEY_PRESSED;
								}
							}
						}
					}
					Local_u8Keypressed=NO_KEY_PRESSED;
					for(u8 char_counter = 0 ; char_counter<Local_u8PassLength ; char_counter++ )
					{
						if(password_reorganize[char_counter]==password_organize[char_counter])
						{
							Local_u8NewPassMatchFlag=0;
						}
						else
						{
							Local_u8NewPassMatchFlag=1;
							break;
						}
					}
					if(Local_u8NewPassMatchFlag==1)
					{
						LCD_vidwriteString("No Matching");
						LCD_u8goTo(1,0);
						LCD_vidwriteString("Please try again");
						_delay_ms(1000);
						LCD_vidclearDisplay();
					}
				}
				Local_u8NewPassMatchFlag=1;
				for(u8 char_counter = 0 ; char_counter<Local_u8PassLength ; char_counter++ )
				{
					correct_pass[char_counter]=password_organize[char_counter];
				}
				DIO_u8setPinVal(PORT_B,PIN_0,LOW);
				LCD_vidwriteString("Pass Changed !");
				_delay_ms(1000);
				LCD_vidclearDisplay();
			}
		}
		else
		{
			DIO_u8setPinVal(PORT_B,PIN_1,HIGH);
			Local_u8TrialsNum++;
			LCD_vidwriteString("Wrong Password ! ");
			_delay_ms(1000);
			LCD_vidclearDisplay();
			LCD_u8goTo(0,4);
			LCD_vidwriteString("Trial No : ");
			LCD_vidwriteNumber(Local_u8TrialsNum);
			LCD_u8goTo(1,2);
			LCD_vidwriteString("Trials Left:");
			LCD_vidwriteNumber(3-Local_u8TrialsNum);
			LCD_vidwriteCharacter('!');
			_delay_ms(2000);
			LCD_vidclearDisplay();
		}
		if(Local_u8TrialsNum == 3)
		{
			LCD_vidclearDisplay();
			LCD_viddisplayOnCursorOff();
			LCD_vidwriteString("SAFE IS LOCKED!");
			while(1)
			{
				DIO_u8setPinVal(PORT_B,PIN_2,HIGH);
				_delay_ms(200);
				DIO_u8setPinVal(PORT_B,PIN_2,LOW);
				_delay_ms(200);
			}
		}
	}
}



