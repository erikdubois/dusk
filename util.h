/* See LICENSE file for copyright and license details. */

#ifndef MAX
#define MAX(A, B)               ((A) > (B) ? (A) : (B))
#endif
#ifndef MIN
#define MIN(A, B)               ((A) < (B) ? (A) : (B))
#endif
#define BETWEEN(X, A, B)        ((A) <= (X) && (X) <= (B))

#ifdef _DEBUG
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
#else
#define DEBUG(...)
#endif

static const unsigned long
	SmartGaps = 0x1, // enables no gaps if there is only one visible window
	SmartGapsMonocle = 0x2, // enforces no (outer) gaps in monocle layout
	Swallow = 0x4, // enables swallowing of clients
	SwallowFloating = 0x8, // means swallow floating windows by default
	CenteredWindowName = 0x10,
	BarActiveGroupBorderColor = 0x20, // use border color of active group, otherwise title scheme is used
	BarMasterGroupBorderColor = 0x40, // use border color of master group, otherwise title scheme is used
	ColorEmoji = 0x80,
	Status2DNoAlpha = 0x100, // option to not use alpha when drawing status2d status
	Systray = 0x200, // enables systray
	BarBorder = 0x400, // draw a border around the bar
	NoBorders = 0x800, // as per the noborder patch, show no border when only one client in tiled mode
	Warp = 0x1000, // warp patch
	FocusedOnTop = 0x2000,
	DecorationHints = 0x4000, // used by setfullscreen, prevents state change
	FocusOnNetActive = 0x8000,
	AllowNoModifierButtons = 0x10000,
	CenterSizeHintsClients = 0x20000, // center tiled clients subject to size hints within their tiled area
	ResizeHints = 0x40000, // if enabled then dusk will respect size hints in tiled resizals
	SortScreens = 0x80000, // only applies on startup
	ViewOnWs = 0x100000, // follow a window to the workspace it is being moved to
	Xresources = 0x200000, // xrdb patch
	FuncPlaceholder0x400000 = 0x400000,
	Debug = 0x800000,
	AltWorkspaceIcons = 0x1000000, // show the workspace name instead of the icons
	GreedyMonitor = 0x2000000, // when viewing a workspace the monitor is greedy and gives nothing in return (i.e. disables swap of workspaces)
	SmartLayoutConvertion = 0x4000000, // when moving a workspace from one monitor to another, automatically adjust layout based on monitor orientation (i.e. vertical vs horizontal)
	AutoHideScratchpads = 0x8000000, // automatically hide open scratchpads when moving to another workspace
	RioDrawIncludeBorders = 0x10000000, // indicates whether the area drawn using slop includes the window borders
	RioDrawSpawnAsync = 0x20000000, // indicates whether to spawn the application alongside or after drawing area using slop
	BarPadding = 0x40000000, // enables bar padding
	RestrictFocusstackToMonitor = 0x80000000, // option to restrict focusstack to only operate within the monitor
	AutoReduceNmaster = 0x100000000, // automatically reduce nmaster if there are multiple master clients and one is killed
	WinTitleIcons = 0x200000000, // adds application icons to window titles in the bar
	WorkspacePreview = 0x400000000, // adds preview images when hovering workspace icons in the bar
	SpawnCwd = 0x800000000, // spawn applications in the currently selected client's working directory
	SystrayNoAlpha = 0x1000000000, // option to not use alpha (transparency) for the systray
	FuncPlaceholder137438953472 = 0x2000000000,
	FuncPlaceholder274877906944 = 0x4000000000,
	FuncPlaceholder549755813888 = 0x8000000000,
	FuncPlaceholder1099511627776 = 0x10000000000,
	FuncPlaceholder2199023255552 = 0x20000000000,
	FuncPlaceholder4398046511104 = 0x40000000000,
	FuncPlaceholder8796093022208 = 0x80000000000,
	FuncPlaceholder17592186044416 = 0x100000000000,
	FuncPlaceholder35184372088832 = 0x200000000000,
	FuncPlaceholder70368744177664 = 0x400000000000,
	FuncPlaceholder140737488355328 = 0x800000000000,
	FuncPlaceholder281474976710656 = 0x1000000000000,
	FuncPlaceholder562949953421312 = 0x2000000000000,
	FuncPlaceholder1125899906842624 = 0x4000000000000,
	FuncPlaceholder2251799813685248 = 0x8000000000000,
	FuncPlaceholder4503599627370496 = 0x10000000000000,
	FuncPlaceholder9007199254740992 = 0x20000000000000,
	FuncPlaceholder18014398509481984 = 0x40000000000000,
	FuncPlaceholder36028797018963968 = 0x80000000000000,
	FuncPlaceholder72057594037927936 = 0x100000000000000,
	FuncPlaceholder144115188075855872 = 0x200000000000000,
	FuncPlaceholder288230376151711744 = 0x400000000000000,
	FuncPlaceholder576460752303423488 = 0x800000000000000,
	FuncPlaceholder1152921504606846976 = 0x1000000000000000,
	FuncPlaceholder2305843009213693952 = 0x2000000000000000,
	FuncPlaceholder4611686018427387904 = 0x4000000000000000,
	FuncPlaceholder9223372036854775808 = 0x8000000000000000;

void die(const char *fmt, ...);
void *ecalloc(size_t nmemb, size_t size);
int enabled(const long functionality);
int disabled(const long functionality);
void enablefunc(const long functionality);
void disablefunc(const long functionality);
void togglefunc(const long functionality);
const unsigned long getfuncbyname(const char *name);
