[NAME]
irxevent - infrared X-event sender

[DESCRIPTION]
Irxevent is a program that I wrote to send button clicks and key presses to X
applications triggered by a LIRC driven remote control. You can control your
favorite CD/MP3 player or your TV tuner program or any other X application
that responds to keyboard or mouse input. If you like to you can send emacs
^X^S from your armchair.

Irxevent is a complement to irexec and irpty.

[FILES]
Irxevent works with the same config file as irexec and irpty (~/.lircrc). For
a complete sample .lircrc look at examples/lircrc.

.B Part of your .lircrc could look like this:

.nf
.RS 3
begin
        prog = irxevent
        button = VIDEO_UP    
        config = Key SHIFT-KP_Add CurrentWindow
end
begin
        prog = irxevent
        button = VIDEO_DOWN
        config = Key SHIFT-KP_Subtract CurrentWindow
end
begin
        prog = irxevent
        button = STOP
        config = Key ctrl-c CurrentWindow
end
begin
        prog = irxevent
        button = 0
        config = Key f xawtv
        config = Key f xawtv
end
begin
        prog = irxevent
        button = POWER
        config = Key q xawtv
end
begin
        prog = irxevent
        button = CH_DOWN
        config = Button 1 329 92 kscd
end
begin
        prog = irxevent
        button = UP
        config = Button 1 110 80 GQmpeg
end
begin
        prog = irxevent
        button = DOWN
        config = Button 1 130 80 GQmpeg
end
.RE
.fi

.B Simply said \fIconfig\fB =  lines may look like this:

.nf
.RS 3
config = Key [shift-][ctrl-][alt-]<key> <windowname> | CurrentWindow
config = Button <button> <x> <y> <windowname> | CurrentWindow
config = xy_Key <x> <y> [shift-][ctrl-][alt-]<key> <windowname> | CurrentWindow
.RE
.fi

.B some more examples:

.nf
.RS 3
config = Key Up xawtv
config = Key Down xawtv
config = Button 1 50 110 xclickme
config = Key q xawtv
config = Key ctrl-c mpg123
config = Key shift-Page_Up rxvt
.RE
.fi

.B In BNF this looks like:

.RS 3
.nf
LINE    = "config =" <KEY|BUTTON|XYKEY> <TARGET>
XYKEY   = "xy_Key" <x_position> <y_position> <MOD>Keyname
KEY     = "Key" <MOD>Keyname
MOD     = ["shift-"]["numlock-"]["ctrl-"]["alt-"]["meta-"]
          ["numlock-"]["mod3-"]["mod4-"]["scrlock-"]
BUTTON  = "Button" <1..5> <x_position> <y_position>
TARGET  = Windowname | "CurrentWindow"
.fi

.I Keyname:
.RS 2
is the key symbol that is declared in X windows. E.g. "Up" refers to the
cursor arrow pointing up. "KP_Add" is the plus sign on the key pad. Just take
a look at irxevent.keys (in the documentation directory) if you are not sure
about a symbol's name.
.RE
.I Windowname:
.RS 2
can be the first characters of the window name displayed by the window manager
or the name that is displayed below the icon. Some programs use the name
displayed by the window manager to show a lot of status information but don't
change the icon name (like xawtv). Others append information to the window
name ("GQmpeg - kill_windooz.mp3"). If neither window name nor icon name match
the given Windowname information from XClassHint(3x) will be checked.
.RE
.I CurrentWindow:
.RS 2
refers to the active window as returned by XGetInputFocus(3x). Most times this
is the window with your mouse pointer in it.
.RE
.RE

[TROUBLESHOOTING]

If you have problems finding the coordinates for a button click you can try
xev -id <window_id>. The window_id can be found using xwininfo. If xev and
xwininfo are not part of your distribution you can find them at a FTP server
using the search engine at: http:\/\/ftpsearch.ntnu.no/ . xev also reports the
names of key symbols like "Control_L" (your left control key) or "KP_Subtract"
(the 'minus' key on your keypad).

There are programs that do not accept any synthetic X-events by default
because they can cause security problems. Currently xterm and xemacs are known
to ignore events simulated by irxevent.

You can however make xterm accept external events by enabling "Allow
SendEvents" in the "Main Options" (hold down the Ctrl button and press the
left mouse button inside the xterm window). You can as well place this line
into your .Xresources file to change this permanently:

.RS 3
XTerm.vt100.allowSendEvents: true
.RE

Yet another possibility is to start xterm like this:

.RS 3
xterm -xrm "XTerm.vt100.allowSendEvents: true"
.RE

xemacs will accept events if you set a built-in variable. The following was
taken from the online help:

.RS 3
`x-allow-sendevents' is a built-in boolean variable.

Value: t

Documentation:

*Non-nil means to allow synthetic events.  Nil means they are ignored.

Beware: allowing emacs to process SendEvents opens a big security hole.

In order to allow events you have to evaluate this lisp code (press Meta-x and
enter the following expression):

	 (setq x-allow-sendevents t)

Placing this line into your .xemacs-options file should have the same result.
.RE

If you have problems sending events please drop me an email.

[AUTHOR]
Written by Heinrich Langos <heinrich@mad.scientist.com>.