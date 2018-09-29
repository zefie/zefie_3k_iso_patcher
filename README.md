# zefie_3k_iso_patcher

How to use:

1. Create a raw, encrypted ISO dump
  * Via GameOS: multiMAN (via Direct Disc Access and Video column)
  * Via OtherOS: dd if=/dev/sr0 of=path/to/file.iso bs=2048
  * Via PC with BD Reader: Dump with ImgBurn
  
2. Insert disc into PS3, run [DumpKey - zefie edition](https://github.com/zefie/getkey_gameos_zefie) (Requires creating your own [3Dump.bin](http://forum.redump.org/post/61023/#p61023))
3. Place the ISO and /dev_usb000/disc.key (created by DumpKey - zefie edition) into to a folder together on your PC (if dealing with multiple isos, you can also rename "disc.key" to the same name as the file, eg dump.iso dump.key)
4. Run this program, with the first argument pointing to the ISO. (eg: ./zefie_3k_iso_patcher files/dump.iso)
5. Open [3k3y Tools v1.34.x](https://archive.midnightchannel.net/SonyPS/PS3/Windows%20Apps/3k3y%20IsoTools-1.34.7.7z)
6. Choose (from the menu bar) "Tools > ISO > Extract ISO"
7. Point to ISO, make a temp folder to extract the files to, choose a save path for your IRD
8. Let it do its thing
9. You have now made a valid IRD file!

Notes:

1. "Create IRD" button is broken in 3k3y which is why we do it this way.
2. If compiling on windows, use cygwin or msys, not visual studio
3. If 3k3y Tools is throwing an error regarding "Not a valid PS3 Disc", be sure your file extension is lowercase (eg ".iso" and NOT ".ISO")
