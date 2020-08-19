//
// Created by root on 2020/8/19.
//
#include <cstdio>
#include "../DiskInfoGetter.h"

int main(void)
{
    DiskData *pData = DiskInfoGetter::getDiskData("/dev/nvme0n1");
    printf("hello\n");
    return 0;
}
