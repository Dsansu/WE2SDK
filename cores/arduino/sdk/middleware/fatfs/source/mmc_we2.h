/*-----------------------------------------------------------------------
/  Low level disk interface modlue include file   (C)ChaN, 2016
/-----------------------------------------------------------------------*/

#ifndef _MMC_DEFINED
#define _MMC_DEFINED

#include "ff.h"
#include "diskio.h"
#include <stdbool.h>

typedef void (*FnPtr_GPIO_Output_Level) (bool setLevelHigh);
typedef void (*FnPtr_GPIO_Dir) (bool setDirOut);
typedef void (*FnPtr_GPIO_Pinmux) (bool setGpioFn);

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------*/
/* Prototypes for disk control functions */

DSTATUS mmc_disk_initialize (void);
DSTATUS mmc_disk_status (void);
DRESULT mmc_disk_read (BYTE* buff, LBA_t sector, UINT count);
DRESULT mmc_disk_write (const BYTE* buff, LBA_t sector, UINT count);
DRESULT mmc_disk_ioctl (BYTE cmd, void* buff);
void mmc_disk_timerproc (void);

#ifdef __cplusplus
}
#endif

#endif
