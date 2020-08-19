//
// Created by raven on 2020/8/19.
//

#ifndef DISKINFOSERVER_DISKDATA_H
#define DISKINFOSERVER_DISKDATA_H
#include "linux/nvme.h"

// 额外磁盘信息，等待驱动工具
struct nvme_additional_disk_info{

};

struct DiskData{
    DiskData(nvme_smart_log *pLog, nvme_additional_disk_info *pInfo)
    {
        this->smart_log = pLog;
        this->additional_info = pInfo;
    }
    
    struct nvme_smart_log *smart_log;
    struct nvme_additional_disk_info *additional_info; // 额外数据
};

#endif //DISKINFOSERVER_DISKDATA_H
