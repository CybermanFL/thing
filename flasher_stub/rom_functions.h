/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 51 Franklin
 * Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef ROM_FUNCTIONS_H_
#define ROM_FUNCTIONS_H_

#include <stdint.h>
#include <common_macros.h>

void ets_delay_us(uint32_t us);
void ets_isr_mask(uint32_t ints);
void ets_isr_unmask(uint32_t ints);

uint32_t SPIRead(uint32_t addr, void *dst, uint32_t size);
uint32_t SPIWrite(uint32_t addr, const uint8_t *src, uint32_t size);
uint32_t SPIEraseSector(uint32_t sector_num);
uint32_t SPI_read_status();
uint32_t Wait_SPI_Idle();
void spi_flash_attach();

void SelectSpiFunction();
void SPIFlashModeConfig(uint32_t a, uint32_t b);
void SPIReadModeCnfig(uint32_t a);

void Cache_Read_Disable();

void memset(void *addr, uint8_t c, uint32_t len);

void ets_delay_us(uint32_t delay_micros);

typedef void (*int_handler_t)(void *arg);
int_handler_t ets_isr_attach(uint32_t int_num, int_handler_t handler,
                             void *arg);
void ets_set_user_start(void (*user_start_fn)());

uint32_t rtc_get_reset_reason();
void software_reset();
void rom_phy_reset_req();

void _ResetVector();

#ifdef ESP8266
/* Some ROM functions are only present on ESP8266 */

struct MD5Context {
  uint32_t buf[4];
  uint32_t bits[2];
  uint8_t in[64];
};

void MD5Init(struct MD5Context *ctx);
void MD5Update(struct MD5Context *ctx, void *buf, uint32_t len);
void MD5Final(uint8_t digest[16], struct MD5Context *ctx);

/* Documented ESP31/32 ROM functions don't include these */
uint32_t SPIEraseChip();
uint32_t SPIEraseBlock(uint32_t block_num);
uint32_t SPILock();
uint32_t SPIUnlock();

#endif

#ifdef ESP32
/* Some ESP31/32 ROM functions */

inline static int SPIUnlock(void) { return 0; /* no-op */ }

#endif

#endif /* ROM_FUNCTIONS_H_ */
