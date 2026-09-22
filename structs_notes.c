#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sensor {
    char name[50]; //50 = size
    float reading;
    char unit[10];

    void (*display)(struct Sensor* self); //struct used here bc technically Sensor isn't completely established
} Sensor;


//C doesn't have built-in inheritance, but it can be simulated through composition:
typedef struct NetworkSensor {
    Sensor base; //FIRST member - inherits everything from Sensor
    char ip_address[16];
    void (*transmit)(struct NetworkSensor* self);
} NetworkSensor;

void display_temperature(Sensor* self) {
    printf("%s: %.1f%s\n", self->name, self->reading, self->unit);
}

void display_pressure(Sensor* self) {
    printf("%s: %.1f%s (Standard: 1013 hPa)\n", self->name, self->reading, self->unit);
}

void network_sensor_transmit(NetworkSensor* self) {
    printf("Transmitting %s reading %.1f%s to %s\n", self->base.name, self->base.reading,
        self->base.unit, self->ip_address);
}

void network_sensor_display(Sensor* self) {
    NetworkSensor* net = (NetworkSensor*)self;
    printf("%s: %.1f%s [Network: %s]\n", net->base.name, net->base.reading, net->base.unit,
        net->ip_address);
}


//Syntax for the following two functions doesn't matter as much
//replaces having to do the big block of commented out code below
//these simulate constructor functions
void sensor_init_temp(Sensor* s, const char* name, float reading) {
    strncpy(s->name, name, 49);
    s->name[49] = '\0'; //needed when using strncpy instead of strcpy
    s->reading = reading;
    strcpy(s->unit, "C");
    s->display = display_temperature;
}
void sensor_init_pressure(Sensor* s, const char* name, float reading) {
    strncpy(s->name, name, 49);
    s->name[49] = '\0'; //needed when using strncpy instead of strcpy
    s->reading = reading;
    strcpy(s->unit, "hPa");
    s->display = display_pressure;
}

void network_sensor_init(NetworkSensor* ns, const char* name, float reading, const char* ip) {
    strncpy(ns->base.name, name, 49);
    ns->base.name[49] = '\0'; 
    ns->base.reading = reading;
    strcpy(ns->base.unit, "C");

    ns->base.display = network_sensor_display; //overrides base display to specialized display function

    strncpy(ns->ip_address, ip, 15);
    ns->ip_address[15] = '\0';
    ns->transmit = network_sensor_transmit;
}


int main() {
    //struct = collection of related members (variables)
    //         can be of different data types

    Sensor temp, pressure;
    sensor_init_temp(&temp, "Living Room", 22.5);
    sensor_init_pressure(&pressure, "Barometer", 1013.2);

    /*strcpy(temp.name, "Living Room"); //string copy function
    temp.reading = 22.5; //strcpy not needed with numbers
    strcpy(temp.unit, "C");
    temp.display = display_temperature; //sets function pointer (specific method that carries function from above)

    Sensor pressure;

    strcpy(pressure.name, "Barometer"); 
    pressure.reading = 1013.2; 
    strcpy(pressure.unit, "hPa");
    pressure.display = display_pressure; //different function


    /*void (*action)(int);

    action = print_double;
    action(5);

    action = print_square;
    action(5);*/

    temp.display(&temp);
    pressure.display(&pressure);


    Sensor basic;
    sensor_init_temp(&basic, "Room A", 21.0);

    NetworkSensor network;
    network_sensor_init(&network, "Room B", 22.5,"192.168.1.10");

    Sensor* all_sensors[2] = {
        &basic,
        (Sensor*)&network //cast NetworkSensor* to Sensor*
    };

    for (int i = 0; i < 2; i++) {
        all_sensors[i]->display(all_sensors[i]);
    }

    network.transmit(&network);

    return 0;

}
