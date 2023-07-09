//Preview Type:0:DVP Raw 10 bit// 1:Raw 8 bit// 2:YUV422// 3:RAW16
//Preview Type:4:RGB565// 5:Pixart SPI// 6:MIPI 10bit// 7:MIPI 12bit// 8: MTK SPI
//port  0:MIPI// 1:Parallel// 2:MTK// 3:SPI// 4:TEST// 5: HISPI// 6 : Z2P/Z4P
//I2C Mode    :0:Normal 8Addr,8Data//  1:Samsung 8 Addr,8Data// 2:Micron 8 Addr,16Data
//I2C Mode    :3:Stmicro 16Addr,8Data//4:Micron2 16 Addr,16Data
//Out Format  :0:YCbYCr/RG_GB// 1:YCrYCb/GR_BG// 2:CbYCrY/GB_RG// 3:CrYCbY/BG_GR
//MCLK Speed  :0:6M//1:8M//2:10M//3:11.4M//4:12M//5:12.5M//6:13.5M//7:15M//8:18M//9:24M
//pin  :BIT0 pwdn// BIT1:reset
//avdd  0:2.8V// 1:2.5V// 2:1.8V
//dovdd  0:2.8V// 1:2.5V// 2:1.8V
//dvdd  0:1.8V// 1:1.5V// 2:1.2V
/*
[DataBase]
DBName=DemoSens

[Vendor]
VendorName=SmartSens
I2C_CRC=0

[Sensor]
SensorName=SC101AP_raw
width=1280
height=720
port=1
type=2
pin=3
SlaveID=0xd0
mode=0
FlagReg=0xf7
FlagMask=0xff
FlagData=0xda
FlagReg1=0xf8
FlagMask1=0xff
FlagData1=0x4a
outformat=0
mclk=20
avdd=2.800000
dovdd=2.800000
dvdd=1.200000

Ext0=0
Ext1=0
Ext2=0
AFVCC=0.00
VPP=0.000000
*/
#include <stdint.h>

static const uint8_t sc101iot_default_init_regs[][2] = {
#if CONFIG_SC101IOT_720P_15FPS_ENABLED // 720P+YUV422+15FPS sensor default regs
/* Here are some test results:
#   size    xclk    fps    pic       pclk                       
#  ------- ------- ------ --------- ------- --- --- --- --- --- 
#   720p    4       3      err                                  
#   720p    8       5      normal    15                         
#   720p    10      7.8    normal    19                         
#   720p    20      15     warning   37.5                       
#   VGA     8       6      normal    
#   VGA     20      16     normal    

*/
    {0xf0, 0x30},
    {0x01, 0xff},
    {0x02, 0xe0},
    {0x30, 0x10},
    {0x3f, 0x81},
    {0xf0, 0x00},
    {0x70, 0x6b},
    {0x72, 0x30},
    {0x84, 0xb4},
    {0x8b, 0x00},
    {0x8c, 0x20},
    {0x8d, 0x02},
    {0x8e, 0xec},
    {0x9e, 0x10},
    {0xb0, 0xc1},
    {0xc8, 0x10},
    {0xc9, 0x10},
    {0xc6, 0x00},
    {0xe0, 0x0f},
    {0xb5, 0xf0},
    {0xde, 0x80},
    {0xb5, 0xf0},
    {0xde, 0x80},
    {0xb2, 0x50},
    {0xb3, 0xfc},
    {0xb4, 0x40},
    {0xb5, 0xc0},
    {0xb6, 0x50},
    {0xb7, 0xfc},
    {0xb8, 0x40},
    {0xb9, 0xc0},
    {0xba, 0xff},
    {0xbb, 0xcc},
    {0xbc, 0xa9},
    {0xbd, 0x7d},
    {0xc1, 0x77},
    {0xf0, 0x01},
    {0x70, 0x02},
    {0x71, 0x02},
    {0x72, 0x50},
    {0x73, 0x02},
    {0x74, 0xd2},
    {0x75, 0x20},
    {0x76, 0x81},
    {0x77, 0x8c},
    {0x78, 0x81},
    {0xf4, 0x01},
    {0xf5, 0x00},
    {0xf6, 0x00},
    {0xf0, 0x36},
    {0x40, 0x03},
    {0x41, 0x01},
    {0xf0, 0x39},
    {0x02, 0x70},
    {0xf0, 0x32},
    {0x41, 0x00},
    {0x43, 0x01},
    {0x48, 0x02},
    {0xf0, 0x45},
    {0x09, 0x20},
    {0xf0, 0x33},
    {0x33, 0x10},
    {0xf0, 0x30},
    {0x38, 0x44},
    {0xf0, 0x39},
    {0x07, 0x00},
    {0x08, 0x19},
    {0x47, 0x00},
    {0x48, 0x00},
    {0xf0, 0x37},
    {0x24, 0x31},
    {0xf0, 0x34},
    {0x9f, 0x02},
    {0xa6, 0x51},
    {0xa7, 0x57},
    {0xe8, 0x5f},
    {0xa8, 0x50},
    {0xa9, 0x50},
    {0xe9, 0x50},
    {0xf0, 0x33},
    {0xb3, 0x58},
    {0xb2, 0x78},
    {0xf0, 0x34},
    {0x9f, 0x03},
    {0xa6, 0x51},
    {0xa7, 0x57},
    {0xaa, 0x01},
    {0xab, 0x28},
    {0xac, 0x01},
    {0xad, 0x38},
    {0xf0, 0x33},
    {0x0a, 0x01},
    {0x0b, 0x28},
    {0xf0, 0x33},
    {0x64, 0x0f},
    {0xec, 0x51},
    {0xed, 0x57},
    {0x06, 0x58},
    {0xe9, 0x58},
    {0xeb, 0x68},
    {0xf0, 0x33},
    {0x64, 0x0f},
    {0xf0, 0x36},
    {0x70, 0xdf},
    {0xb6, 0x40},
    {0xb7, 0x51},
    {0xb8, 0x53},
    {0xb9, 0x57},
    {0xba, 0x5f},
    {0xb0, 0x84},
    {0xb1, 0x82},
    {0xb2, 0x84},
    {0xb3, 0x88},
    {0xb4, 0x90},
    {0xb5, 0x90},
    {0xf0, 0x36},
    {0x7e, 0x50},
    {0x7f, 0x51},
    {0x77, 0x81},
    {0x78, 0x86},
    {0x79, 0x89},
    {0xf0, 0x36},
    {0x70, 0xdf},
    {0x9c, 0x51},
    {0x9d, 0x57},
    {0x90, 0x54},
    {0x91, 0x54},
    {0x92, 0x56},
    {0xf0, 0x36},
    {0xa0, 0x51},
    {0xa1, 0x57},
    {0x96, 0x33},
    {0x97, 0x43},
    {0x98, 0x43},
    {0xf0, 0x36},
    {0x70, 0xdf},
    {0x7c, 0x40},
    {0x7d, 0x53},
    {0x74, 0xd0},
    {0x75, 0xf0},
    {0x76, 0xf0},
    {0xf0, 0x37},
    {0x0f, 0xd5},
    {0x7a, 0x40},
    {0x7b, 0x57},
    {0x71, 0x09},
    {0x72, 0x09},
    {0x73, 0x05},
    {0xf0, 0x33},
    {0x01, 0x44},
    {0xf0, 0x36},
    {0x37, 0xfb},
    {0xf0, 0x36},
    {0x3c, 0x0d},
    {0xf0, 0x33},
    {0x14, 0x95},
    {0xf0, 0x33},
    {0x8f, 0x80},
    {0xf0, 0x37},
    {0x27, 0x14},
    {0x28, 0x03},
    {0xf0, 0x36},
    {0x37, 0xf4},
    {0xf0, 0x33},
    {0x01, 0x44},
    {0xf0, 0x36},
    {0x79, 0x89},
    {0xf0, 0x34},
    {0xac, 0x01},
    {0xad, 0x40},
    {0xf0, 0x33},
    {0xeb, 0x70},
    {0xf0, 0x34},
    {0xa8, 0x50},
    {0xa9, 0x50},
    {0xf0, 0x33},
    {0xb3, 0x58},
    {0xf0, 0x36},
    {0x11, 0x80},
    {0xf0, 0x36},
    {0x41, 0x51},
    {0xf0, 0x3f},
    {0x03, 0x09},	  
    {0xf0, 0x32},
    {0x0c, 0x06},
    {0x0d, 0x82},
    {0x0e, 0x02},
    {0x0f, 0xee},
    {0xf0, 0x36},
    {0xea, 0x09},
    {0xeb, 0xf5},
    {0xec, 0x11},
    {0xed, 0x27},
    {0xe9, 0x20},
#endif
};
