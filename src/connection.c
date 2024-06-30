#include "connection.h"

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "packet.h"
#include "protocol.h"
#include "handler/handler.h"

#define BUFFER_SIZE 65535

m_Connection m_Connection_constructor(int client_fd) {
	m_Connection con = {
		.client_fd = client_fd,
		.buffer = malloc(BUFFER_SIZE)
	};

	return con;
}

m_Packet m_Connection_read(m_Connection *con) {
	m_Packet pck = m_Packet_empty();
	
	memset(con->buffer, 0, BUFFER_SIZE);
	
	pck.size = read(con->client_fd, con->buffer, BUFFER_SIZE);
	pck.data = malloc(pck.size);
	memcpy(pck.data, con->buffer, pck.size);

	return pck;
}

void m_Connection_write(m_Connection *con, m_Packet pck) {	
	write(con->client_fd, pck.data, pck.size);
}

void m_Connection_handle_connection(m_Connection *con) {
	m_Packet handshake_pck = m_Connection_read(con);
	/*uint32_t pck_len =*/ m_Packet_read_varint(&handshake_pck);
	uint32_t pck_id = m_Packet_read_varint(&handshake_pck);
	/*uint32_t pck_proto =*/ m_Packet_read_varint(&handshake_pck);
	/*char *pck_address =*/ m_Packet_read_string(&handshake_pck);
	/*uint16_t pck_port =*/ m_Packet_read_short(&handshake_pck);
	con->next_state = m_Packet_read_varint(&handshake_pck);

	handshake_pck.pos = 0;

	if (pck_id == PI_HANDSHAKE) {
		switch (con->next_state) {
			case SI_STATUS: {
				m_Handler_handle_status(con, nullptr);

				break;
			}
			case SI_LOGIN: {
				m_Handler_handle_login(con, nullptr);	

				break;
			}
		}
	}
}
