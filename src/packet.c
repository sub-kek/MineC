#include "packet.h"

#include <bits/types/struct_iovec.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

m_Packet *m_Packet_constructor(uint8_t *data, uint32_t size) {
	m_Packet *pck = malloc(sizeof(*pck));
	
	pck->size = size;
	pck->pos	= 0;
	pck->data	= data;

	return pck;
}

m_Packet *m_Packet_empty() {
	m_Packet *pck = malloc(sizeof(*pck));

	pck->size = 0;
	pck->pos	= 0;
	pck->data = malloc(1024);

	return pck;
}

uint8_t m_Packet_read_byte(m_Packet *pck)
	{ return pck->data[pck->pos++]; }

uint16_t m_Packet_read_short(m_Packet *pck) {
	uint16_t value = m_Packet_read_byte(pck) << 8;
  value |= m_Packet_read_byte(pck);
  return value;	
}

uint64_t m_Packet_read_long(m_Packet *pck) {
    uint64_t value = (uint64_t)m_Packet_read_byte(pck) << 56;
    value |= (uint64_t)m_Packet_read_byte(pck) << 48;
    value |= (uint64_t)m_Packet_read_byte(pck) << 40;
    value |= (uint64_t)m_Packet_read_byte(pck) << 32;
    value |= (uint64_t)m_Packet_read_byte(pck) << 24;
    value |= (uint64_t)m_Packet_read_byte(pck) << 16;
    value |= (uint64_t)m_Packet_read_byte(pck) << 8;
    value |= (uint64_t)m_Packet_read_byte(pck);
    return value;
}

uint32_t m_Packet_read_int(m_Packet *pck) {
	uint32_t	result = 0,
						shift = 0;

	uint8_t read;

	do {
		read = m_Packet_read_byte(pck);
		result |= (read & 0x7f) << shift;
		shift += 7;
	} while (read & 0x80);

	return result;
}

void m_Packet_write_long(m_Packet *pck, uint64_t value) {
    m_Packet_write_byte(pck, (value >> 56) & 0xFF);
    m_Packet_write_byte(pck, (value >> 48) & 0xFF);
    m_Packet_write_byte(pck, (value >> 40) & 0xFF);
    m_Packet_write_byte(pck, (value >> 32) & 0xFF);
    m_Packet_write_byte(pck, (value >> 24) & 0xFF);
    m_Packet_write_byte(pck, (value >> 16) & 0xFF);
    m_Packet_write_byte(pck, (value >> 8) & 0xFF);
    m_Packet_write_byte(pck, value & 0xFF);
}

char *m_Packet_read_string(m_Packet *pck) {
	uint32_t lenght = m_Packet_read_int(pck);

	char *string = malloc(lenght);

	for (uint32_t i = 0; i < lenght; i++) {
		string[i] = m_Packet_read_byte(pck);
	}

	return string;
}

void m_Packet_write_lenght(m_Packet *pck) {
	m_Packet *tpck = m_Packet_empty();
	m_Packet_write_int(tpck, pck->pos);	

	for (uint32_t i = 0; i < tpck->pos; i++) {
		for (uint32_t j = pck->pos + 1; j > 0; j--) {
			pck->data[j] = pck->data[j - 1];
		}
	}

	uint32_t data_size = pck->pos;
	pck->pos = 0;
	m_Packet_write_int(pck, data_size);
	pck->pos = data_size + tpck->pos;
	free(tpck);
}

void m_Packet_write_byte(m_Packet *pck, uint8_t value)
	{ pck->data[pck->pos++] = value; }

void m_Packet_write_int(m_Packet *pck, uint32_t value) {
	while (value >= 0x80) {
		m_Packet_write_byte(pck, (value & 0x7f) | 0x80);
		value >>= 7;
	}

	m_Packet_write_byte(pck, value);
}

void m_Packet_write_string(m_Packet *pck, char *value) {
	uint32_t lenght = strlen(value);
	m_Packet_write_int(pck, lenght);
	
	for (uint32_t i = 0; i < lenght; i++) {
		m_Packet_write_byte(pck, value[i]);	
	}
}
