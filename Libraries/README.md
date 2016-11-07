hARMful
=======
hARMful is a project of making a whole experience of programming video games and
interaction 2D/3D applications on Raspberry Pi.

It stands for "Handy, Adapted to Raspi Multimedia and Fast Utilities Libraries".
It also makes a joke with the Raspberry Pi ARM CPU. Basically the project was
landed for a video game where player was projected in a harmful environment.

The project is composed of different "little" libraries (called "Extensions")
that can be used independently one of each other. You can even use them in
combination of other engines.
The main aim is to provide and share a base to generate all the applications the
developers want to make. A second aim is to avoid as far as possible useless
dependencies. In that way, the little the libraries use other libraries, the
better it is, because it can become very tricky to manage a lot of dependencies
on a such project!

Keep It Simple, Stupid!


DISDAINful
----------
It is the Damage + Inventory Systems and Dynamic Artificial Intelligence Network
extension.
It provides the basis to develop your own "artificial intelligences" and various
stuff for video games as characters management, character body, inventory
management, magics, weapons, etc.

Just inherit the classes from this library and adjust the behaviours to yours.

This library requires no dependency at all.


DOOMful
-------
It groups Debugging and Oriented-Object Modules.
Those utilities are used by all the other libraries, that's why it is not
directly integrated to the WISHful extension. For example, it includes threads
management to easily and properly end the application on fatal error.


GUILEful
--------
It is a Graphic User Interface Low-level Engine.
This one provides basic abstract classes to generate a GUI. As it does not
depend on extra library to display graphics, it is intended to be overloaded
through a full implementation by calling the wanted rendering library or engine.


HOPEful
-------
It stands for "Handy OpenGL and Physics Engines".
It displays 2D and 3D elements on screen. It only requires OpenGL and specific
Raspberry Pi APIs. A tiny physics engine is developed to ensure some basic
functions as gravity, and it can be improved with a true physics engine.


MINDful
-------
The "Mathematics Interface to New Developments" is used to manage matrix as
OpenGL did before recent releases. It means that users do not have to set tricky
things to make their models rotate, translate or scale for example.

It provides some functions with best accuracy VS the ones with best speed.
Moreover, it provides high performance features thanks to SSE2 and NEON.


SHAMEful
--------
It is the Shared Audio Management Extension. It can be used by at lot of
external engines.
You can load/play/repeat audio samples, musics and other audio stuff.
Of course, this depends on some well know external dependencies as libogg.


SPITEful
--------
It is the extension intended for Saving and Parsing Images, Texts and Extra.
As its name says, it is an extension to load pictures as PNG, JPEG... + some
other types of common formats (binary or ASCII).
It is not included directly in other project libraries as it depends on extra
libraries as libpng, libjpeg, etc. Yet, those external libraries may be
unwanted.


WISHful
-------
It is the Wide Interface for System and Hardware.
It may be useful to manage some drivers to use keyboards, mouses or even joypads
on Raspberry Pi. This extention is used to support such devices.

It is also where the basic display is done through the (deprecated) Dispmanx API
from Broadcom. As soon as OpenWF is fully supported - and if it happens one
day... - on Raspberry Pi, it could be easily replaced by this new API.
