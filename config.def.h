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
static const char *fonts[]          = { "LigalexMono:size=5",/*"IBMPlexMono-Regular:size=10",*/ /*"JoyPixels*/"NotoColorEmoji:pixelsize=5:antialias=true:autohint=true" };
static const char dmenufont[]       = "LigalexMono:size=5"/*"IBMPlexMono-Regular:size=10"*/;
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
static const char *filemanager[] = { "thunar", NULL };
static const char *screenshot[] = { "spectacle", "--fullscreen", "--background", NULL };
static const char *screenshotclip[] = { "spectacle", "--fullscreen", "--background", "--copy-image", NULL };
static const char *screenshotregion[] = { "spectacle", "--region", "--background", NULL };
static const char *screenshotregionclip[] = { "spectacle", "--region", "--background", "--copy-image", NULL };
static const char *screenshotregionannotate[] = { "flameshot", "gui", NULL };
static const char *clipboard[] = { "copyq", "menu", NULL };
static const char *applauncher[] = { "panther_launcher", NULL };
static const char *keepmenu[] = { "keepmenu", NULL };

static const char *suspend[] = { "systemctl", "suspend", NULL };
static const char *lock[] = { "betterlockscreen", "-l", NULL };
static const char *logout[] = { "pkill", "dwm", NULL };

#include <X11/XF86keysym.h>
#include "shift-tools.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_o, shiftviewclients,    { .i = +1 } },
	{ MODKEY,             		XK_j,	shiftview,         { .i = +1 } },
	{ MODKEY,	      		XK_k,	shiftview,         { .i = -1 } },
	{ MODKEY,	                XK_y, shiftviewclients,    { .i = -1 } },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,	      		XK_Return, spawn,          {.v = termcmd } },
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
	{ MODKEY|ALTKEY,                XK_m,      incrgaps,       {.i = +1 } },
	{ MODKEY|ALTKEY,                XK_i,      incrgaps,       {.i = -1 } },
	{ MODKEY|ALTKEY|ShiftMask,      XK_m,      incrogaps,      {.i = +1 } },
	{ MODKEY|ALTKEY|ShiftMask,      XK_i,      incrogaps,      {.i = -1 } },
	{ MODKEY|ALTKEY|ControlMask,    XK_m,      incrigaps,      {.i = +1 } },
	{ MODKEY|ALTKEY|ControlMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY,                       XK_g,      togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_g,      defaultgaps,    {0} },
	{ MODKEY|ALTKEY,                XK_Right,  incrihgaps,     {.i = +1 } },
	{ MODKEY|ALTKEY,                XK_Left,   incrihgaps,     {.i = -1 } },
	{ MODKEY|ALTKEY,                XK_Up,     incrivgaps,     {.i = +1 } },
	{ MODKEY|ALTKEY,                XK_Down,   incrivgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_Right,  incrohgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_Left,   incrohgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_Right,  incrovgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_Left,   incrovgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ControlMask,           XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ALTKEY,		XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ALTKEY,                XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	

	{ MODKEY|ControlMask,           XK_s,      spawn,          {.v = suspend} },
        { MODKEY|ControlMask|ALTKEY,    XK_l,      spawn,          {.v = lock} },
	{ MODKEY|ControlMask,           XK_q,      spawn,          {.v = logout} },
	{ 0,                            XK_Print,  spawn,	   {.v = screenshot} },
	{ 0|ShiftMask,                  XK_Print,  spawn,	   {.v = screenshotclip} },
	{ MODKEY,                       XK_s,      spawn,          {.v = screenshotregion} },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = screenshotregionclip} },
	{ MODKEY|ALTKEY,                XK_s,      spawn,          {.v = screenshotregionannotate} },
	{ MODKEY|ShiftMask,  		XK_Return, spawn,          {.v = filemanager } },
	{ MODKEY|ShiftMask|ControlMask, XK_Return, spawn,          SHCMDZSH("kitty nnn -a -c -P p") },//{.v = termfm } },
	{ MODKEY|ControlMask,           XK_Return, spawn,          SHCMDZSH("kitty nnn -a -e -P p") }, //{.v = termfmedit } },
	{ MODKEY,                       XK_v,      spawn,          {.v = clipboard } },
	{ MODKEY,                       XK_h,      spawn,          {.v = applauncher } },
	{ MODKEY,                       XK_c,      spawn,          SHCMD("kill -s USR1 $(pidof deadd-notification-center)") },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          SHCMD("keepmenu") },//{.v = keepmenu } },

        { 0, XF86XK_AudioMute,		spawn,		SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer -i 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer -d 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPrev,		spawn,		SHCMD("playerctl previous") },
	{ 0, XF86XK_AudioNext,		spawn,		SHCMD("playerctl next") },
	{ 0, XF86XK_AudioPause,		spawn,		SHCMD("playerctl play-pause") },
	{ 0, XF86XK_AudioPlay,		spawn,		SHCMD("playerctl play-pause") },
	{ 0, XF86XK_AudioStop,		spawn,		SHCMD("playerctl stop") },
	{ 0, XF86XK_AudioRewind,	spawn,		SHCMD("playerctl position -10") },
	{ 0, XF86XK_AudioForward,	spawn,		SHCMD("playerctl position +10") },
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

	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
