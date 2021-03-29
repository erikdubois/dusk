static char termcol0[]  = "#000000"; /* black   */
static char termcol1[]  = "#ff0000"; /* red     */
static char termcol2[]  = "#33ff00"; /* green   */
static char termcol3[]  = "#ff0099"; /* yellow  */
static char termcol4[]  = "#0066ff"; /* blue    */
static char termcol5[]  = "#cc00ff"; /* magenta */
static char termcol6[]  = "#00ffff"; /* cyan    */
static char termcol7[]  = "#d0d0d0"; /* white   */
static char termcol8[]  = "#808080"; /* black   */
static char termcol9[]  = "#ff0000"; /* red     */
static char termcol10[] = "#33ff00"; /* green   */
static char termcol11[] = "#ff0099"; /* yellow  */
static char termcol12[] = "#0066ff"; /* blue    */
static char termcol13[] = "#cc00ff"; /* magenta */
static char termcol14[] = "#00ffff"; /* cyan    */
static char termcol15[] = "#ffffff"; /* white   */
static char *termcolor[] = {
	termcol0, termcol1, termcol2, termcol3, termcol4, termcol5, termcol6, termcol7,
	termcol8, termcol9, termcol10, termcol11, termcol12, termcol13, termcol14, termcol15,
};

int
width_status2d(Bar *bar, BarArg *a)
{
	return status2dtextlength(rawstext);
}

int
width_status2d_es(Bar *bar, BarArg *a)
{
	return status2dtextlength(rawestext);
}

int
draw_status2d(Bar *bar, BarArg *a)
{
	return drawstatusbar(a, rawstext);
}

int
draw_status2d_es(Bar *bar, BarArg *a)
{
	return drawstatusbar(a, rawestext);
}

int
drawstatusbar(BarArg *a, char* stext)
{
	int i, w, len;
	int x = a->x;
	int y = a->y;
	short isCode = 0;
	char *text;
	char *p;
	Clr oldbg, oldfg;
	len = strlen(stext) + 1;
	if (!(text = (char*) malloc(sizeof(char)*len)))
		die("malloc");
	p = text;

	copyvalidchars(text, stext);

	drw_setscheme(drw, scheme[SchemeNorm]);
	drw_rect(drw, a->x, a->y, a->w, a->h, 1, 1);
	drw_setscheme(drw, scheme[LENGTH(colors)]);
	drw->scheme[ColFg] = scheme[SchemeNorm][ColFg];
	drw->scheme[ColBg] = scheme[SchemeNorm][ColBg];

	/* process status text */
	i = -1;
	while (text[++i]) {
		if (text[i] == '^' && !isCode) {
			isCode = 1;

			text[i] = '\0';
			w = TEXTWM(text);
			drw_text(drw, x, y, w, bh, 0, text, 0, True);

			x += w;

			/* process code */
			while (text[++i] != '^') {
				if (text[i] == 'c') {
					char buf[8];
					if (i + 7 > len) {
						i += 7;
						break;
					}
					memcpy(buf, (char*)text+i+1, 7);
					buf[7] = '\0';
					drw_clr_create(drw, &drw->scheme[ColFg], buf, enabled(Status2DNoAlpha) ? 0xff : alphas[SchemeNorm][ColFg]);
					i += 7;
				} else if (text[i] == 'b') {
					char buf[8];
					if (i + 7 > len) {
						i += 7;
						break;
					}
					memcpy(buf, (char*)text+i+1, 7);
					buf[7] = '\0';
					drw_clr_create(drw, &drw->scheme[ColBg], buf, enabled(Status2DNoAlpha) ? 0xff : alphas[SchemeNorm][ColFg]);
					i += 7;
				} else if (text[i] == 'C') {
					int c = atoi(text + ++i) % 16;
					drw_clr_create(drw, &drw->scheme[ColFg], termcolor[c], enabled(Status2DNoAlpha) ? 0xff : alphas[SchemeNorm][ColFg]);
				} else if (text[i] == 'B') {
					int c = atoi(text + ++i) % 16;
					drw_clr_create(drw, &drw->scheme[ColBg], termcolor[c], enabled(Status2DNoAlpha) ? 0xff : alphas[SchemeNorm][ColFg]);
				} else if (text[i] == 'd') {
					drw->scheme[ColFg] = scheme[SchemeNorm][ColFg];
					drw->scheme[ColBg] = scheme[SchemeNorm][ColBg];
				} else if (text[i] == 'w') {
					Clr swp;
					swp = drw->scheme[ColFg];
					drw->scheme[ColFg] = drw->scheme[ColBg];
					drw->scheme[ColBg] = swp;
				} else if (text[i] == 'v') {
					oldfg = drw->scheme[ColFg];
					oldbg = drw->scheme[ColBg];
				} else if (text[i] == 't') {
					drw->scheme[ColFg] = oldfg;
					drw->scheme[ColBg] = oldbg;
				} else if (text[i] == 'r') {
					int rx = atoi(text + ++i);
					while (text[++i] != ',');
					int ry = atoi(text + ++i);
					while (text[++i] != ',');
					int rw = atoi(text + ++i);
					while (text[++i] != ',');
					int rh = atoi(text + ++i);

					if (ry < 0)
						ry = 0;
					if (rx < 0)
						rx = 0;

					drw_rect(drw, rx + x, y + ry, rw, rh, 1, 0);
				} else if (text[i] == 'f') {
					x += atoi(text + ++i);
				}
			}

			text = text + i + 1;
			i=-1;
			isCode = 0;
		}
	}
	if (!isCode) {
		w = TEXTWM(text);
		drw_text(drw, x, y, w, bh, 0, text, 0, True);
		x += w;
	}
	free(p);

	drw_setscheme(drw, scheme[SchemeNorm]);
	return len - 1;
}

int
status2dtextlength(char* stext)
{
	int i, w, len;
	short isCode = 0;
	char *text;
	char *p;

	len = strlen(stext) + 1;
	if (!(text = (char*) malloc(sizeof(char)*len)))
		die("malloc");
	p = text;

	copyvalidchars(text, stext);

	/* compute width of the status text */
	w = 0;
	i = -1;
	while (text[++i]) {
		if (text[i] == '^') {
			if (!isCode) {
				isCode = 1;
				text[i] = '\0';
				w += TEXTWM(text);
				text[i] = '^';
				if (text[++i] == 'f')
					w += atoi(text + ++i);
			} else {
				isCode = 0;
				text = text + i + 1;
				i = -1;
			}
		}
	}
	if (!isCode)
		w += TEXTWM(text);
	free(p);
	return w;
}