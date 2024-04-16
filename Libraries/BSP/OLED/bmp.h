

#ifndef __BMP_H
#define __BMP_H
//battery 22*16
#define battery_charging_bmp_sizex 12
#define battery_charging_bmp_sizey 8
const unsigned char battery_charging_bmp[] =
{
	0x00,0x3C,0x7E,0x42,0x5A,0x4A,0x52,0x5A,0x42,0x42,0x7E,0x00
};

//battery 22*16
#define battery_low_bmp_sizex 12
#define battery_low_bmp_sizey 8
const unsigned char battery_low_bmp[] =
{
	0x00,0x3C,0x7E,0x42,0x42,0x42,0x42,0x42,0x7E,0x7E,0x7E,0x00
};

//battery 22*16
#define battery_mid_bmp_sizex 12
#define battery_mid_bmp_sizey 8
const unsigned char battery_mid_bmp[] =
{
	0x00,0x3C,0x7E,0x42,0x42,0x42,0x7E,0x7E,0x7E,0x7E,0x7E,0x00
};

//battery 22*16
#define battery_high_bmp_sizex 12
#define battery_high_bmp_sizey 8
const unsigned char battery_high_bmp[] =
{
	0x00,0x3C,0x7E,0x42,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x00
};

//battery 22*16
#define battery_full_bmp_sizex 12
#define battery_full_bmp_sizey 8
const unsigned char battery_full_bmp[] =
{
	0x00,0x3C,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x00
};

//volume 8*16
#define volume_bmp_sizex 8
#define volume_bmp_sizey 8
const unsigned char volume_bmp[] =
{
	0x00,0x3C,0x3C,0x7E,0xFF,0x00,0x00,0x00
};

//silence 11*16
#define silence_bmp_sizex 8
#define silence_bmp_sizey 8
const unsigned char silence_bmp[] =
{
	0x80,0x7C,0x3C,0x7E,0xFF,0x04,0x02,0x01
};

//signal 20*16
#define signal_bmp_sizex 14
#define signal_bmp_sizey 8
const unsigned char signal_bmp[] =
{
	0xF0,0xF0,0x00,0xF8,0xF8,0x00,0xFC,0xFC,0x00,0xFE,0xFE,0x00,0xFF,0xFF
};

#define no_signal_bmp_sizex 14
#define no_signal_bmp_sizey 8
const unsigned char no_signal_bmp[]=
{0xC0,0xCA,0x04,0xFA,0xF0,0x00,0xFC,0xFC,0x00,0xFE,0xFE,0x00,0xFF,0xFF};
#endif


