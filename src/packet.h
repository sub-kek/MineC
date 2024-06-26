#pragma once

#include <stdint.h>

#include "mtypes.h"

typedef struct {
	uint8_t *data;
	unsigned int pos;
	unsigned int size;
} m_Packet;

m_Packet *m_Packet_constructor(uint8_t *data, uint32_t size);
m_Packet *m_Packet_empty();

uint8_t m_Packet_read_byte(m_Packet *pck);
uint16_t m_Packet_read_short(m_Packet *pck);
uint32_t m_Packet_read_varint(m_Packet *pck);
uint64_t m_Packet_read_long(m_Packet *pck);
void m_Packet_read_UUID(m_Packet *pck, uuid_t *out);
char *m_Packet_read_string(m_Packet *pck);

void m_Packet_write_lenght(m_Packet *pck);
void m_Packet_write_byte(m_Packet *pck, uint8_t value);
void m_Packet_write_varint(m_Packet *pck, uint32_t value);
void m_Packet_write_long(m_Packet *pck, uint64_t value);
void m_Packet_write_string(m_Packet *pck, char *value);
