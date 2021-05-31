#ifndef MAGICNO
#define MAGICNO 'K'
#endif

#ifndef RESETSYS
#define RESETSYS _IO(MAGICNO,1)
#endif

#ifndef GETQUANSIZE
#define GETQUANSIZE _IOR(MAGICNO,2,int)
#endif

#ifndef SETQUANSIZE
#define SETQUANSIZE _IOW(MAGICNO,3,int)
#endif

#ifndef GETQSETSIZE
#define GETQSETSIZE _IOR(MAGICNO,4,int)
#endif

#ifndef SETQSETSIZE
#define SETQSETSIZE _IOW(MAGICNO,5,int)
#endif

#ifndef GETDEVSIZE
#define GETDEVSIZE _IOR(MAGICNO,6,int)
#endif

#ifndef SETDEVSIZE
#define SETDEVSIZE _IOW(MAGICNO,7,int)
#endif

#ifndef GETBAUDRATE
#define GETBAUDRATE _IOR(MAGICNO,8,int)
#endif

#ifndef SETBAUDRATE
#define SETBAUDRATE _IOW(MAGICNO,9,int)
#endif
