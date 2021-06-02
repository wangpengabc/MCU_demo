#include <stdlib.h>
#include <stdio.h>
#include "hbird_sdk_soc.h"
#include "iic.h"
#include "LQ12864.h"


void wait_seconds(size_t n)
{
    uint64_t start_mtime, delta_mtime;

    uint64_t tmp = SysTimer_GetLoadValue();
    do {
        start_mtime = SysTimer_GetLoadValue();
    } while (start_mtime == tmp);

    do {
        delta_mtime = SysTimer_GetLoadValue() - start_mtime;
    } while (delta_mtime < (n * SOC_TIMER_FREQ));
}

int main(void)
{   

    iic_Init();
    wait_seconds(2);
    OLED_Init();
    wait_seconds(2);

    // OLED_Fill(0xFF);
    // iic_Init();

    int col_index = 0;

    // 显示队伍名称和编号, 穿越时差队  CICC2297
    for (col_index=0; col_index<5; col_index++)
    {
        OLED_P16x16Ch_gp(18*col_index + 20, 0, col_index);
    }

    for (col_index=0; col_index<16; col_index++)
    {
        OLED_P16x8Ch_gp(8*col_index, 2, col_index+11);
    }


    while(1)
    {
        iic_Init();
    }

    return 0;
}