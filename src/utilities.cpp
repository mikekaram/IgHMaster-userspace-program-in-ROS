
/*
 * utilities.cpp
 *
 * A library with useful functions
 * for communication and handling process data, using EtherCAT
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include "ecrt.h"
#include "utilities.h"


int safe_atoi(const char *s, int *val)
{
	long l;
	char *endp;

	l = strtol(s, &endp, 10);
	if (s != endp && *endp == '\0') {
		*val = l;
		return 0;
	} else
		return -1;
}

uint16_t process_input_uint16(uint8_t * data_ptr, uint8_t index, uint8_t subindex)
{
    uint16_t return_value = 0x0000;
    uint8_t new_data_ptr[2];
    new_data_ptr[0] = data_ptr[index];
    new_data_ptr[1] = data_ptr[subindex];
    return_value = EC_READ_U16(new_data_ptr);
    return return_value;
}
int16_t process_input_sint16(uint8_t * data_ptr, uint8_t index, uint8_t subindex)
{
    int16_t return_value = 0x0000;
    uint8_t new_data_ptr[2];
    new_data_ptr[0] = data_ptr[index];
    new_data_ptr[1] = data_ptr[subindex];
    return_value = EC_READ_S16(new_data_ptr);
    return return_value;
}
int32_t process_input_sint32(uint8_t * data_ptr, uint8_t index, uint8_t subindex)
{
    int32_t return_value = 0x00000000;
    uint8_t new_data_ptr[4];
    new_data_ptr[0] = data_ptr[index];
    new_data_ptr[1] = data_ptr[index+1];
    new_data_ptr[2] = data_ptr[subindex];
    new_data_ptr[3] = data_ptr[subindex+1];
    return_value = EC_READ_S32(new_data_ptr);
    return return_value;
}

ssize_t insist_write(int fd, const char *buf, size_t count)
{
    ssize_t ret;
    size_t orig_count = count;

    while (count > 0) {
        ret = write(fd, buf, count);
        if(ret < 0)
            return ret;
        buf += ret;
        count -= ret;

    }
    return orig_count;
}