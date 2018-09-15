# zefie_3k_iso_patcker

How to use:

1. Create raw ISO dump with multiMAN (via Direct Disc Access and Video column)
2. Run [DumpKey - zefie edition](https://github.com/zefie/getkey_gameos_zefie) (Requires creating your own [3Dump.bin](http://forum.redump.org/topic/12699/ps3-dumping-instructions/))
3. Transfer raw ISO + disc.key to a folder together
4. Run this program in that folder
5. Open 3k3y Tools v1.3.xx
6. Choose (from the menu bar) "Tools > ISO > Extract ISO"
7. Point to ISO, make a temp folder to extract the files to, choose a save path for your IRD
8. Let it do its thing
9. You have now made a valid IRD file!

Notes:

1. "Create IRD" button is broken in 3k3y which is why we do it this way.
2. If compiling on windows, use cygwin or msys, not visual studio