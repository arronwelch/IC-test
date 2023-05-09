#include <stdio.h>

const unsigned int crc15Table[256] = {  
  0x0, 0xc599, 0xceab, 0xb32, 0xd8cf, 0x1d56, 0x1664, 0xd3fd, 0xf407, 0x319e, 0x3aac,
  0xff35, 0x2cc8, 0xe951, 0xe263, 0x27fa, 0xad97, 0x680e, 0x633c, 0xa6a5, 0x7558, 0xb0c1,
  0xbbf3, 0x7e6a, 0x5990, 0x9c09, 0x973b, 0x52a2, 0x815f, 0x44c6, 0x4ff4, 0x8a6d, 0x5b2e,
  0x9eb7, 0x9585, 0x501c, 0x83e1, 0x4678, 0x4d4a, 0x88d3, 0xaf29, 0x6ab0, 0x6182, 0xa41b,
  0x77e6, 0xb27f, 0xb94d, 0x7cd4, 0xf6b9, 0x3320, 0x3812, 0xfd8b, 0x2e76, 0xebef, 0xe0dd,
  0x2544, 0x2be, 0xc727, 0xcc15, 0x98c, 0xda71, 0x1fe8, 0x14da, 0xd143, 0xf3c5, 0x365c,
  0x3d6e, 0xf8f7, 0x2b0a, 0xee93, 0xe5a1, 0x2038, 0x7c2, 0xc25b, 0xc969, 0xcf0, 0xdf0d,
  0x1a94, 0x11a6, 0xd43f, 0x5e52, 0x9bcb, 0x90f9, 0x5560, 0x869d, 0x4304, 0x4836, 0x8daf,
  0xaa55, 0x6fcc, 0x64fe, 0xa167, 0x729a, 0xb703, 0xbc31, 0x79a8, 0xa8eb, 0x6d72, 0x6640,
  0xa3d9, 0x7024, 0xb5bd, 0xbe8f, 0x7b16, 0x5cec, 0x9975, 0x9247, 0x57de, 0x8423, 0x41ba,
  0x4a88, 0x8f11, 0x57c, 0xc0e5, 0xcbd7, 0xe4e, 0xddb3, 0x182a, 0x1318, 0xd681, 0xf17b,
  0x34e2, 0x3fd0, 0xfa49, 0x29b4, 0xec2d, 0xe71f, 0x2286, 0xa213, 0x678a, 0x6cb8, 0xa921,
  0x7adc, 0xbf45, 0xb477, 0x71ee, 0x5614, 0x938d, 0x98bf, 0x5d26, 0x8edb, 0x4b42, 0x4070,
  0x85e9, 0xf84, 0xca1d, 0xc12f, 0x4b6, 0xd74b, 0x12d2, 0x19e0, 0xdc79, 0xfb83, 0x3e1a, 0x3528,
  0xf0b1, 0x234c, 0xe6d5, 0xede7, 0x287e, 0xf93d, 0x3ca4, 0x3796, 0xf20f, 0x21f2, 0xe46b, 0xef59,
  0x2ac0, 0xd3a, 0xc8a3, 0xc391, 0x608, 0xd5f5, 0x106c, 0x1b5e, 0xdec7, 0x54aa, 0x9133, 0x9a01,
  0x5f98, 0x8c65, 0x49fc, 0x42ce, 0x8757, 0xa0ad, 0x6534, 0x6e06, 0xab9f, 0x7862, 0xbdfb, 0xb6c9,
  0x7350, 0x51d6, 0x944f, 0x9f7d, 0x5ae4, 0x8919, 0x4c80, 0x47b2, 0x822b, 0xa5d1, 0x6048, 0x6b7a,
  0xaee3, 0x7d1e, 0xb887, 0xb3b5, 0x762c, 0xfc41, 0x39d8, 0x32ea, 0xf773, 0x248e, 0xe117, 0xea25,
  0x2fbc, 0x846, 0xcddf, 0xc6ed, 0x374, 0xd089, 0x1510, 0x1e22, 0xdbbb, 0xaf8, 0xcf61, 0xc453,
  0x1ca, 0xd237, 0x17ae, 0x1c9c, 0xd905, 0xfeff, 0x3b66, 0x3054, 0xf5cd, 0x2630, 0xe3a9, 0xe89b,
  0x2d02, 0xa76f, 0x62f6, 0x69c4, 0xac5d, 0x7fa0, 0xba39, 0xb10b, 0x7492, 0x5368, 0x96f1, 0x9dc3,
  0x585a, 0x8ba7, 0x4e3e, 0x450c, 0x8095
};

//GTE PEC 
unsigned int LTC_pec15_calc(unsigned int len, unsigned char *data) 
{
  unsigned int remainder = 0;
  unsigned int addr = 0;

  remainder = 16;  /* initialize the PEC */
  for (unsigned int i = 0; i < len; i++) {  /* loops for each byte in data array */

    addr = ((remainder>>7)^data[i])&0xff;  /* calculate PEC table address */
    remainder = (remainder<<8)^crc15Table[addr];
  }
  return(remainder*2);  /* The CRC15 has a 0 in the LSB so the remainder must be multiplied by 2 */
}

//GTE ECC
unsigned char ECC_calc(unsigned int data)
{
  unsigned char databit[16];
  unsigned char datatemp = 0;
  unsigned char p0 = 0;
  unsigned char p1 = 0;
  unsigned char p2 = 0;
  unsigned char p3 = 0;
  unsigned char p4 = 0;
  unsigned char p5 = 0;
  for (int i=0;i<16;i++)
  {
    datatemp = (data>>i)&0x01;
    databit[i] = datatemp;
  }
  p0 = databit[0]+databit[1]+databit[3]+databit[4]+databit[6]+databit[8]+databit[10]+databit[11]+databit[13]+databit[15];
  p0 = p0&0x01;
  p1 = databit[0]+databit[2]+databit[3]+databit[5]+databit[6]+databit[9]+databit[10]+databit[12]+databit[13];
  p1 = p1&0x01;
  p2 = databit[1]+databit[2]+databit[3]+databit[7]+databit[8]+databit[9]+databit[10]+databit[14]+databit[15];
  p2 = p2&0x01;
  p3 = databit[4]+databit[5]+databit[6]+databit[7]+databit[8]+databit[9]+databit[10];
  p3 = p3&0x01;
  p4 = databit[11]+databit[12]+databit[13]+databit[14]+databit[15];
  p4 = p4&0x01;
  p5 = databit[0]+databit[1]+databit[2]+databit[3]+databit[4]+databit[5]+databit[6]+databit[7]+databit[8]+databit[9]+databit[10]+databit[11]+databit[12]+databit[13]+databit[14]+databit[15]+p0+p1+p2+p3+p4;
  p5 = p5&0x01;
  unsigned char res = (p5<<5)+(p4<<4)+(p3<<3)+(p2<<2)+(p1<<1)+p0;
  return (res&0x3f);
}

int main()
{
	unsigned int input = 0;
	unsigned int ecc = 0;
	unsigned char data[6] = {0}; // 48-bit data

// calculate 48'{16'h[data] + 8'h[ecc]} + 16'h[ecc]
//	printf("Please enter source data(16bit) of ecc:\n");
//	scanf("%x", &input);
//	ecc = ECC_calc(input);
//	printf("ECC(16'h%#x) = 6'h%#x\n", input, ecc);
//
//	// MTP is 22bit = data(16bit) + ecc(6bit)
//	data[0] =  input       & 0xFF;	// 8bit
//	data[1] = (input >> 8) & 0xFF;	// 8bit
//	data[2] =  ecc;			// 6bit
//	printf("PEC(22'h%#x%x) = 16'h%#x\n", ecc, input, 0xFFFF & LTC_pec15_calc(6, data));

	// calculate 16'CMD(Big-endian,MSB) + 16'PEC(MSB) + 48'DATA(Little-endian,MSB) + 16'PEC(MSB)
	printf("16'CMD(Big-endian,MSB) + 16'PEC(MSB) + 48'DATA(Little-endian,MSB) + 16'PEC(MSB)\n");

	// 6 bytes is Little-endian to calculate PEC
	unsigned char data0[6] = {0x91, 0x0d, 0x07, 0x76, 0xf2, 0x35}; //48'h35f276070d91
	unsigned char data1[6] = {0x44, 0x12, 0xa3, 0xe8, 0x09, 0x79}; //48'h7909e8a31244
	unsigned char data2[6] = {0xa5, 0xe7, 0x3c, 0xc3, 0x1a, 0xa1}; //48'hallac33ce7a5

	// 2 bytes is Big-endian to calculate PEC
	unsigned char data3[2] = {0x00, 0xa5}; //16'h00a5

	printf("PEC(48'h35f276070d91) = 16'h%#x\n", 0xFFFF & LTC_pec15_calc(6, data0));
	printf("PEC(48'h7909e8a31244) = 16'h%#x\n", 0xFFFF & LTC_pec15_calc(6, data1));
	printf("PEC(48'hallac33ce7a5) = 16'h%#x\n", 0xFFFF & LTC_pec15_calc(6, data2));
	printf("PEC(16'ha5) = 16'h%#x\n", 0xFFFF & LTC_pec15_calc(2, data3));

	return 0;
}
