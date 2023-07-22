


#ifndef CALCULATOR_H_
#define CALCULATOR_H_

typedef enum{
	NOINP,
	NUM,
	OPERATOR,
	EQUAL,
	RESULT,
	DELETE
	}CALCULATOR_Input_t;

void CALCULATOR_Init(void);


CALCULATOR_Input_t CALCULATOR_GetInput(u8 *num);
void CALCULATOR_UI(CALCULATOR_Input_t chr,s16 input);
s32 CALCULATOR_Calc(u8 op,s16 num1,s16 num2);

void CALCULATOR_APP(void);




#endif /* CALCULATOR_H_ */