# AlbumGenerator

<p>Be aware that this code is STILL under active development. I have begun integrating the doxygen comments into the headers but have a long way to go. The code is complex enough that it would be difficult to use right now, however, the structure diagrams in the doxygen files help. I will add some initial discription of how the design fits together in the near future. I will be documenting the build process and environment as soon as possible. If you are a seasoned C++ programmer and are still interested in helping just let me know.

<p>This is an application for maintaining an inventory and want list of stamps and visually creating a stamp album. It is designed to be cross platform but, as of now, has only been run on Linux Mint.
</p>
<p>The intention is that this App will be completely free. The input data is not propritary, the output is .pdf file  which can be read an printed, and the development environment tools and libraries are open source.
</p><p>
The app can import its catalog data from a comma seperated variable (.csv) file. I wrote the csv import to read Colnect export files for my list generation but the desires for additionally functionality exploded and I never got to the list. As a minimum it needs a csv file with the id, stamp name, height and width. or you can manually enter everything. Intermediate files are in XML for readability. The output is a pdf file which is printable.
</p><p>
Current State:<br>
It is starting to be useable( though I've recently buggered up the pdf generation) and stable. That means there is still a lot of little holes, and has had very little testing except for main paths. Specifically:
<ul>
<li>Modify and build to run on MS Windows and OSX.</li>
<li>Develop distribution package for each platform.</li>
<li>Much functionality in popup menus is only partially developed.</li>
<li>Develop text list generator of owned and wanted stamps.</li>
<li>Develop User and Developer Guide.</li>
<li>Much testing.</li>
</ul>
</p><p>
Development Environment:
<ul>
<li>C++,</li>
<li>WxWidgets 3.2.2.1,</li>
<li>VSCode,</li>
<li>Dialog Blocks <http://www.dialogblocks.com/></li>
</ul>
<p>Background: This program started out as a way to autogenerate a list of stamps I wanted. I got the idea to visually layout the stamps and generate an albumEasy file from the data but that evolved into me writing my own generator code.  I know there are a lot of these kinds of aps outther and probably way better than wht I've done. I am retired and looking for ways to keep my mnd active and this semed like a fun project for me. It keeps me busy and if someone else can find it useful then all the better.
<p>
AlbumGenerator is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation,  either version 3 of the License, or any later version.
</p><p>
AlbumGenerator is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
</p><p>
You should have received a copy of the GNU General Public License along with  AlbumGenerator. If not, see [][https://www.gnu.org/licenses](https://www.gnu.org/licenses)
</p>
