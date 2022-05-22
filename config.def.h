/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 2;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 2;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 0;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;    	/* 0 means no systray */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "IBM Plex Mono:size=9","twemoji:pixelsize=9:antialias=true:autohint=true","Fira Code Medium:size=9", "fontawesome-regular:size=9","monospace:size=9","Font Awesome 6 Free Solid:size=9"/*"IBMPlexMono-Regular:pixelsize=9"*/ /*"JoyPixels*/};
static const char dmenufont[]      = "IBM Plex Mono:size=9";
/*static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {*/
	/*               fg         bg         border   */
/*	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};*/

static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
       const char *name;
       const void *cmd;
} Sp;                                                                                                            
//const char *spcmd1[] = {"kitty", "-T", "spterm", NULL };
//const char *spcmd2[] = {"kitty", "-T", "calcterm","-o", "font_size=14", "R", "-q", NULL };
const char *spcmd1[] = {"alacritty", "-t", "spterm", NULL };
const char *spcmd2[] = {"alacritty", "-t", "calcterm","-o", "font_size=14","-e", "R", "-q", NULL };
const char *spcmd3[] = {"keepassxc", NULL };
static Sp scratchpads[] = {
       /* name          cmd  */
       {"spterm",      spcmd1},
       {"termcalc",    spcmd2},
       {"keepassxc",   spcmd3},
};


static const char *const autostart[] = {
	"deadd-notification-center", NULL,
	"copyq", NULL,
	"playrectld","daemon", NULL,
	"flameshot", NULL,
	"dwmblocks", NULL,
	"lock", NULL,
	"sxhkd", NULL,

	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor  float x,y,w,h      floatborderpx */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1,      50,50,1896,1040,   1  },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1,      50,50,500,500,     4  },
	{ "st",      NULL,     NULL,           0,         0,          1,           0,        -1,      50,50,500,500,     4  },
	{ "kitty",   NULL,     NULL,           0,         0,          1,           0,        -1,      50,50,500,500,     4  },
	{ "Alacritty", NULL,   NULL,           0,         0,          1,           0,        -1,      50,50,500,500,     4  },
	{ "nnn",     NULL,     NULL,           0,         0,          1,           0,        -1,      50,50,500,500,     4  },
	{ "handlr",  NULL,     NULL,           0,         0,          1,           0,        -1,      50,50,500,500,     4  },
	{ "Discord", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1,      50,50,500,500,     4  },
	{ "Panther", NULL,     NULL,           0,         1,          0,          -1,        -1,      1900,1060,500,500, 2  },
	{ "bms_linux", NULL, NULL,             0,         0,          0,          -1,        -1,      0,0,1920,1080,     0  },
	{ "Picture-in-Picture", "Picture-in-Picture", "Picture-in-Picture",0,0,       0,          -1,        -1,      50,50,500,500,     4  },
	{ NULL,      NULL,   "spterm",         SPTAG(0),  1,         -1,          -1,         0,      240,1100,1400,800,   8  },
        { NULL,      NULL,   "calcterm",       SPTAG(1),  1,         -1,          -1,         0,      710,225,500,250,   4  },
        { NULL,     "keepassxc", NULL,         SPTAG(2),  0,         -1,          -1,        -1,      50,50,500,500,     2  },
	{ NULL,      NULL,   "cmus",           0,         1,         -1,          -1,        -1,      240,110,1400,800,   4  },
	{ "copyq",      NULL,   NULL,           0,         1,         -1,          -1,        -1,      140,110,800,900,   4  },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1,      50,50,500,500,     4  }, /* xev */
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_n,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_e,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_t,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_b,     ACTION##stack, {.i = -1 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define SHCMDZSH(cmd) { .v = (const char*[]){ "/bin/zsh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
//static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "alacritty", NULL };


/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
};

#include <X11/XF86keysym.h>
#include "shift-tools.c"


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ALTKEY,                XK_o, shiftviewclients,    { .i = +1 } },
	{ MODKEY,             		XK_u,	shiftview,         { .i = +1 } },
	{ MODKEY,	      		XK_l,	shiftview,         { .i = -1 } },
	{ MODKEY|ALTKEY,                XK_y, shiftviewclients,    { .i = -1 } },
	{ MODKEY|ControlMask,           XK_b,      togglebar,      {0} },
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_m,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_m,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_i,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,		XK_l,      shiftboth,      { .i = -1 }	},
	{ MODKEY|ControlMask,           XK_l,      shiftswaptags,  { .i = -1 }	},
	{ MODKEY|ControlMask,   	XK_u,      shiftswaptags,  { .i = +1 }	},
	{ MODKEY|ShiftMask,             XK_u,      shiftboth,      { .i = +1 }	},
	{ MODKEY|ALTKEY,                XK_z,      incrgaps,       {.i = +1 } },
	{ MODKEY|ALTKEY,                XK_x,      incrgaps,       {.i = -1 } },
/*	{ MODKEY|ALTKEY|ShiftMask,      XK_m,      incrogaps,      {.i = +1 } },
	{ MODKEY|ALTKEY|ShiftMask,      XK_i,      incrogaps,      {.i = -1 } },
	{ MODKEY|ALTKEY|ControlMask,    XK_m,      incrigaps,      {.i = +1 } },
	{ MODKEY|ALTKEY|ControlMask,    XK_i,      incrigaps,      {.i = -1 } },*/
	{ MODKEY,                       XK_g,      togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_g,      defaultgaps,    {0} },
/*	{ MODKEY|ALTKEY,                XK_Right,  incrihgaps,     {.i = +1 } },
	{ MODKEY|ALTKEY,                XK_Left,   incrihgaps,     {.i = -1 } },
	{ MODKEY|ALTKEY,                XK_Up,     incrivgaps,     {.i = +1 } },
	{ MODKEY|ALTKEY,                XK_Down,   incrivgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_Right,  incrohgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_Left,   incrohgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_Right,  incrovgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_Left,   incrovgaps,     {.i = -1 } },*/
	{ MODKEY,                       XK_space, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
//	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ControlMask,           XK_t,      setlayout,      {.v = &layouts[0]} },//Tiling
	{ MODKEY|ControlMask,           XK_f,      setlayout,      {.v = &layouts[1]} },//floating
	{ MODKEY|ControlMask,           XK_m,      setlayout,      {.v = &layouts[2]} },//monacle
	{ MODKEY,        		XK_f,      fullscreen,     {0} },
	{ MODKEY|ShiftMask,             XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefloating, {0} },
	{ MODKEY|ALTKEY,                XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	//******** Scratchpads
	{ 0|ControlMask|ALTKEY,         XK_Return, togglescratch,  {.ui = 0 } },//scratchpad 
        { MODKEY,                       XK_c,      togglescratch,  {.ui = 1 } },//calculator
        { MODKEY|ControlMask,           XK_x,      togglescratch,  {.ui = 2 } },//keepassxc	
	//******** System
	//{ MODKEY|ControlMask,           XK_s,      spawn,          SHCMD("systemctl suspend") },//suspend
    { MODKEY,                    XK_BackSpace, spawn,          SHCMD("betterlockscreen -l") },  //lock
	{ MODKEY|ControlMask,           XK_q,      spawn,          SHCMD("sysact") },         //logout
	//******** Programs
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,	      		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,        		XK_r,      spawn,          SHCMD("thunar") },
	{ MODKEY|ALTKEY,             XK_Return, spawn,          SHCMDZSH("emacs") },//{.v = termfm } },
	//{ MODKEY|ShiftMask,             XK_Return, spawn,          SHCMDZSH("kitty nnn -a -c -P p") },//{.v = termfm } },
	//{ MODKEY|ControlMask,           XK_Return, spawn,          SHCMDZSH("kitty nnn -a -e -P p") }, //{.v = termfmedit } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          SHCMDZSH("alacritty -e nnn -a -c") },//{.v = termfm } },
	{ MODKEY|ShiftMask|ALTKEY,      XK_Return, spawn,          SHCMDZSH("alacritty -e nnn -a -c -P b") },//{.v = termfm } },
	{ MODKEY|ShiftMask|ControlMask, XK_Return, spawn,          SHCMDZSH("alacritty nnn -a -e") }, //{.v = termfmedit } },
	//{ MODKEY,                       XK_w,      spawn,          SHCMDZSH("$BROWSER") },
	//{ 0|ControlMask|ALTKEY,         XK_Delete, spawn,          SHCMD("kitty btop") }, 
    //{ MODKEY|ShiftMask,             XK_m,      spawn,          SHCMDZSH("kitty -T cmus screen -q -r -D cmus || screen -S cmus $(which --skip-alias cmus)") },
	{ 0|ControlMask|ALTKEY,         XK_Delete, spawn,          SHCMD("alacritty -e btop") }, 
    { MODKEY|ALTKEY,                XK_m,      spawn,          SHCMDZSH("alacritty -t cmus -e screen -q -r -D cmus || screen -S cmus $(which --skip-alias cmus)") },
	{ 0,                            XK_Print,  spawn,	   SHCMD("spectacle --fullscreen --background") },
	//{ MODKEY,                       XK_s,      spawn,          SHCMD("spectacle --region --background") },
	//{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("spectacle --region --background --copy-image") },
	//{ MODKEY|ALTKEY,                XK_s,      spawn,          SHCMD("flameshot gui") },
	//{ MODKEY,                       XK_v,      spawn,          SHCMD("copyq menu") },
	{ MODKEY,                       XK_h,      spawn,          SHCMD("panther_launcher") },
	{ MODKEY|ShiftMask,             XK_c,      spawn,          SHCMD("kill -s USR1 $(pidof deadd-notification-center)") },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          SHCMD("keepmenu") },//{.v = keepmenu } },
    { MODKEY|ControlMask,           XK_v,      spawn,          SHCMD("copyq toggle") },//copyq
    //{ MODKEY|ControlMask,           XK_e,      spawn,          SHCMD("easyeffects") },//easyeffects
    { MODKEY|ALTKEY,                XK_h,      spawn,          SHCMD("groff -mom ~/.dwm/help/dwm-help.mom -Tpdf | zathura -") },//help menu
    //{ MODKEY,                       XK_p,      spawn,          SHCMD("cabl") },

	
        { 0, XF86XK_AudioMicMute,               spawn,          SHCMD("amixer set Capture toggle; kill -47 $(pidof dwmblocks)") },	
       /* { 0, XF86XK_Launch5,               spawn,          SHCMD("") },	
        { 0, XF86XK_Launch6,               spawn,          SHCMD("") },	
        { 0, XF86XK_Launch7,               spawn,          SHCMD("") },	
        { 0, XF86XK_Launch8,               spawn,          SHCMD("") },	
        { 0, XF86XK_Launch9,               spawn,          SHCMD("") },	
        { 0, XF86XK_Tools,               spawn,          SHCMD("") },	
        { 0, XF86XK_Tools,               spawn,          SHCMD("") },	
        { 0, XF86XK_TouchpadToggle,               spawn,          SHCMD("") },	
        { 0, XF86XK_TouchpadOn,               spawn,          SHCMD("") },	
        { 0, XF86XK_TouchpadOff,               spawn,          SHCMD("") },*/	
        
	{ 0, XF86XK_Mail,               spawn,          SHCMD("thunderbird") },	
//        { 0, XF86XK_HomePage,           spawn,          SHCMDZSH("$BROWSER") },	
        { 0, XF86XK_Forward,            spawn,          SHCMD("brave") },	
        { 0, XF86XK_Back,               spawn,          SHCMD("tabbed -c surf -e") },	
        { 0, XF86XK_Explorer,           spawn,          SHCMD("thunar") },	
        { 0, XF86XK_Sleep,              spawn,          SHCMD("systemctl suspend") },	
        { 0, XF86XK_WakeUp,             spawn,          SHCMD("sysact") },
	{ 0, XF86XK_PowerOff,		spawn,		SHCMD("sysact") },
	{ 0, XF86XK_Calculator,		spawn,		SHCMD("kcalc") },
	{ 0, XF86XK_Favorites,		spawn,		SHCMD("panther_launcher") },
	{ 0, XF86XK_Reload,		quit,        {0} },
        
/*	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("monbrightcontrol 1 15") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("monbrightcontrol 1 -15") },
	{ 0|ControlMask, XF86XK_MonBrightnessUp,	spawn,		SHCMD("monbrightcontrol 2 15") },
	{ 0|ControlMask, XF86XK_MonBrightnessDown,	spawn,		SHCMD("monbrightcontrol 2 -15") },
	{ 0|ALTKEY, XF86XK_MonBrightnessUp,	spawn,		SHCMD("monbrightcontrol 3 15") },
	{ 0|ALTKEY, XF86XK_MonBrightnessDown,	spawn,		SHCMD("monbrightcontrol 3 -15") },*/

	{ 0, XF86XK_AudioMute,		spawn,		SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer -i 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer -d 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPrev,		spawn,		SHCMD("playerctl previous; kill -52 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioNext,		spawn,		SHCMD("playerctl next; kill -52 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPause,		spawn,		SHCMD("playerctl play-pause; kill -52 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPlay,		spawn,		SHCMD("playerctl play-pause; kill -52 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioStop,		spawn,		SHCMD("playerctl stop; kill -52 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRewind,	spawn,		SHCMD("playerctl position -10; kill -52 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioForward,	spawn,		SHCMD("playerctl position +10; kill -52 $(pidof dwmblocks)") },
	
	//Mouse Control
#define Button6 6
#define Button7 7
#define Button8 8
#define Button9 9
	{ MODKEY|ShiftMask,             Button6,  focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             Button7, focusmon,       {.i = +1 } },
	{ MODKEY,                       Button6,  tagmon,         {.i = -1 } },
	{ MODKEY,                       Button7, tagmon,         {.i = +1 } },
	{ MODKEY|ControlMask,  		Button7,	shiftview,         { .i = +1 } },
	{ MODKEY|ControlMask,  		Button6,	shiftview,         { .i = -1 } },
	
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ControlMask,           XK_BackSpace, quit,        {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
/*
 * Button1 = Left Click
 * Button3 = Right Click
 * Button2 = Middle Click
 * Button4 = Scroll Up
 * Button5 = Scroll Down
 */

static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },

	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
        { ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
        { ClkStatusText,        ShiftMask,      Button1,        sigstatusbar,   {.i = 6} },
	{ ClkStatusText,        ShiftMask,      Button4,        sigstatusbar,   {.i = 7} },
        { ClkStatusText,        ShiftMask,      Button5,        sigstatusbar,   {.i = 8} },

	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
