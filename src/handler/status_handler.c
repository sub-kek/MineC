#include "handler.h"

#include <json-c/json_object.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#include "../protocol.h"
#include "../connection.h"
#include "../mfile.h"

void m_Handler_handle_status(m_Connection *con, m_Packet*) {
	m_Packet rpck = m_Packet_empty();
	m_Packet_write_varint(&rpck, PI_HANDSHAKE);	

	struct json_object *motd_object = json_object_from_file("motd.json");
	char *motd = (char*)json_object_to_json_string_ext(motd_object, JSON_C_TO_STRING_PLAIN);
	free(motd_object);

	size_t favicon_size;
	char *favicon = mread_file("favicon.png", &favicon_size); 
	char *favicon_base64 = mbase64_encode(favicon, favicon_size); 

	size_t both_size = strlen(motd) + strlen(favicon_base64);

	char json_buf[both_size];
	snprintf(json_buf, both_size, motd, favicon_base64);

	m_Packet_write_string(&rpck, json_buf);

	m_Packet_write_lenght(&rpck);
			
	rpck.size = rpck.pos;	

	m_Connection_write(con, rpck);

	m_Connection_read(con);
	m_Connection_write(con, m_Connection_read(con));

	free(motd);
	free(favicon_base64);
	free(favicon);
	m_Packet_cleanup(&rpck);
}
