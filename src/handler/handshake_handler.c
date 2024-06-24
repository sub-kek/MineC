#include "handler.h"

#include <stdint.h>

#include "../protocol.h"
#include "../connection.h"

void m_Handler_handle_handshake(m_Connection *con, m_Packet *pck) {
	m_Packet_read_varint(pck);
	m_Packet_read_varint(pck);
	m_Packet_read_varint(pck);
	m_Packet_read_string(pck);
	m_Packet_read_short(pck);
	con->next_state = m_Packet_read_varint(pck);

	switch (con->next_state) {
		case SI_STATUS:
			m_Packet *rpck = m_Packet_empty();
			m_Packet_write_varint(rpck, 0x00);
			m_Packet_write_string(rpck, "{\"version\":{\"name\":\"MineC\",\"protocol\":765},\"players\":{\"max\":100,\"online\":5,\"sample\":[]},\"description\":{\"text\":\"Welcome to MineC!\"}}");
			m_Packet_write_lenght(rpck);
			
			rpck->size = rpck->pos;	

			m_Connection_write(con, rpck);

			m_Connection_read(con);
			m_Connection_write(con, m_Connection_read(con));
		break;
	}
}
