#include "connection.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "packet.h"
#include "protocol.h"
#include "handler/handler.h"

#define BUFFER_SIZE 65535

m_Connection *m_Connection_constructor(int client_fd) {
	m_Connection *con = malloc(sizeof(*con));
	
	con->client_fd = client_fd;
	con->buffer = malloc(BUFFER_SIZE);

	return con;
}

m_Packet *m_Connection_read(m_Connection *con) {
	m_Packet *pck = m_Packet_empty();
	
	memset(con->buffer, 0, BUFFER_SIZE);
	
	pck->size = read(con->client_fd, con->buffer, BUFFER_SIZE);
	pck->data = malloc(pck->size);
	memcpy(pck->data, con->buffer, pck->size);

	return pck;
}

void m_Connection_write(m_Connection *con, m_Packet *pck) {	
	write(con->client_fd, pck->data, pck->size);
}

void m_Connection_handle_connection(m_Connection *con) {
	m_Packet *handshake_pck = m_Connection_read(con);
	uint32_t pck_len = m_Packet_read_varint(handshake_pck);
	uint32_t pck_id = m_Packet_read_varint(handshake_pck);	

	switch (pck_id) {
		case PI_HANDSHAKE:
			handshake_pck->pos = 0;
			m_Handler_handle_handshake(con, handshake_pck);
		break;
		default:
			printf("Unimplemented packet id: 0x%02x with len: %d\n", pck_id, pck_len);
		break;
	}
}
