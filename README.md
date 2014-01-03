# Preamble

This is the standalone version of the VGM2PRE VGM preset dumper. This app is a testbed for the preset conversion and dumping code that will be integrated into new VGMTool.

* Based on the previous VGM2TFI work by shiru.

# Compilation

Pre-built binaries for Windows will be available soon. Compiling this app requires nall, included, and will later require phoenix, included, for the GUI. Please be aware that the compilation process has only been confirmed to work on a MinGW-based environment.

1. Download this code into some directory.
2. Navigate to this code's directory and run <tt>make</tt>

# Installation

So far there's no installation; the compiled vgm2pre is a standalone executable and can be run from any directory. The pre-compiled 32-bit binary is confirmed to work on 32- and 64-bit Windows 7, and the 64-bit binary is confirmed to work on 64-bit Windows 7. Neither has been tested on Windows Vista or XP. Eventually there will be a Makefile that works on Linux.

# Usage

`vgm2pre`

Open the VGM2PRE GUI.

`vgm2pre path`

<var>path</var> can either be a file or a directory; if a file it will process that singular file, but if a directory it will process all the VGM/VGZ files in that given directory. Preset files are output into either the given directory or the same directory as the given file and duplicates are ignored. The loudest version of a given duplicate preset will be dumped.

<!--
`vgm2pre -pOPN abcdef path`

Passing <i>-pOPN</i> allows choosing which preset file formats are dumped from OPN-format VGMs (currently only YM2612 is supported). <var>abcdef</var> is six toggles, either 0 or 1, for the following formats in order:

1. VGI, for use with VGI-compatible apps such as shiru's VGM MM and Delek's DefleMask Tracker
2. TFI, for use with TFI-compatible apps such as shiru's TFM Maker and Aly James's FMDRIVE VSTi
3. TYI, for use with TYI-compatible apps such as superjoebob's YM2612 VSTi
4. EIF, for use with the Echo Sound Format
5. DMP, for use with DefleMask Tracker
6. Y12, currently unsupported and will only print to the console for now
-->

# The Math

A more detailed description of how presets are calculated and duplicates handled will be added here later. For now, we'll say that I use the same duplicate handling algorithms that shiru did in his VGM2TFI source.

# Disclaimer

This program is for personal use only; I, Alex Rosario, am not responsible for any damage, physical or digital, incurred through the use of this program, whether proper or improper.
