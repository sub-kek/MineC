#include "handler.h"

#include <stdio.h>

#include "../protocol.h"
#include "../connection.h"

void m_Handler_handle_status(m_Connection *con, m_Packet*) {
	m_Packet rpck = m_Packet_empty();
	m_Packet_write_varint(&rpck, PI_HANDSHAKE);	

	FILE *file = fopen("motd.json", "ro");
	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	fseek(file, 0, SEEK_SET);
	char buf[size];
	fread(buf, sizeof(char), size, file);
	fclose(file);

	m_Packet_write_string(&rpck, buf);

	m_Packet_write_lenght(&rpck);
			
	rpck.size = rpck.pos;	

	m_Connection_write(con, rpck);

	m_Connection_read(con);
	m_Connection_write(con, m_Connection_read(con));
}
