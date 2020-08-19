//
// Created by raven on 2020/8/19.
//
/**
 * 获取磁盘信息类
 */

#ifndef DISKINFOSERVER_DISKINFOGETTER_H
#define DISKINFOSERVER_DISKINFOGETTER_H

#include "linux/nvme.h"
#include "DiskData.h"
#include <string>


class DiskInfoGetter {
public:
    /**
     * 获取disk数据的string表达
     * @param dev
     * @return
     */
    static std::string getDiskDataString(char *dev);
private:
    /**
     * 获取磁盘的所有信息
     * @param dev 指定哪个磁盘
     * @return DiskData 指针
     *         failed: null
     */
    static struct DiskData* getDiskData(char *dev);
    /**
     * 获取smart信息
     * @param dev 查看哪个磁盘
     * @return smart log 结构体
     *          failed: null
     */
    static struct nvme_smart_log* getSmartLog(char *dev);
    
    /**
     * 获取额外磁盘信息
     * @param dev  哪个磁盘
     * @return 额外磁盘结构体
     *         failed:null
     */
    static struct nvme_additional_disk_info* getAdditionalDiskInfo(char *dev);
};


#endif //DISKINFOSERVER_DISKINFOGETTER_H
