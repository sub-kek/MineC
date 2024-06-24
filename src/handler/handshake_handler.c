#include "handler.h"

#include <stdint.h>
#include <stdio.h>

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
		case SI_STATUS: {
			m_Packet *rpck = m_Packet_empty();
			m_Packet_write_varint(rpck, 0x00);	

			char buf[65535];
			sprintf(buf, "{\"version\":{\"name\":\"MineC\",\"protocol\":765},\"players\":{\"max\":100,\"online\":5,\"sample\":[]},\"description\":{\"text\":\"\u00a7bWelcome to MineC!\"}, \"favicon\":\"%s\"}", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAIAAAAlC+aJAAABhGlDQ1BJQ0MgcHJvZmlsZQAAKJF9kT1Iw0AcxV9TpaIVQTuIOGSoTnZRkeJUq1CECqFWaNXB5NIvaNKQpLg4Cq4FBz8Wqw4uzro6uAqC4AeIq4uToouU+L+k0CLWg+N+vLv3uHsHCPUy06yuGKDptplKxMVMdlUMvMKPQfQhilmZWcacJCXRcXzdw8fXuwjP6nzuz9Gv5iwG+ETiGDNMm3iDeGbTNjjvE4dYUVaJz4knTLog8SPXFY/fOBdcFnhmyEyn5olDxGKhjZU2ZkVTI54mDquaTvlCxmOV8xZnrVxlzXvyFwZz+soy12mOIoFFLEGCCAVVlFCGjQitOikWUrQf7+Afcf0SuRRylcDIsYAKNMiuH/wPfndr5acmvaRgHOh+cZyPMSCwCzRqjvN97DiNE8D/DFzpLX+lDkQ/Sa+1tPARMLANXFy3NGUPuNwBhp8M2ZRdyU9TyOeB9zP6piwwdAv0rnm9Nfdx+gCkqavkDXBwCIwXKHu9w7t72nv790yzvx8HnXLi5LMWtAAAAAlwSFlzAAAuIwAALiMBeKU/dgAAAAd0SU1FB+cDEgwAKTGNBVYAAAAZdEVYdENvbW1lbnQAQ3JlYXRlZCB3aXRoIEdJTVBXgQ4XAAADFUlEQVRo3u1aUW7bMAx9JGU7G4rdahfaHXrhoVhtSRT3kbRdbCqNA6dZWvHDQGjH5hPJR1I2/fz1CE90nLATrJHS+fpsydezuvqIaakkYvdirlkjuwGj4mpSs36t8KmTKz1wE+GtblSLn63ErFwXwN17oAH4qgACgELq8a6QkfufxPnoFroxWTFLKbpUjhgHG+YAXOsBmCmRmOlp6wFkUQAoYBaP7zPgLITB/AJKujfXPTvRtCKEltZf4uISWg40AA1AAwCMGKt1oNqfscN0AlGoR94BHjOO7D+YQDUm9SaEqCULz63Vkk+ynNf/KReX1wuUISM/nzsPIFXIG5H8U1rydUPofOsBBPj9d836jvuWxA1AA/Ap54GCwuD9cdEnz3k06Ns10eK809boE4j0tcdPaV4lqK9OF7mkykCD8np843VyqsweUipxxRIJpQrlx+TUuOW6XBhCXBnHbiWqaR0A1wMfIF2Sr5XEnxfA2hxIiJsYlDq9bw+szQGnmc4aAZSOgoVMubbzMU/6nP0Vkm5B5zFwv9YDh82bJYCsVde71ldXIgw5T171iTVlFuf+VBA53nEIrbL+ZBKnbeoAZ7oNC7U6cG8A3Aw+vdFwGwBuT3uB9OhXGurnUlA6dNFi/ELzB43CAITjWmEC0sPxX6XIoNO03P4mQzhpa+J0XIW8pl+6qTy/U8he7T78DPaygZOPDSIT2xs9n07IiSIj5ByXfUnsUm36WQ5GWVPFAR+SxFedLDYD8Cf+bjTaAPzPIhbWAZCVPcz3/sdNgIVxepqpdsPDgRbHp2H3MOdKjLVtfeqOmNWS7pWjORReUATO7OK+fAAQeXpxhbwz0OwhFbE9hvnp3bmvTWd4zreVxIsL88epm+UAG183iVm3KT9u/DQabQC8jMyb3Of8V5c39kAh/xs4wrrcCwDQM2KpPkle0xoAivcJC5MQsftd3o6+uXlssBO2lsUrXkFwnRzQ8wGDcxd1kThXmsJA7GCIFJnEc70kiwXl3FAhgTmBumUI1b6MPH+ZL0izxkINQANQ2/+B3gWAv5hjW5zpJFU/AAAAAElFTkSuQmCC");

			m_Packet_write_string(rpck, buf);

			m_Packet_write_lenght(rpck);
			
			rpck->size = rpck->pos;	

			m_Connection_write(con, rpck);

			m_Connection_read(con);
			m_Connection_write(con, m_Connection_read(con));
			break;
		}
		case SI_LOGIN: {
			m_Packet *rpck = m_Packet_empty();

			m_Packet_write_varint(rpck, 0x00);
			m_Packet_write_string(rpck, "{\"text\": \"You want to play?\nServer not written lol.\",\"color\": \"red\",\"bold\": true}");
			m_Packet_write_lenght(rpck);

			m_Connection_write(con, rpck);
			break;
		}
	}
}
