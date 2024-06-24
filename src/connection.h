#pragma once

#include <stdint.h>

#include "packet.h"

typedef struct {
	int client_fd;
	uint8_t *buffer;
	uint32_t next_state;
} m_Connection;

m_Connection *m_Connection_constructor(int client_fd);

m_Packet *m_Connection_read(m_Connection *con);
void m_Connection_write(m_Connection *con, m_Packet *pck);

void m_Connection_handle_connection(m_Connection *con);
