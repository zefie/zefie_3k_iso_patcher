zefie_3k_iso_patcher : zefie_3k_iso_patcher.c
	cc -O2 -mtune=native -static zefie_3k_iso_patcher.c -o zefie_3k_iso_patcher

clean :
	rm zefie_3k_iso_patcher