#pragma once
#include "sys.h"

namespace flash
{
	const u32 FLASH_BASE_ADDR = 0X0800C004;
	const u32 FLASH_CONFIG    = FLASH_BASE_ADDR + 0X800;
	const u32 FLASH_IP        = FLASH_CONFIG+0X800;
	const u32 FLASH_SOCKET    = FLASH_IP + 0X800;
	const u32 FLASH_IP_LEN    = FLASH_SOCKET + 0X800;
}
