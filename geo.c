#include <maxminddb.h>
#include <string.h>
#include <stdio.h>
// g++ -o test geo.c -lmaxminddb

int main(void)
{
	int gai_error, mmdb_error;
	MMDB_s mmdb;
	char *ip = "8.8.8.8";
	int status = MMDB_open("/home/lannister/Documentos/GeoLite2-City.mmdb", MMDB_MODE_MMAP, &mmdb);

	if (MMDB_SUCCESS != status) { 
		printf("Fail WTF"); 
	}

	MMDB_lookup_result_s result = MMDB_lookup_string(&mmdb, ip, &gai_error, &mmdb_error);

	if (MMDB_SUCCESS != mmdb_error) { 
		printf("Fail WTF2"); 
	}

	int exit_code = 0;
	char *country = NULL;

	MMDB_entry_data_s entry_data;

	status = MMDB_get_value(&result.entry, &entry_data,"city","names","es", NULL);
	if (entry_data.has_data) { 
		country =  strndup(entry_data.utf8_string, entry_data.data_size);
		printf("%s\n", country);
	}else{
		printf("No city");
	}

	status = MMDB_get_value(&result.entry, &entry_data,"country","names","es", NULL);
	if (entry_data.has_data) { 
		country =  strndup(entry_data.utf8_string, entry_data.data_size);
		printf("%s\n", country);
	}

	MMDB_close(&mmdb);
 return 0;
}