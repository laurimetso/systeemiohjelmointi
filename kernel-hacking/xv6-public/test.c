#include "types.h" // xv6 type definitions
#include "user.h" // user space system call declaration

int
main(void)
{
	// store current number of read() calls before testing
	int before = getreadcount();

	// buffer to store data
	char  buf[10];
	// open readme in read only
	int fd = open("README",0);

	// read 10 bytes twice into buf
	read(fd,buf,10);
	read(fd,buf,10);

	// store updated count 
	int after = getreadcount();

	// print read count before and after testing
	printf(1, "before: %d\n", before);
	printf(1,"after: %d\n",after);
	exit();
}
