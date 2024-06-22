#pragma once

#include <stdint.h>
typedef struct {
	uint8_t *data;
	unsigned int pos;
	unsigned int size;
} m_Packet;

m_Packet *m_Packet_constructor(unsigned int size);

uint8_t m_Packet_read_byte(m_Packet *pck);
uint16_t m_Packet_read_short(m_Packet *pck);
uint32_t m_Packet_read_int(m_Packet *pck);
char *m_Packet_read_string(m_Packet *pck);
