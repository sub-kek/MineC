#pragma once

#include "../connection.h"
#include "../packet.h"

void m_Handler_handle_status(m_Connection *con, m_Packet *pck);
void m_Handler_handle_login(m_Connection *con, m_Packet *pck);
