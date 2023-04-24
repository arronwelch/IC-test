    #include <iostream>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <string>
    #include <stdint.h> 
    
    using namespace std;
    typedef unsigned char  BYTE       ;
    typedef const unsigned char CBYTE ;
    typedef unsigned int   uint       ;    

	char   IC_LOGO[64];//IC logo string  
    
//-------------------CRC32 INIT---------->>>>--------------//    
    uint   POLYNOMIAL             = 0xEDB88320 ;//CRC32 polynomial
    int    have_table             = 0          ;
    int    have_crc32             = 0          ;
    uint   table[256]             ={0}         ;//CRC32 table
    uint   IC_LOGO_CRC32_UINT     ={0}         ;//IC logo string CRC unsigned int number
    BYTE   IC_LOGO_CRC32_BYTE [4] ={0}         ;//IC logo string CRC32 byte array
//-------------------CRC32 INIT----------<<<<--------------//


/* crc-8: x^8+x^2+x^1+x^0 0x107
 * polynomial 0x07
 * SIMPLE_CRC8_ALGORITHM
 * Width=8
 * 2020.1.30
 * NQ
 */
BYTE CRC8(BYTE AugmentedMessage)
{
  BYTE CRC_8_Remainder=0;
  int Width=8;
  while(Width--)
  {
  	CRC_8_Remainder <<= 1;
    if(AugmentedMessage & 0x80)
    	CRC_8_Remainder ^= 0x07;  //poly=0x07
    AugmentedMessage <<= 1;	
  }
  return CRC_8_Remainder;
}

/* CRC32 table function
 * 2020.1.30
 * NQ
 */
void make_table()
{
    int i, j;
    for (i = 0 ; i < 256 ; i++)
        for (j = 0, table[i] = i ; j < 8 ; j++)
            table[i] = (table[i]>>1)^((table[i]&1)?POLYNOMIAL:0) ;
}

/* SIMPLE_CRC32_ALGORITHM
 * 2020.1.30
 * NQ
 */
uint CRC32(char *buff)
{  
   if(0==have_table)
   {
   	make_table();
   	have_table = 1 ;
   }
   uint crc=~0;
   int len=strlen(buff);
   for (int i = 0; i < len; i++)
       crc = (crc >> 8) ^ table[(crc ^ buff[i]) & 0xff];
   return ~crc;
}

/* this is user function:
 * get IC name CRC32
 * 2020.1.30
 * NQ
 */
void calc_IC_LOGO_CRC32(void)
{              
	 if(0==have_crc32) 
	 {
	 	IC_LOGO_CRC32_UINT=CRC32(IC_LOGO);
	 	have_crc32=1;
	 }        	         

   for(int i=0;i<4;i++)
   {
     IC_LOGO_CRC32_BYTE[i]=(IC_LOGO_CRC32_UINT&(0xff000000>>(8*i)))>>(8*(3-i));
   }
}


int main(void)
{
	string input_str;
	string input_strc;
	char string[64];
	
	while(1)
	{
		cout<<"please ENTER IC LOGO:"<<endl;
		scanf("%s",&IC_LOGO);    
		input_str =IC_LOGO;
		input_strc = "exit";
		if(input_str.compare(input_strc) == 0) break;
	 
	    IC_LOGO_CRC32_UINT=CRC32(IC_LOGO);
	 
        for(int i=0;i<4;i++)
        {
          IC_LOGO_CRC32_BYTE[i]=(IC_LOGO_CRC32_UINT&(0xff000000>>(8*i)))>>(8*(3-i));
        }
	 
        itoa(IC_LOGO_CRC32_UINT,string,16);
        printf("0x%s\n",string);
						
        for(int i=0;i<4;i++)
        {
          itoa(IC_LOGO_CRC32_BYTE[i],string,10);
          cout<<string<<endl;
        }
	}
}
