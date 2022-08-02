# AlbumGenerator

<p>Be aware that this code is under active development. There is no documentation yet and is complex enough that it would be difficult to use right now. I will be documenting the build process and environment as soon as possible. if you are a seasoned C++ programmer and are still interested in helping just let me know. 

<p>This is an application for maintaining an inventory and want list of stamps and visually creating a stamp album. It is designed to be cross platform but, as of now, has only been run on Linux Mint.
</p>
<p>The intention is that this App will be completely free. The input data is not propritary, the output is Open Office text document file (.odt) which can be read and printed with open source software, and the development environment tools and libraries are open source.
</p><p>
The app can import its catalog data from a comma seperated variable (.csv) file. I wrote the csv import to read Colnect export files for my list generation but the desires for additionally functionality exploded and I never got to the list. As a minimum it needs a csv file with the id, stamp name, height and width. or you can manually enter everything. Intermediate files are in XML for readability. The output is an OpenOffice .odt file which is readable and modifiable by Open Office and (I think) by MSWord.
</p><p>
Current State:<br>
It is in an early state of developmet but is starting to be useable. That means there is still a lot to implement, and has had very little testing except for main paths. Specifically:
<ul>
<li>Modify and build to run on MS Windows and OSX.</li>
<li>Develop distribution package for each platform.</li>
<li>Use Colnect API to remotely retrieve images. (Currently images must reside on disk.)</li>
<li>Much functionality in popup menus is only partially developed.</li>
<li>Develop text list generator of owned and wanted stamps.</li>
<li>Develop User and Developer Guide.</li>
<li>Much testing.</li>
</ul>
</p><p>
Development Environment:
<ul>
<li>C++,</li>
<li>WxWidgets 3.2,</li>
<li>VSCode,</li>
<li>Dialog Blocks <http://www.dialogblocks.com/></li>
</ul>

<p>
AlbumGenerator is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation,  either version 3 of the License, or any later version.
</p><p>
AlbumGenerator is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
</p><p>
You should have received a copy of the GNU General Public License along with  AlbumGenerator. If not, see <https://www.gnu.org/licenses/>.
</p>
