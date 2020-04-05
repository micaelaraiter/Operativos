/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include "tp0.h"
#include "stdio.h"
int main(void)
{
	/*---------------------------------------------------PARTE 2 - LOGGER + config -------------------------------------------------------------*/
		int conexion;
		char* ip;
		char* puerto;

		ip="127.0.0.1";
		puerto="4444";

		t_log* logger;
		t_config* config;
		config->path="tp0.config";


		logger = iniciar_logger();
		log_info(logger,"El Programa Funciona Correctamente"); // ejemplo de mensaje de info
		log_warning(logger,"El Programa Encontro un error"); // ejemplo mensaje warning

		config = leer_config();
		config_save(config);




		/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

		//antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

		//crear conexion

		//enviar mensaje

		//recibir mensaje

		//loguear mensaje recibido

		terminar_programa(conexion, logger, config);
	}

	//TODO
	t_log* iniciar_logger(void)
	{
		t_log_level level = LOG_LEVEL_INFO;
		return log_create("tp0.log","program0",1,level);
	}

	//TODO
	t_config* leer_config(void)
	{
		return config_create("tp0.config");
	}

	//TODO
	void terminar_programa(int conexion, t_log* logger, t_config* config)
	{
		log_destroy(logger);
		config_destroy(config);

	}
