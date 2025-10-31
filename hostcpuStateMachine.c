/*************************************************HOST CPU GPIO BMC APPLICATION*********************************************
 * File name: hostcpuStateMachine.c 
 * Library: Power on state machine control and monitor gpio pins from host cpu nxp2160A(64bit).
 * 
 * Author: st
 * Created: xx/xx/2025
 * 
 * Description: To power on state machine of AST2600A has control power down gpios of belows are with respect to host cpu nxp2160a
 *              gpios : 
 *			1. CPU_BOOT_HEARTBEAT         "446"  // host output  == > line no: 30  ===> chip1
 *			2. CPU_OPERATIONAL_HEARTBEAT  "447"  // host output  == > line no: 31  ===> chip1
 *			3. SYS_PWRDN_READY            "498"  \\ *host input  == > line no: 18  ===> chip3
 *			4. SYS_PWRDN_REQ              "499"  // host output  == > line no: 19  ===> chip3
 *			5. MODULE_PWRDN_READY         "500"  // host output  == > line no: 20  ===> chip3
 *			6. MODULE_PWRDN_REQ           "501"  \\ *host input  == > line no: 21  ===> chip3
 *			7. POWER_DOWN                 "503"  // host output  == > line no: 23  ===> chip3
 *
 *              These gpios are can trigger manually by below commands
 *              - gpioset --active-low gpiochipN N=0   to low the gpio
 *		- gpioset --active-low gpiochipN N=1   to high the gpio
 *              To run application in terminal as "./hostcpuStateMachine"
 *			***********outputs******************************
 *			gpioset --active-low gpiochip1 30=0    CPU_BOOT_HEARTBEAT
 *			gpioset --active-low gpiochip1 31=0    CPU_OPERATIONAL_HEARTBEAT
 *			gpioset --active-low gpiochip3 19=0    SYS_PWRDN_REQ
 *			gpioset --active-low gpiochip3 20=0    MODULE_PWRDN_READY
 *			gpioset --active-low gpiochip3 23=0    POWER_DOWN
 *			***********inputs******************************
 *			gpioget --active-low gpiochip3 21      MODULE_PWRDN_REQ
 *			gpioget --active-low gpiochip3 18      SYS_PWRDN_READY     
 *
 * Test application on HOST STATEMACHINE LOGIC
 * 	-After Power on of host cpu boot heartbeat will generate the pulse up to 60 secs
 *	-poweron booting indication(cpu boot heartbeat)
 *	-wait 1 min then
 *	-1. turnon operational heartbeat, 2. continue poweron booting indication(boot heartbeat) up to 10 secs.
 *	-wait 10secs.
 *	-turnoff booting indication(boot heart beat).
 *	-operational heart beat will continue.
 *	-based on the bmc input(Power button  pressed less than 5 secs  or remote command soft power off) then 
 *	BMC will trigger module power down request,
 *	if  module power down request high then Host will trigger MODULE_P WRDN_READYn and SYS_PWRDN_REQn  after 60s then  
 *	Once the BMC receive MODULE_P WRDN_READYn or SYS_PWRDN_REQn signal, it will send the Signal of SYS_PWRDN_READYn to Host.
 *      Host will Monitor SYS_PWRDN_READYn of BMC signal if it is received then HOST will trigger POWER _DOWN_N after
 *	60 secs delay. 
 *      BMC will turn off the PSU after certain delay.
*****************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>

int VERBOSE = 0;
#define MAX_LEN  128
#define BOOT_HEARTBAEAT 120
#define POWER_CTRL_DELAY 60
#define BOOT_PULSES 10

#define LOG(fmt, ...) \
    do { if (VERBOSE) printf("[LOG] " fmt "\n", ##__VA_ARGS__); } while (0)
    
struct gpio_toggle_args {
    int chip;
    int line;
};

void* gpio_toggle_thread(void* arg) {
    struct gpio_toggle_args* gpio = (struct gpio_toggle_args*)arg;
    int value = 0;
    int ret;
    char cmd[MAX_LEN];

    while (1) {
        value = !value;
        snprintf(cmd, sizeof(cmd), "gpioset --active-low gpiochip%d %d=%d", gpio->chip, gpio->line, value);
        //printf("Running: %s\n", cmd);
        LOG("Toggling GPIO: %s", cmd);
        ret = system(cmd);
        if (ret == -1) {
            perror("system");
            pthread_exit(NULL);
        }
        usleep(600000); // 0.5 seconds
    }

    return NULL;
}


int read_gpio(int chip, int line) {
    char cmd[MAX_LEN];
    char result[16];
    FILE *fp;

    snprintf(cmd, sizeof(cmd), "gpioget --active-low gpiochip%d %d", chip, line);
    fp = popen(cmd, "r");
    if (fp == NULL) {
        perror("popen failed");
        return -1;
    }

    if (fgets(result, sizeof(result), fp) == NULL) {
        perror("fgets failed");
        pclose(fp);
        return -1;
    }
    //printf("Running: %s : %s\n", cmd,result);
    //LOG("Read GPIO: %s : %s\n", cmd,result);
    pclose(fp);
    return atoi(result); // 0 or 1
}


void toggle_gpio(const int chip, const int line, int value) {
    char cmd[MAX_LEN];
    snprintf(cmd, sizeof(cmd), "gpioset --active-low gpiochip%d %d=%d", chip, line, value);
    //printf("Running: %s\n", cmd);
    LOG("Toggling GPIO: %s", cmd);
    int ret = system(cmd);
    if (ret == -1) {
        perror("system");
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "v") == 0) {
        VERBOSE = 1;
    }
    LOG("Started Host cpu state machine");
    const int heartbeat_chip = 1;       	// gpiochip for boot heartbeat and operational heartbeat number
    const int powergpio_chip = 3;               // gpiochip for POWER ON STATE MACHINE number
    const int bt_hrtbt_line = 30;      		// GPIO cpu boot heartbeat line number
    const int oper_hrtbt_line = 31;      	// GPIO cpu operational heartbeat  line number
    
    const int sys_pwrdnRd_line = 18;        // input GPIO system power down ready
    const int sys_pwrdnRq_line = 19;	    // GPIO module powerdown request line number
    const int mod_pwrdnRd_line = 20;	    // GPIO module powerdown ready line number	
    const int mod_pwrdnRq_line = 21;        // GPIO module powerdown request line number
    const int power_down_line = 23;         // GPIO powerdown line number

    int value = 1, def_val=0;      // Initial toggle value
    int ret;
    char cmd[MAX_LEN];
    
    pthread_t toggle_thread;
    struct gpio_toggle_args args = {
        .chip = heartbeat_chip,      // gpiochip1
        .line = oper_hrtbt_line      // GPIO line number (oper_hrtbt_line)
    };
    
    toggle_gpio(heartbeat_chip, bt_hrtbt_line, def_val);
	toggle_gpio(heartbeat_chip, oper_hrtbt_line, def_val);
	
	toggle_gpio(powergpio_chip, sys_pwrdnRq_line, def_val);
	toggle_gpio(powergpio_chip, mod_pwrdnRd_line, def_val);
	toggle_gpio(powergpio_chip, power_down_line, def_val);
	// read_gpio(powergpio_chip, sys_pwrdnRd_line);
	//read_gpio(powergpio_chip, mod_pwrdnRq_line);
	LOG("Module Power Down Req Pin :%d \n ", read_gpio(powergpio_chip, mod_pwrdnRq_line));
	LOG("Sytem Power Down Ready Pin :%d \n ", read_gpio(powergpio_chip, sys_pwrdnRd_line));
	
	usleep(1000000);  // delay for 1 seconds
    for (int i = 0; i < BOOT_HEARTBAEAT; i++) {
        value = !value;
        snprintf(cmd, sizeof(cmd), "gpioset --active-low gpiochip%d %d=%d", heartbeat_chip, bt_hrtbt_line, value);
        //printf("Running: %s\n", cmd);
        LOG("Toggling GPIO: %s", cmd);
        ret = system(cmd);
        if (ret == -1) {
            perror("system");
            return 1;
        }
        usleep(700000); // Sleep for 700ms (0.7s)
    }
  
    for (int i = 0; i < BOOT_PULSES; i++) {
        value = !value;
    	toggle_gpio(heartbeat_chip, bt_hrtbt_line, value);
		toggle_gpio(heartbeat_chip, oper_hrtbt_line, value);
        usleep(700000); // Sleep for 700ms (0.7s)
    }  
    
    toggle_gpio(heartbeat_chip, bt_hrtbt_line, def_val);  //stop the cpu boot heartbeat after 10 seconds
    
   
    if (pthread_create(&toggle_thread, NULL, gpio_toggle_thread, &args) != 0) {
        perror("Failed to create toggle thread");
        return 1;
    }
        
    // Main thread can continue doing other things here
    // For example, just wait forever
    //pthread_join(toggle_thread, NULL);
	
	int powerdownfalg =0;
	while(1) {
		LOG("Sytem Power Down  Ready Pin :%d, Module power Down Req Pin: %d \n ", read_gpio(powergpio_chip, sys_pwrdnRd_line),\
		 read_gpio(powergpio_chip, mod_pwrdnRq_line));
		 
		if (read_gpio(powergpio_chip, mod_pwrdnRq_line)){
			powerdownfalg =0;
			def_val=1;
			LOG("Module Power Down Req Pin :%d \n ", read_gpio(powergpio_chip, mod_pwrdnRq_line));
			sleep(POWER_CTRL_DELAY);
			toggle_gpio(powergpio_chip, sys_pwrdnRq_line, def_val);
			toggle_gpio(powergpio_chip, mod_pwrdnRd_line, def_val);
			if(read_gpio(powergpio_chip, sys_pwrdnRd_line))
			{
				LOG("Sytem Power Down  Ready Pin :%d \n ", read_gpio(powergpio_chip, sys_pwrdnRd_line));
				sleep(POWER_CTRL_DELAY);
				toggle_gpio(powergpio_chip, power_down_line, def_val);	
			}
		}
		else {
			def_val=0;
			if (! powerdownfalg)
				{
				toggle_gpio(powergpio_chip, sys_pwrdnRq_line, def_val);
				toggle_gpio(powergpio_chip, mod_pwrdnRd_line, def_val);
				toggle_gpio(powergpio_chip, power_down_line, def_val);
				powerdownfalg =1;
				}
			usleep(500000); // Sleep for 500ms (0.5s)
    		}
    	}
    return 0;
}


