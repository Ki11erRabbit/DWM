/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
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
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "LigalexMono:size=9",/*"IBMPlexMono-Regular:size=10",*/ /*"JoyPixels*/"twemoji:pixelsize=9:antialias=true:autohint=true" };
static const char dmenufont[]       = "LigalexMono:size=9"/*"IBMPlexMono-Regular:size=10"*/;
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

typedef struct {
       const char *name;
       const void *cmd;
} Sp;                                                                                                            
const char *spcmd1[] = {"kitty", "-T", "spterm", NULL };
const char *spcmd2[] = {"kitty", "-T", "calcterm","-o", "font_size=14", "R", "-q", NULL };
const char *spcmd3[] = {"keepassxc", NULL };
static Sp scratchpads[] = {
       /* name          cmd  */
       {"spterm",      spcmd1},
       {"termcalc",    spcmd2},
       {"keepassxc",   spcmd3},
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
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1,      50,50,500,500,     5  },
	{ "st",      NULL,     NULL,           0,         0,          1,           0,        -1,      50,50,500,500,     5  },
	{ "kitty",   NULL,     NULL,           0,         0,          1,           0,        -1,      50,50,500,500,     5  },
	{ "nnn",     NULL,     NULL,           0,         0,          1,           0,        -1,      50,50,500,500,     5  },
	{ "handlr",  NULL,     NULL,           0,         0,          1,           0,        -1,      50,50,500,500,     5  },
	{ "Discord", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1,      50,50,500,500,     5  },
	{ "Panther", NULL,     NULL,           0,         1,          0,          -1,        -1,      1900,1060,500,500, 2  },
	{ "Black Mesa - OpenGL", NULL, NULL,   0,         0,          0,          -1,        -1,      0,0,1920,1080,     1  },
	{ NULL,      NULL,   "spterm",         SPTAG(0),  1,         -1,          -1,         0,      240,1100,1400,800,   8  },
        { NULL,      NULL,   "calcterm",       SPTAG(1),  1,         -1,          -1,         0,      710,225,500,250,   8  },
        { NULL,     "keepassxc", NULL,         SPTAG(2),  0,         -1,          -1,        -1,      50,50,500,500,     2  },
	{ NULL,      NULL,   "cmus",           0,         1,         -1,          -1,        -1,      240,110,1400,800,   8  },
	{ "copyq",      NULL,   NULL,           0,         1,         -1,          -1,        -1,      140,110,800,900,   8  },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1,      50,50,500,500,     5  }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
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
	{ MOD, XK_q,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_x,     ACTION##stack, {.i = -1 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define SHCMDZSH(cmd) { .v = (const char*[]){ "/bin/zsh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "kitty", NULL };

#include <X11/XF86keysym.h>
#include "shift-tools.c"


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ALTKEY,                XK_o, shiftviewclients,    { .i = +1 } },
	{ MODKEY,             		XK_j,	shiftview,         { .i = +1 } },
	{ MODKEY,	      		XK_k,	shiftview,         { .i = -1 } },
	{ MODKEY|ALTKEY,                XK_y, shiftviewclients,    { .i = -1 } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY,                       XK_u,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_l,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_m,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_i,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,		XK_k,      shiftboth,      { .i = -1 }	},
	{ MODKEY|ControlMask,           XK_n,      shiftswaptags,  { .i = -1 }	},
	{ MODKEY|ControlMask,   	XK_e,      shiftswaptags,  { .i = +1 }	},
	{ MODKEY|ShiftMask,             XK_j,      shiftboth,      { .i = +1 }	},
	{ MODKEY,                       XK_z,      incrgaps,       {.i = +1 } },
	{ MODKEY,                       XK_x,      incrgaps,       {.i = -1 } },
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
//	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
//	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },//Tiling
	{ MODKEY|ControlMask,           XK_f,      setlayout,      {.v = &layouts[1]} },//floating
	{ MODKEY|ControlMask,           XK_m,      setlayout,      {.v = &layouts[2]} },//monacle
	{ MODKEY,        		XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ALTKEY,                XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
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
	{ MODKEY|ControlMask,           XK_s,      spawn,          SHCMD("systemctl suspend") },//suspend
        { MODKEY,                    XK_BackSpace, spawn,          SHCMD("betterlockscreen -l") },  //lock
	{ MODKEY|ControlMask,           XK_q,      spawn,          SHCMD("pkill dwm") },         //logout
	//******** Programs
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,	      		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,        		XK_r,      spawn,          SHCMD("thunar") },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          SHCMDZSH("kitty nnn -a -c -P p") },//{.v = termfm } },
	{ MODKEY|ControlMask,           XK_Return, spawn,          SHCMDZSH("kitty nnn -a -e -P p") }, //{.v = termfmedit } },
	{ MODKEY,                       XK_w,      spawn,          SHCMD("firefox") },
	{ 0|ControlMask|ALTKEY,         XK_Delete, spawn,          SHCMD("kitty btop") }, 
        { MODKEY|ShiftMask,             XK_m,      spawn,          SHCMDZSH("kitty -T cmus screen -q -r -D cmus || screen -S cmus $(which --skip-alias cmus)") },	
	{ 0,                            XK_Print,  spawn,	   SHCMD("spectacle --fullscreen --background") },
	{ MODKEY,                       XK_s,      spawn,          SHCMD("spectacle --region --background") },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("spectacle --region --background --copy-image") },
	{ MODKEY|ALTKEY,                XK_s,      spawn,          SHCMD("flameshot gui") },
	{ MODKEY,                       XK_v,      spawn,          SHCMD("copyq menu") },
	{ MODKEY,                       XK_h,      spawn,          SHCMD("panther_launcher") },
	{ MODKEY|ShiftMask,             XK_c,      spawn,          SHCMD("kill -s USR1 $(pidof deadd-notification-center)") },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          SHCMD("kitty keepmenu") },//{.v = keepmenu } },
        { MODKEY|ControlMask,           XK_v,      spawn,          SHCMD("copyq toggle") },//copyq	


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
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	//{ MODKEY|ShiftMask,             XK_BackSpace, quit,        {0} },
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
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
