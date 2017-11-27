/*
 * bsp_eeprom.c
 *
 *  Created on: 2017Äê9ÔÂ8ÈÕ
 *      Author: fly
 */
#include "bsp.h"
#include "lite-log.h"

void EEPROM_InitHard(void) {

	uint32_t u32Data;

	SYS_UnlockReg();

	/* Enable FMC ISP function */
	FMC_Open();
	/* Read BS */
	log_debug("  Boot Mode ............................. ");
	if (FMC_GetBootSource() == 0)
		log_debug("[APROM]");
	else {
		log_debug("[LDROM]");
		log_debug("  WARNING: The driver sample code must execute in AP mode!");
		// goto lexit;
	}

	u32Data = FMC_ReadCID();
	log_debug("  Company ID ............................ [0x%08x]", u32Data);

	u32Data = FMC_ReadPID();
	log_debug("  Product ID ............................ [0x%08x]", u32Data);

	/* Read User Configuration */
	log_debug("  User Config 0 ......................... [0x%08x]",
			FMC_Read(FMC_CONFIG_BASE));
	log_debug("  User Config 1 ......................... [0x%08x]",
			FMC_Read(FMC_CONFIG_BASE + 4));

	uint8_t i;

	for (i = 0; i < 3; i++) {
		u32Data = FMC_ReadUID(i);
		log_debug("  Unique ID %d ........................... [0x%08x]\n", i,
				u32Data);
	}

	for (i = 0; i < 4; i++) {
		u32Data = FMC_ReadUCID(i);
		log_debug("  Unique Customer ID %d .................. [0x%08x]\n", i,
				u32Data);
	}

	/* Read Data Flash base address */
	u32Data = FMC_ReadDataFlashBaseAddr();
	log_debug("  Data Flash Base Address ............... [0x%08x]\n", u32Data);
	/* Disable FMC ISP function */
	FMC_Close();

	/* Lock protected registers */
	SYS_LockReg();
}
void bsp_eeprom_write_int(uint32_t u32addr, uint32_t u32data) {
	FMC_Write(u32addr, u32data);
}
int32_t bsp_eeprom_erase(uint32_t u32addr) {
	return FMC_Erase(u32addr);
}

uint32_t bsp_eeprom_read_int(uint32_t u32Addr) {
	return FMC_Read(u32Addr);
}

/******************************************************************************************************************/
