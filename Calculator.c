
#include "StdTypes.h"
#include "KeyPad_Interface.h"
#include "LCD_Interface.h"
#include "Calculator.h"

void CALCULATOR_Init(void)
{
	
}

CALCULATOR_Input_t CALCULATOR_GetInput(u8 *num)
{
	u8 input;
	CALCULATOR_Input_t status = NOINP;
	
	input = KEYPAD_GetKey();
	if (input!=NO_KEY)
	{
		if (input>='0' && input<='9')
		{
			*num = input - '0';
			status = NUM;
		}
		else if (input == '=')
		{
			status = EQUAL;
		}
		else if (input == 'C')
		{
			*num=input;
			status = DELETE;
		}
		else
		{
			*num=input;
			status = OPERATOR;
		}
	}
	return status;
}
void CALCULATOR_UI(CALCULATOR_Input_t chr,s16 input)
{
	if (chr == NUM)
	{
		input=input+'0';
		LCD_WriteChar(input);
	}
	else if (chr == OPERATOR || chr == EQUAL)
	{
		LCD_WriteChar(' ');
		LCD_WriteChar(input);
		LCD_WriteChar(' ');
	}
	else if (chr == RESULT)
	{
		LCD_ClearPosition(line2,0,15);
		LCD_GoTo(line2,0);
		LCD_WriteNumber(input);
		LCD_GoTo(line1,0);
	}
	else if (chr == DELETE)
	{
		if (input==0)
		{
			LCD_ClearPosition(line1,0,15);
			LCD_GoTo(line1,0);
		}
		else
		{
			LCD_Clear();
		}
		
	}
}
s32 CALCULATOR_Calc(u8 op,s16 num1,s16 num2)
{
	s32 result=0; 
	switch(op)
	{
		case '+':
		result = (s32)num1 + (s32)num2;
		break;
		case '-':
		result = (s32)num1 - (s32)num2;
		break;
		case '*':
		result = (s32)num1 * (s32)num2;
		break;
		case '/':
		result = (s32)num1 / (s32)num2;
		break;
	}
	
	return result;
}

void CALCULATOR_APP(void)
{
	s16 num1=0,num2=0;
	u8 op='+',tempnum,num1_flag=0,negnum1_flag=0,negnum2_flag=0,e_flag=0;
	s8 op_flag=-1;
	s16 result=0;
	CALCULATOR_Input_t key;
	key=CALCULATOR_GetInput(&tempnum);
	while(tempnum!='C')
	{
		
		if ((key==NUM || key==OPERATOR)&&(e_flag==1))
		{
			CALCULATOR_UI(DELETE,0);
		}
		if (key==NUM)
		{
			if (num1_flag==0)
			{
				e_flag=0;
				op_flag=0;
				num1=(num1*10) + tempnum;
				CALCULATOR_UI(NUM,tempnum);
			}
			else
			{
				num2=(num2*10) + tempnum;
				CALCULATOR_UI(NUM,tempnum);
			}
		}
		else if (key==OPERATOR)
		{
			if (tempnum=='-')
			{
				if(op_flag==1)
				{
					negnum2_flag=1;
					CALCULATOR_UI(key,tempnum);
					op_flag=2;
				}
				else if (op_flag==-1)
				{
					negnum1_flag=1;
					CALCULATOR_UI(key,tempnum);
					op_flag=2;
				}
			}
			
			if (op_flag==0)
			{
				op=tempnum;
				num1_flag=1;
				if (e_flag==1)
				{
					num1=result;
					LCD_WriteNumber(num1);
				}
				CALCULATOR_UI(key,op);
				op_flag=1;
				e_flag=0;
			}
		}
		else if (key==EQUAL)
		{
			CALCULATOR_UI(key,'=');
			if (negnum2_flag==1)
			{
				num2*=-1;
				negnum2_flag=0;
			}
			if (negnum1_flag==1)
			{
				num1*=-1;
				negnum1_flag=0;
			}
			result=CALCULATOR_Calc(op,num1,num2);
			CALCULATOR_UI(RESULT,result);
			
			num1=0;
			num2=0;
			e_flag=1;
			num1_flag=0;
			op_flag=0;
		}
		key=CALCULATOR_GetInput(&tempnum);
	}
	CALCULATOR_UI(DELETE,1);
	
}
