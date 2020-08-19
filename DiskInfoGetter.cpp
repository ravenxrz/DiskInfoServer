//
// Created by raven on 2020/8/19.
//

#include "DiskInfoGetter.h"
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <cstring>
#include <sys/ioctl.h>

static long double int128_to_double(__u8 *data)
{
    int i;
    long double result = 0;
    
    for (i = 0; i < 16; i++) {
        result *= 256;
        result += data[15 - i];
    }
    return result;
}

static std::string data2String(DiskData *diskData)
{
    struct nvme_smart_log *smart = diskData->smart_log;
    /* convert temperature from Kelvin to Celsius */
    int c;
    unsigned int temperature = ((smart->temperature[1] << 8) |smart->temperature[0]) - 273;
    
    printf("critical_warning:%#x\n", smart->critical_warning);
    printf("temperature:%u\n", temperature);
    printf("available_spare:%u\n", smart->avail_spare);
    printf("available_spare_threshold:%u\n", smart->spare_thresh);
    printf("percentage_used:%u\n", smart->percent_used);
    printf("data_units_read:%.0Lf\n",
           int128_to_double(smart->data_units_read));
    printf("data_units_written:%.0Lf\n",
           int128_to_double(smart->data_units_written));
    printf("host_read_commands:%.0Lf\n",
           int128_to_double(smart->host_reads));
    printf("host_write_commands:%.0Lf\n",
           int128_to_double(smart->host_writes));
    printf("controller_busy_time:%.0Lf\n",
           int128_to_double(smart->ctrl_busy_time));
    printf("power_cycles:%.0Lf\n",
           int128_to_double(smart->power_cycles));
    printf("power_on_hours:%.0Lf\n",
           int128_to_double(smart->power_on_hours));
    printf("unsafe_shutdowns:%.0Lf\n",
           int128_to_double(smart->unsafe_shutdowns));
    printf("media_errors:%.0Lf\n",
           int128_to_double(smart->media_errors));
    printf("num_err_log_entries:%.0Lf\n",
           int128_to_double(smart->num_err_log_entries));
    printf("Critical Composite Temperature Time:%u\n", smart->warning_temp_time);
    for (c=0; c < 8; c++) {
        printf("Temperature Sensor %d:%u\n", c+1, smart->temp_sensor[c] ? smart->temp_sensor[c]-273 :0);
    }
}

nvme_smart_log *DiskInfoGetter::getSmartLog(char *dev)
{
    struct nvme_smart_log *smart_log = new nvme_smart_log();
    struct nvme_admin_cmd cmd{};
    
    unsigned int data_len = sizeof(*smart_log);
    unsigned int dw10 = 0x2 | (((sizeof(*smart_log) / 4) - 1) << 16);
    unsigned int nsid = 0xffffffff;
    
    memset(&cmd, 0, sizeof(cmd));
    cmd.opcode = nvme_admin_get_log_page;
    cmd.addr = (__u64) ((unsigned long) smart_log);
    cmd.data_len = data_len;
    cmd.cdw10 = dw10;
    cmd.nsid = nsid;
    
    int fd = open(dev, O_RDONLY);
    if (fd == -1){
        perror("open device error");
        return nullptr;
    }
    ioctl(fd, NVME_IOCTL_ADMIN_CMD, &cmd);
    close(fd);
    
    return smart_log;
}

nvme_additional_disk_info *DiskInfoGetter::getAdditionalDiskInfo(char *dev)
{
    return nullptr;
}

struct DiskData *DiskInfoGetter::getDiskData(char *dev)
{
    // get smart info
    struct nvme_smart_log *smartLog = getSmartLog(dev);
    if(smartLog == nullptr) return nullptr;
    // get additional info
    struct nvme_additional_disk_info *additional_info = getAdditionalDiskInfo(dev);
    // TODO: if(additional_info == nullptr) return nullptr;
    
    struct DiskData *diskData = new DiskData(smartLog,additional_info);
    return diskData;
}

std::string DiskInfoGetter::getDiskDataString(char *dev)
{
    DiskData* diskData = getDiskData(dev);
    
    return std::string();
}



