#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tlv.h"
#include "hashtable.h"
#include "emvTagList.h"



int main(){
	/*Se hace un test con la cadena hexadecimal 6F1A840E315041592E5359532E4444463031A5088801025F2D02656E
	cuyo significado es el siguiente:
	6F(File Control Information(FCI) Template)
		1A
		84(Dedicated File(DF) Name)
			0E -len
			315041592E5359532E4444463031 - value(1PAY.SYS.DDF01 en hexa)
		A5(File Control information(FCI) Propietary template)
		08-len
			88(Short File Identifier(SFI))
				01- len
				02 -value
			5F2D(language preference)
				02-len
				656E-value
	*/

	dict_t *dict[HASHSIZE];
	memset(dict, 0, sizeof(dict));
	emvInit(dict);
//	displayTable(dict);

	/*unsigned char test[] = {0x6F,0x1A,0x84,0x0E,0x31,0x50,0x41,0x59,0x2E,0x53,0x59,
							0x53,0x2E,0x44,0x44,0x46,0x30,0x31,0xA5,0x08,0x88,0x01,
							0x02,0x5F,0x2D,0x02,0x65,0x6E,
							0x6F,0x1A,0x84,0x0E,0x31,0x50,0x41,0x59,0x2E,0x53,0x59,
							0x53,0x2E,0x44,0x44,0x46,0x30,0x31,0xA5,0x08,0x88,0x01,
							0x02,0x5F,0x2D,0x02,0x65,0x6E};
*/

		unsigned char test[] = {0x9F,0x02,0x06,0x00,0x00,0x00,0x00,0x07,0x77,0x9F,0x03,
								0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x9F,0x26,0x08,0x2C,
								0x7F,0xC4,0x3E,0x05,0x8E,0x4A,0xE5,0x5F,0x24,0x03,0x17,
								0x12,0x31,0x82,0x02,0x19,0x80,0x50,0x0A,0x4D,0x41,0x53,
								0x54,0x45,0x52,0x43,0x41,0x52,0x44,0x5A,0x08,0x54,0x13,
								0x33,0x00,0x90,0x00,0x02,0x18,0x5F,0x34,0x01,0x00,0x9F,
								0x36,0x02,0x09,0x6F,0x9F,0x09,0x02,0x00,0x02,0x9F,0x27,
								0x01,0x40,0x9F,0x34,0x03,0x1F,0x03,0x02,0x84,0x07,0xA0,
								0x00,0x00,0x00,0x04,0x10,0x10,0x9F,0x1E,0x08,0x00,0x01,
								0x02,0x03,0x04,0x05,0x06,0x07,0x9F,0x10,0x12,0x01,0x10,
								0x90,0x40,0x03,0x22,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
								0x19,0x76,0x66,0xA1,0xFF,0x9F,0x33,0x03,0x00,0x08,0x08,
								0x9F,0x1A,0x02,0x08,0x26,0x9F,0x35,0x01,0x22,0x95,0x05,
								0x00,0x00,0x00,0x00,0x00,0x57,0x11,0x54,0x13,0x33,0x00,
								0x90,0x00,0x02,0x18,0xD1,0x71,0x22,0x01,0x90,0x42,0x60,
								0x00,0x0F,0x5F,0x2A,0x02,0x08,0x26,0x9A,0x03,0x16,0x07,
								0x05,0x9C,0x01,0x00,0x9F,0x37,0x04,0x6D,0x00,0xB4,0x51};


	//unsigned char test[] = {0x9F, 0x35, 0x00}; //consulta de tag
//	unsigned short size = sizeof(test)/sizeof(test[0]);
//	tlvInfo_t *t=malloc(sizeof(tlvInfo_t)*size);
//	memset(t,0,size);
//	tlvInfo_init(t);
//	int tindex =0;
	//emvparse(test, size, t, &tindex , 0, dict);
//	printf("<ICC type=\"EMV\">\n");
//	emvparse2(test, size, t, &tindex , 0, dict);
//	printf("</ICC>\n");
	//emvPrint_result(t, tindex);
//	emvFormat_result(t, tindex);

	int tlvTag;
	int tlvLength;
	int tlvCommand;
	int tlvValuePointer;
	int tlvOffset;
	int idx = 0;
	int commandOffset = 0;

//	unsigned char tlvtest[] = {0x5F,0x81,0x81,0x01,0x02,0x00,0x00}; //Antenna Off
//	unsigned char tlvtest[] = {0x5F,0x81,0x81,0x01,0x06,0x04,0x00,0x01,0x02,0x03,0x04}; //Load Polling Table
//	unsigned char tlvtest[] = {0x5F,0x81,0x81,0x01,0x06,0x02,0x00,0x01,0x02,0x03,0x04}; //Poll For Card
	unsigned char tlvtest[] = {0x5F,0x84,0x81,0x15,0x06,0xFE,0x01,0x02,0x03,0x04,0x05}; //Straight Through Mode


	printf("INPUT DATA: ");
		for (idx = 0; idx < sizeof(tlvtest); idx++){
				printf("%02X ", tlvtest[idx]);
		}
	printf("\n");

	parseTlv(&tlvtest, sizeof(tlvtest), &tlvTag, &tlvLength, &tlvValuePointer);
	printf("TAG: %02X\n", tlvTag);
	printf("LEN: %02X\n", tlvLength);

	tlvOffset = (int)tlvValuePointer - (int)&tlvtest;

	printf("OFFSET: %02X\n", tlvOffset);

	printf("VALUE: ");
	for (idx = 0; idx < tlvLength; idx++){
			printf("%02X ", tlvtest[idx+tlvOffset]);
	}
	printf("\n");

	if (tlvTag == 0x5F818101 && tlvLength >= 0x02){
		tlvCommand=(tlvtest[tlvOffset]<<8)|tlvtest[tlvOffset+1];
		commandOffset = 0x02;
		if (tlvCommand == 0x0200){
			printf("COMMAND POLL: %02X\n", tlvCommand);
		}
		if (tlvCommand == 0x0400){
			printf("COMMAND LOAD TABLE: %02X\n", tlvCommand);
		}
		if (tlvCommand == 0x0000){
			printf("COMMAND ANTENNA OFF: %02X\n", tlvCommand);
		}
	}

	if (tlvTag == 0x5F848115 && tlvLength >= 0x01){
		tlvCommand=tlvtest[tlvOffset];
		commandOffset = 0x01;
		if (tlvCommand == 0xFE){
			printf("COMMAND THROUGH MODE: %02X\n", tlvCommand);
		}
	}

	printf("COMMAND OFFSET: %02X\n", commandOffset);

	printf("ACTUAL VALUE: ");
	for (idx = 0; idx < tlvLength-commandOffset; idx++){
			printf("%02X ", tlvtest[idx+tlvOffset+commandOffset]);
	}
	printf("\n");

	printf("COMMAND: %02X\n", tlvCommand);

	return 0;
}

int parseTlv(unsigned char *buffer, int length, int *tlvTag, int *tlvLength, int *tlvValue) {

        // Get tag
        int tag=*(buffer++);
        int tagLength,tmp;
        length--;
        if((tag&0x1F)==0x1F) {
            if((length--)==0) return -1;
            tag=(tag<<8)|*(buffer++);
            if((tag&0x80)==0x80) {
                if((length--)==0) return -1;
                tag=(tag<<8)|*(buffer++);
                if((tag&0x80)==0x80) {
                    if((length--)==0) return -1;
                    tag=(tag<<8)|*(buffer++);
                    if((tag&0x80)==0x80) {
                        // Longer than 4 byte tags are NOT supported
                        return -1;
                    }
                }
            }
        } else {
            if(tag==0) {
            	return -1;
            }
        }

        (*tlvTag) = tag;

        // Get length
        if((length--)==0) return -1;
        tmp=*(buffer++);
        tagLength=0;

        switch(tmp) {
            case 0x84:
                if((length--)==0) return -1;
                tagLength=*(buffer++);
                /* no break */
            case 0x83:
                if((length--)==0) return -1;
                tagLength=(tagLength<<8)|*(buffer++);
                /* no break */
            case 0x82:
                if((length--)==0) return -1;
                tagLength=(tagLength<<8)|*(buffer++);
                /* no break */
            case 0x81:
                if((length--)==0) return -1;
                tagLength=(tagLength<<8)|*(buffer++);
                break;
            default:
                if(tmp>=0x80) {
                    // Other 8x variants are NOT supported
                    return -1;
                }
                tagLength=tmp;
                break;
        }

        (*tlvLength) = tagLength;

        (*tlvValue) = buffer;

        // Check value
        if(tagLength>length) return -1;

    return 0;
}
