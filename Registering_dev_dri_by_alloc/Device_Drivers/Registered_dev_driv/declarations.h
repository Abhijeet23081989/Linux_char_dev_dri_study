#ifndef MAJR
#define MAJR 0
#endif

#ifndef MINR
#define MINR 0
#endif

#ifndef DEVNAME
#define DEVNAME "Abhijeet_dev_driver"
#endif
typedef struct
{
	struct Qset *next;
	void **data;
}Qset;
typedef struct
{
	struct Qset *first;
}DEV;
extern DEV *dev;
extern int new_majorno;
