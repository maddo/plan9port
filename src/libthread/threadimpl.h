#include <ucontext.h>

typedef struct Context Context;
typedef struct Proc Proc;
typedef struct _Procrendez _Procrendez;

typedef struct Jmp Jmp;
struct Jmp
{
	p9jmp_buf b;
};

enum
{
	STACK = 8192
};

struct Context
{
	ucontext_t	uc;
};

struct _Thread
{
	_Thread	*next;
	_Thread	*prev;
	_Thread	*allnext;
	_Thread	*allprev;
	Context	context;
	uint	id;
	uchar	*stk;
	uint	stksize;
	int		exiting;
	void	(*startfn)(void*);
	void	*startarg;
	Proc	*proc;
	char	name[256];
	char	state[256];
};

struct _Procrendez
{
	Lock		*l;
	int		asleep;
#ifdef PLAN9PORT_USING_PTHREADS
	pthread_cond_t	cond;
#else
	int		pid;
#endif
};

extern	void	_procsleep(_Procrendez*);
extern	void	_procwakeup(_Procrendez*);

struct Proc
{
	Proc		*next;
	Proc		*prev;
	char		msg[128];
#ifdef PLAN9PORT_USING_PTHREADS
	pthread_t	osprocid;
#else
	uint		osprocid;
#endif
	Lock		lock;
	_Thread		*thread;
	_Threadlist	runqueue;
	_Threadlist	allthreads;
	uint		nthread;
	uint		sysproc;
	_Procrendez	runrend;
	Context	schedcontext;
	void		*udata;
	Jmp		sigjmp;
};

#define proc() _threadproc()
#define setproc(p) _threadsetproc(p)

extern Proc *_threadprocs;
extern Lock _threadprocslock;

extern void _procstart(Proc*, void (*fn)(Proc*));
extern _Thread *_threadcreate(Proc*, void(*fn)(void*), void*, uint);
extern void _threadexit(void);
extern Proc *_threadproc(void);
extern void _threadsetproc(Proc*);
extern int _threadlock(Lock*, int, ulong);
extern void _threadunlock(Lock*, ulong);
extern void _pthreadinit(void);
