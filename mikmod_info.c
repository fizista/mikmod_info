#include <mikmod.h>

#if defined(_WIN32)
#define MikMod_Sleep(ns) Sleep(ns / 1000)
#elif defined(_MIKMOD_AMIGA)
void amiga_sysinit (void);
void amiga_usleep (unsigned long timeout);
#define MikMod_Sleep(ns) amiga_usleep(ns)
#else
#include <unistd.h>  /* for usleep() */
#define MikMod_Sleep(ns) usleep(ns)
#endif

int main(int argc, char **argv)
{
	MODULE *module;

	if (argc < 2) {
		fprintf(stderr, "Usage: mikmod_info <file>\n");
		return 1;
	}

#ifdef _MIKMOD_AMIGA
	amiga_sysinit ();
#endif

	MikMod_InitThreads ();
	MikMod_RegisterDriver(&drv_nos);
	MikMod_RegisterAllLoaders();
	md_mode |= DMODE_SOFT_MUSIC | DMODE_NOISEREDUCTION;

	if (MikMod_Init("")) {
		fprintf(stderr, "Could not initialize sound, reason: %s\n",
				MikMod_strerror(MikMod_errno));
		return 2;
	}

	module = Player_Load(argv[1], 64, 0);
	if (module) {
		Player_Start(module);
		MikMod_Update();
		printf("%s}-{%s}-{%d\n", module->songname, module->modtype, (int) module->numchn);
		Player_Stop();
		Player_Free(module);
		MikMod_Exit();
		return 0;
	} else {
		fprintf(stderr, "Could not load module, reason: %s\n",
				MikMod_strerror(MikMod_errno));
		MikMod_Exit();
		return 1;
	}
}

