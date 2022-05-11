@page DeveloperInfo Developer Info
@tableofcontents
this is the developer info page
@section Design

The design of StampManager is really very straight forward. TinyXML-2 is used to read and write XML files containing all the stamp info. All the data is stored internally in this module, i.e., there are no classes in the SampManager code that store the stamp data. There are classes which wrap the wxXmlNode class to safely/conviently read and write the
data from the TinyXML-2 module. The bulk of the code is the wxWidget GUIs to display the data.


@section DevelopmentEnvironment Development Environment
This section is primarily for giving non-programmers a boost.  All the applications and libraries are freely available on Linux, Windows and Mac. I chose them because they are free and as a bonus cross-platform.  At this point I have only built on Linux though with very few exceptions there should be no issue building on another OS,

@subsection VSCode Visual Studio Code
I began using Microsoft Visual Studio back in the 90's and have used it of and on since.  I switched to MS Visual Studio Express for several years then migrated to using VSCode a few years when I migrated to Linux as my preferred work environment.  VSCode is powerful and can be tailored to nearly any way you want to work.  That said, it is sometimes hard to find exactly how to do something and sometime very hard to find exactly how to make it quit doing things you don't like.
Visual Studio Code is a lightweight but powerful source code editor which runs on your desktop and is available for Windows, macOS and Linux. 
<a href="https://code.visualstudio.com">Visual Studio Code Homepage</a> 
@subsection wxWidgets wxWidgets
wxWidgets is a C++ library that lets developers create applications for Windows, macOS, Linux and other platforms with a single code base.

<a href="https://wxwidgets.org/">wxWidgets Homepage</a> 

@subsection tinyxml2 TinyXML-2
TinyXML-2 is a simple, small, efficient, C++ XML parser that can be easily integrated into other programs.

<a href="https://github.com/leethomason/tinyxml2">TinyXML-2 Homepage</a> 
