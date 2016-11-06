// This is the system call test. 
#include <stdio.h>
#include <stdint.h>
#include "cpu.h"
#include "utilities.h"
#include "register_names.h"
#include "programming.h"

	void syscall() {

		int i;
		int x;
		int scan_integer;
		char scan_string[100];
		char read_string[11];

		switch (registers[2])
		{
			case 1:
				printf("%d\n", registers[4]);
				break;

			case 2:
				printf("print float is an error\n");
				cpu_exit(1);
				break;

			case 3:
				printf("print double is an error");
				cpu_exit(1);
				break;

			case 4: 
				printf("%s\n", &memory[registers[4]]);
				break;

			case 5:
				scanf("%d", &scan_integer);
				registers[2] = scan_integer;
				break;

			case 6:
				printf("read_float is not supported");
				cpu_exit(1);
				break;

			case 7:
				printf("read_double is not supported");
				cpu_exit(1);
				break;

			case 8:
				scanf("%d", &scan_string);
				for(i=0; i<= registers[5]; i++) { 
	      			memory[registers[4]++] = scan_string[i]; 
				}
	  			memory[registers[4]++] = 0; 
				break;

			case 9:
				printf("sbrk is not supported");
				cpu_exit(1);
				break;

			case 10:
				cpu_exit(0);
				break;

			default:
				printf("This is an erorr");
				cpu_exit(1);

		}
	}



