//Displays numbers and characters on a 7-segment display <Both for common cathode and common anode>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


#define MASK(X) (1<<X)

enum character {zero,one,two,three,four,five,six,seven,eight,nine,a,b,c,d,e,f,h,s,g,y};
void common_anode(register uint8_t* reg, enum character ch);
void clear_reg(register uint8_t* reg);
void common_cathode(register uint8_t* reg, enum character ch);
void clear_reg(register uint8_t* reg);
void set_bit(register uint8_t* reg,int pos);
void toggle_reg(register uint8_t* reg);

void print_bits(int x);//delete soon

int main()
{
	register uint8_t* reg;
	uint8_t k = (uint8_t)0x00;
	reg = &k;

	for(int i=zero; i<=y;i++)
	{
		printf("%d ... \n",i);
		common_anode(reg, i);
		print_bits(*reg);
		common_cathode(reg, i);
		print_bits(*reg);
	}

	return 0;
}

/*displays character for active high*/
void common_anode(register uint8_t* reg, enum character ch)
{
	clear_reg(reg);
	switch(ch)
	{
		case zero:
			set_bit(reg, 4);
			set_bit(reg, 5);
			set_bit(reg, 6);
		case seven:
			set_bit(reg, 1);
			set_bit(reg, 2);
			set_bit(reg, 3);
			break;
		case d:
			set_bit(reg, 4);
			set_bit(reg, 5);
			set_bit(reg, 7);
		case one:
			set_bit(reg, 2);
			set_bit(reg, 3);
			break;
		case two:
			set_bit(reg, 1);
			set_bit(reg, 2);
			set_bit(reg, 7);
			set_bit(reg, 5);
			set_bit(reg, 4);
			break;
		case eight:
			set_bit(reg, 5);
			set_bit(reg, 6);
		case three:
			set_bit(reg, 1);
			set_bit(reg, 2);
			set_bit(reg, 7);
			set_bit(reg, 3);
			set_bit(reg, 4);
			break;
		case y:
			set_bit(reg, 4);
		case four:
			set_bit(reg, 6);
			set_bit(reg, 7);
			set_bit(reg, 2);
			set_bit(reg, 3);
			break;
		case g:
		case nine:
			set_bit(reg, 2);
		case five:
		case s:
			set_bit(reg, 1);
			set_bit(reg, 6);
			set_bit(reg, 7);
			set_bit(reg, 3);
			set_bit(reg, 5);
			break;	
		case a:
			set_bit(reg, 1);
		case h:
			set_bit(reg, 2);
			set_bit(reg, 3);
			set_bit(reg, 5);
			set_bit(reg, 6);
			set_bit(reg, 7);
			break;
		case six:
			set_bit(reg, 3);
		case e:
			set_bit(reg, 4);
		case f:
			set_bit(reg, 1);
			set_bit(reg, 6);
			set_bit(reg, 7);
			set_bit(reg, 5);
			break;
		case b:
			set_bit(reg, 3);
			set_bit(reg, 4);
			set_bit(reg, 5);
			set_bit(reg, 6);
			set_bit(reg, 7);
			break;
		case c:
			set_bit(reg, 1);
			set_bit(reg, 4);
			set_bit(reg, 5);
			set_bit(reg, 6);
			break;
		default:
			clear_reg(reg);
	}
}

/*Display characters for active low*/
void common_cathode(register uint8_t* reg, enum character ch)
{
	common_anode(reg, ch);
	toggle_reg(reg);
}

/*Clears all bits to 0*/
void clear_reg(register uint8_t* reg)
{
	/*clearing the bits*/
	*reg&=0x00;
}

/*sets a bit at position pos to 1*/
void set_bit(register uint8_t* reg,int pos)
{
	*reg|=MASK(pos);
}

/*toggles all bits in the register*/
void toggle_reg(register uint8_t* reg)
{
	*reg^=0xFF;
}


/*prints integer as bits and hex*/
void print_bits(int x)
{
	printf("Register state: [binary => ",x);
	for(int i=7; i>=0; i--)
	{
		if((i+1)%4==0)printf(" ");
		if(x & MASK(i)){
			printf("1");
		}
		else
		{
			printf("0");
		}
	}
	printf("]\t[hex => 0x%X]\n",x,x);
}