/*
 * THIS FILE IS AUTOMATICALLY GENERATED
 *
 * SHDLC-Generator: 0.8.2
 * Yaml Version: 0.3.0
 * Template Version: 0.7.0
 */
/*
 * Copyright (c) 2021, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "svm40_uart.h"
#include "sensirion_common.h"
#include "sensirion_shdlc.h"
#include "sensirion_uart_hal.h"

#define SVM40_UART_ADDRESS 0x00

int16_t svm40_start_continuous_measurement(void) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[12];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x00, SVM40_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x00);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    if (error) {
        return error;
    }
    return NO_ERROR;
}

int16_t svm40_stop_measurement(void) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[12];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x01, SVM40_UART_ADDRESS,
                                0);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    if (error) {
        return error;
    }
    return NO_ERROR;
}

int16_t svm40_read_measured_values_as_integers(int16_t* voc_index,
                                               int16_t* humidity,
                                               int16_t* temperature) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[24];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x03, SVM40_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x0A);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 6, &header);
    if (error) {
        return error;
    }
    *voc_index = sensirion_common_bytes_to_int16_t(&buffer[0]);
    *humidity = sensirion_common_bytes_to_int16_t(&buffer[2]);
    *temperature = sensirion_common_bytes_to_int16_t(&buffer[4]);
    return NO_ERROR;
}

int16_t svm40_read_measured_values_as_integers_with_raw_parameters(
    int16_t* voc_index, int16_t* humidity, int16_t* temperature,
    uint16_t* raw_voc_ticks, int16_t* raw_humidity, int16_t* raw_temperature) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[36];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x03, SVM40_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x0B);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 12, &header);
    if (error) {
        return error;
    }
    *voc_index = sensirion_common_bytes_to_int16_t(&buffer[0]);
    *humidity = sensirion_common_bytes_to_int16_t(&buffer[2]);
    *temperature = sensirion_common_bytes_to_int16_t(&buffer[4]);
    *raw_voc_ticks = sensirion_common_bytes_to_uint16_t(&buffer[6]);
    *raw_humidity = sensirion_common_bytes_to_int16_t(&buffer[8]);
    *raw_temperature = sensirion_common_bytes_to_int16_t(&buffer[10]);
    return NO_ERROR;
}

int16_t
svm40_get_temperature_offset_for_rht_measurements(uint8_t* t_offset,
                                                  uint8_t t_offset_size) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[522];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x60, SVM40_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x01);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 255, &header);
    if (error) {
        return error;
    }
    sensirion_common_copy_bytes(&buffer[0], t_offset, t_offset_size);
    return NO_ERROR;
}

int16_t svm40_get_voc_tuning_parameters(int16_t* voc_index_offset,
                                        int16_t* learning_time_hours,
                                        int16_t* gating_max_duration_minutes,
                                        int16_t* std_initial) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[28];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x60, SVM40_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x08);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 8, &header);
    if (error) {
        return error;
    }
    *voc_index_offset = sensirion_common_bytes_to_int16_t(&buffer[0]);
    *learning_time_hours = sensirion_common_bytes_to_int16_t(&buffer[2]);
    *gating_max_duration_minutes =
        sensirion_common_bytes_to_int16_t(&buffer[4]);
    *std_initial = sensirion_common_bytes_to_int16_t(&buffer[6]);
    return NO_ERROR;
}

int16_t svm40_store_nv_data(void) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[12];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x60, SVM40_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x80);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(500000);

    error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    if (error) {
        return error;
    }
    return NO_ERROR;
}

int16_t
svm40_set_temperature_offset_for_rht_measurements(const uint8_t* t_offset,
                                                  uint8_t t_offset_size) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[520];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x60, SVM40_UART_ADDRESS,
                                255);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x81);

    sensirion_shdlc_add_bytes_to_frame(&frame, t_offset, t_offset_size);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    if (error) {
        return error;
    }
    return NO_ERROR;
}

int16_t svm40_set_voc_tuning_parameters(int16_t voc_index_offset,
                                        int16_t learning_time_hours,
                                        int16_t gating_max_duration_minutes,
                                        int16_t std_initial) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[28];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x60, SVM40_UART_ADDRESS,
                                9);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x88);

    sensirion_shdlc_add_int16_t_to_frame(&frame, voc_index_offset);
    sensirion_shdlc_add_int16_t_to_frame(&frame, learning_time_hours);
    sensirion_shdlc_add_int16_t_to_frame(&frame, gating_max_duration_minutes);
    sensirion_shdlc_add_int16_t_to_frame(&frame, std_initial);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    if (error) {
        return error;
    }
    return NO_ERROR;
}

int16_t svm40_get_voc_state(uint8_t* state, uint8_t state_size) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[28];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x61, SVM40_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x08);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 8, &header);
    if (error) {
        return error;
    }
    sensirion_common_copy_bytes(&buffer[0], state, state_size);
    return NO_ERROR;
}

int16_t svm40_set_voc_state(const uint8_t* state, uint8_t state_size) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[28];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x61, SVM40_UART_ADDRESS,
                                9);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x88);

    sensirion_shdlc_add_bytes_to_frame(&frame, state, state_size);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    if (error) {
        return error;
    }
    return NO_ERROR;
}

int16_t svm40_get_product_type(unsigned char* product_type,
                               uint8_t product_type_size) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[522];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0xD0, SVM40_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x00);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 255, &header);
    if (error) {
        return error;
    }
    sensirion_common_copy_bytes(&buffer[0], product_type, product_type_size);
    return NO_ERROR;
}

int16_t svm40_get_product_name(unsigned char* product_name,
                               uint8_t product_name_size) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[522];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0xD0, SVM40_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x01);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 255, &header);
    if (error) {
        return error;
    }
    sensirion_common_copy_bytes(&buffer[0], product_name, product_name_size);
    return NO_ERROR;
}

int16_t svm40_get_serial_number(unsigned char* serial_number,
                                uint8_t serial_number_size) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[522];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0xD0, SVM40_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x03);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 255, &header);
    if (error) {
        return error;
    }
    sensirion_common_copy_bytes(&buffer[0], serial_number, serial_number_size);
    return NO_ERROR;
}

int16_t svm40_get_version(uint8_t* firmware_major, uint8_t* firmware_minor,
                          bool* firmware_debug, uint8_t* hardware_major,
                          uint8_t* hardware_minor, uint8_t* protocol_major,
                          uint8_t* protocol_minor) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[26];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0xD1, SVM40_UART_ADDRESS,
                                0);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 7, &header);
    if (error) {
        return error;
    }
    *firmware_major = buffer[0];
    *firmware_minor = buffer[1];
    *firmware_debug = buffer[2];
    *hardware_major = buffer[3];
    *hardware_minor = buffer[4];
    *protocol_major = buffer[5];
    *protocol_minor = buffer[6];
    return NO_ERROR;
}

int16_t svm40_device_reset(void) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[12];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0xD3, SVM40_UART_ADDRESS,
                                0);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    if (error) {
        return error;
    }
    sensirion_uart_hal_sleep_usec(100000);
    return NO_ERROR;
}

int16_t svm40_get_system_up_time(uint32_t* system_up_time) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[20];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x93, SVM40_UART_ADDRESS,
                                0);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 4, &header);
    if (error) {
        return error;
    }
    *system_up_time = sensirion_common_bytes_to_uint32_t(&buffer[0]);
    return NO_ERROR;
}

int16_t svm40_enter_bootloader(void) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[12];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0xF3, SVM40_UART_ADDRESS,
                                0);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x00);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    if (error) {
        return error;
    }
    sensirion_uart_hal_sleep_usec(1000000);
    return NO_ERROR;
}
