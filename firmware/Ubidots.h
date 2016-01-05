#ifndef __Ubidots_H_
#define __Ubidots_H_
#define DEBUG_UBIDOTS

#include "application.h"
#include "spark_wiring_string.h"
#include "spark_wiring_tcpclient.h"
#include "spark_wiring_usbserial.h"
#include <stdarg.h>

#define USER_AGENT  "Ubidots/v1 Particle/1.0"
#define BASE_URL  "things.ubidots.com"
#define ATTEMPS  10
#define BUFFER_HTTP_SIZE 1500

typedef struct Value {
    char *name;
    float value;
    char *id;
    Value *next;
} Value;

typedef struct UbidotsCollection {
    char * id_datasource_default;
    Value *first;
} UbidotsCollection;

class ubidots {
 public:
    ubidots(char* token);
    char* get_or_create_datasource();
    char* get_or_create_variable(char* ID, char* variableName);
    bool send(char* chain, char* status, char* body, unsigned int size);
    char* parser_id(char* status, char* body);
    bool send_with_reconnect(char* chain, char* status, char* body, unsigned int size);
    
        
    int ubidots_collection_save(UbidotsCollection *collection);
    void ubidots_collection_cleanup(UbidotsCollection *collection);
        
    void add_value_with_name(UbidotsCollection *collection, char * name, double value);
    void add_value(UbidotsCollection *collection, char * variable_id, double value);
        
        
    bool send_ubidots(int number, ... );
    char* _token;

 private:
    char* assemble(char* method, char* endpoint);
    char* assemble_with_data(char* method, char* endpoint, char* data);
    Value * check_init_value(UbidotsCollection *collection, char* name, double value, char * id);
    UbidotsCollection * cache;
        

};
#endif