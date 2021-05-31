#ifndef DEBUG
#define DEBUG 
#endif

#ifndef MAJR
#define MAJR 0
#endif

#ifndef MINR
#define MINR 0
#endif

#ifndef NOD
#define NOD 1
#endif

#ifndef DEVNAME
#define DEVNAME "Lagertha"
#endif

#ifndef NOOFREG
#define NOOFREG 8
#endif

#ifndef REGSIZE
#define REGSIZE 4
#endif

#ifndef DEVSIZE
#define DEVSIZE 1024
#endif

#ifndef DATASIZE
#define DATASIZE 0
#endif

//_____________for Items(Number of Applications)______________
typedef struct Qset
{
	struct Qset *next;
	//Qset *next;
	void **data;
}Qset;
//_____________________For Device_____________________________
typedef struct
{
	Qset *first;
	struct cdev mycdev;
	int noofreg;//no. of registers
	int regsize;//register size 
	int devsize;//Device size
	int datasize;//Data size
	struct semaphore s1;
	struct rw_semaphore r1;
}DEV;
extern DEV *dev;
extern dev_t devno;
extern int nod;
//____________________For Book Keeping of driver_______________
extern int noofreg,regsize,devsize,datasize;
//____________________prototypes of kernel routies_____________
int opendev(struct inode*, struct file*);
int releasedev(struct inode*, struct file*);
ssize_t readdev (struct file*, char __user *, size_t, loff_t*);
ssize_t writedev(struct file *, const char __user *, size_t, loff_t *);
loff_t llseekdev(struct file *, loff_t, int);
int trimdev(DEV*);
Qset* createscull(int);
