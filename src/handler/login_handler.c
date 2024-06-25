#include "handler.h"

#include "../connection.h"
#include "../protocol.h"
#include <stdint.h>
#include <stdio.h>

void m_Handler_handle_login(m_Connection *con, m_Packet*) {
	m_Packet *rpck = m_Connection_read(con);
	m_Packet_read_varint(rpck);
	m_Packet_read_varint(rpck);
	char *name = m_Packet_read_string(rpck);
	UUID *uuid = m_Packet_read_UUID(rpck);
	char *uuid_str = uuid_to_string(*uuid);

	printf("Name of %s is %s\n", uuid_str, name);

	m_Packet *pck = m_Packet_empty();

	m_Packet_write_varint(pck, PI_KICK);
	m_Packet_write_string(pck, "{\"text\": \"You want to play?\nServer not written lol.\",\"color\": \"red\",\"bold\": true}");
	m_Packet_write_lenght(pck);

	m_Connection_write(con, pck);
}
