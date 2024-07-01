#include "handler.h"

#include <stdio.h>
#include <stdlib.h>

#include "../connection.h"
#include "../protocol.h"

void m_Handler_handle_login(m_Connection *con, m_Packet*) {
	m_Packet rpck = m_Connection_read(con);
	m_Packet_read_varint(&rpck);
	m_Packet_read_varint(&rpck);
	char *name = m_Packet_read_string(&rpck);
  	uuid_t *uuid = malloc(sizeof(*uuid)); m_Packet_read_UUID(&rpck, uuid);
	char *uuid_str = uuid_to_string(*uuid);

	printf("UUID of player %s is %s\n", name, uuid_str);

	m_Packet pck = m_Packet_empty();

	m_Packet_write_varint(&pck, PI_KICK);
	m_Packet_write_string(&pck, "{\"text\": \"You want to play?\nServer not written lol.\",\"color\": \"red\",\"bold\": true}");
	m_Packet_write_lenght(&pck);

	m_Connection_write(con, pck);

	free(name);
	free(uuid_str);
	free(uuid);
	m_Packet_cleanup(&rpck);
	m_Packet_cleanup(&pck);
}
