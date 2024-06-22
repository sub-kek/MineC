#include "packet.h"

#include <stdint.h>
#include <stdlib.h>

m_Packet *m_Packet_constructor(uint8_t *data, uint32_t size) {
	m_Packet *pck = malloc(sizeof(*pck));
	
	pck->size = size;
	pck->pos	= 0;
	pck->data	= data;

	return pck;
}

uint8_t m_Packet_read_byte(m_Packet *pck)
	{ return pck->data[(pck->pos)++]; }

uint16_t m_Packet_read_short(m_Packet *pck) {
	uint16_t value = m_Packet_read_byte(pck) << 8;
  value |= m_Packet_read_byte(pck);
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

char *m_Packet_read_string(m_Packet *pck) {
	uint8_t lenght = m_Packet_read_byte(pck);

	char *string = malloc(lenght);

	for (uint32_t i = 0; i < lenght; i++) {
		string[i] = m_Packet_read_byte(pck);
	}

	return string;
}
