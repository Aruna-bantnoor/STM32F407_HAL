#ifndef INC_FLASH_SECTOR_F4_H_
#define INC_FLASH_SECTOR_F4_H_

#include "stdint.h"

uint32_t Flash_Write_Only(uint32_t Address, uint32_t *Data, uint16_t words);

void Flash_Read_Data (uint32_t StartSectorAddress, uint32_t *RxBuf, uint16_t numberofwords);

void Flash_Erase_Sector_Only(uint32_t Address);


#endif /* INC_FLASH_SECTOR_F4_H_ */
