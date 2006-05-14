 * tig [options]
 * tig [options] [--] [git log options]
 * tig [options] show [git show options]
 * tig [options] <    [git command output]
#ifndef DEBUG
#define NDEBUG
#endif

#include <unistd.h>
static void set_nonblocking_input(bool loading);
/* Some ascii-shorthands fitted into the ncurses namespace. */
	REQ_VIEW_PAGER,
	REQ_QUIT,
	REQ_PROMPT,
	REQ_SCREEN_RESIZE,
	REQ_SHOW_VERSION,
	REQ_STOP_LOADING,
	REQ_VIEW_NEXT,
struct ref {
	char *name;
	char id[41];
	unsigned int tag:1;
	unsigned int next:1;
};

	struct ref **refs;	/* Repository references; tags & branch heads. */
/*
 * String helpers
 */

/* Shell quoting
 *
 * NOTE: The following is a slightly modified copy of the git project's shell
 * quoting routines found in the quote.c file.
 *
 * Help to copy the thing properly quoted for the shell safety.  any single
 * quote is replaced with '\'', any exclamation point is replaced with '\!',
 * and the whole thing is enclosed in a
 *
 * E.g.
 *  original     sq_quote     result
 *  name     ==> name      ==> 'name'
 *  a b      ==> a b       ==> 'a b'
 *  a'b      ==> a'\''b    ==> 'a'\''b'
 *  a!b      ==> a'\!'b    ==> 'a'\!'b'
 */

static size_t
sq_quote(char buf[SIZEOF_CMD], size_t bufsize, const char *src)
{
	char c;

#define BUFPUT(x) ( (bufsize < SIZEOF_CMD) && (buf[bufsize++] = (x)) )

	BUFPUT('\'');
	while ((c = *src++)) {
		if (c == '\'' || c == '!') {
			BUFPUT('\'');
			BUFPUT('\\');
			BUFPUT(c);
			BUFPUT('\'');
		} else {
			BUFPUT(c);
		}
	}
	BUFPUT('\'');

	return bufsize;
}

static char opt_cmd[SIZEOF_CMD]	= "";
static FILE *opt_pipe		= NULL;
static bool
		 *	Start up in log view using the internal log command.
		 *	Start up in diff view using the internal diff command.
		    !strncmp(opt, "--line-number", 13)) {
		    !strcmp(opt, "--version")) {
			return FALSE;
		 * \--::
		 *	End of tig(1) options. Useful when specifying commands
		 *	for the main view. Example:
		 *
		 *		$ tig -- --since=1.month
		if (!strcmp(opt, "--")) {
			i++;
			break;
		}

		/**
		 * log [options]::
		 *	Open log view using the given git log options.
		 *
		 * diff [options]::
		 *	Open diff view using the given git diff options.
		 *
		 * show [options]::
		 *	Open diff view using the given git show options.
		 **/
		if (!strcmp(opt, "log") ||
		    !strcmp(opt, "diff") ||
		    !strcmp(opt, "show")) {
			opt_request = opt[0] == 'l'
				    ? REQ_VIEW_LOG : REQ_VIEW_DIFF;
			break;
		/* Make stuff like:
		 *
		 *	$ tig tag-1.0..HEAD
		 *
		 * work. */
		if (opt[0] && opt[0] != '-')
			break;

	if (!isatty(STDIN_FILENO)) {
		/**
		 * Pager mode
		 * ~~~~~~~~~~
		 * If stdin is a pipe, any log or diff options will be ignored and the
		 * pager view will be opened loading data from stdin. The pager mode
		 * can be used for colorizing output from various git commands.
		 *
		 * Example on how to colorize the output of git-show(1):
		 *
		 *	$ git show | tig
		 **/
		opt_request = REQ_VIEW_PAGER;
		opt_pipe = stdin;

	} else if (i < argc) {
		size_t buf_size;

		/**
		 * Git command options
		 * ~~~~~~~~~~~~~~~~~~~
		 * All git command options specified on the command line will
		 * be passed to the given command and all will be shell quoted
		 * before used.
		 *
		 * NOTE: It is possible to specify options even for the main
		 * view. If doing this you should not touch the `--pretty`
		 * option.
		 *
		 * Example on how to open the log view and show both author and
		 * committer information:
		 *
		 *	$ tig log --pretty=fuller
		 **/

		if (opt_request == REQ_VIEW_MAIN)
			/* XXX: This is vulnerable to the user overriding
			 * options required for the main view parser. */
			string_copy(opt_cmd, "git log --stat --pretty=raw");
		else
			string_copy(opt_cmd, "git");
		buf_size = strlen(opt_cmd);

		while (buf_size < sizeof(opt_cmd) && i < argc) {
			opt_cmd[buf_size++] = ' ';
			buf_size = sq_quote(opt_cmd, buf_size, argv[i++]);
		}

		if (buf_size >= sizeof(opt_cmd))
			die("command too long");

		opt_cmd[buf_size] = 0;

	}

	return TRUE;
	 * p::
	 *	Switch to pager view.
	 * Tab::
	 *	Switch to next view.
	{ 'p',		REQ_VIEW_PAGER },
	{ KEY_TAB,	REQ_VIEW_NEXT },
	 * ':'::
	 *	Open prompt. This allows you to specify what git command to run.
	 *	Example:
	 *
	 *	:log -p
	 *
	{ ':',		REQ_PROMPT },

	/* Use the ncurses SIGWINCH handler. */
	{ KEY_RESIZE,	REQ_SCREEN_RESIZE },
LINE(DIFF_INDEX,   "index ",		COLOR_BLUE,	COLOR_DEFAULT,	0), \
LINE(DIFF_OLDMODE, "old file mode ",	COLOR_YELLOW,	COLOR_DEFAULT,	0), \
LINE(DIFF_NEWMODE, "new file mode ",	COLOR_YELLOW,	COLOR_DEFAULT,	0), \
LINE(PP_AUTHOR,	   "Author: ",		COLOR_CYAN,	COLOR_DEFAULT,	0), \
LINE(PP_COMMIT,	   "Commit: ",		COLOR_MAGENTA,	COLOR_DEFAULT,	0), \
LINE(PP_MERGE,	   "Merge: ",		COLOR_BLUE,	COLOR_DEFAULT,	0), \
LINE(PP_DATE,	   "Date:   ",		COLOR_YELLOW,	COLOR_DEFAULT,	0), \
LINE(PP_ADATE,	   "AuthorDate: ",	COLOR_YELLOW,	COLOR_DEFAULT,	0), \
LINE(PP_CDATE,	   "CommitDate: ",	COLOR_YELLOW,	COLOR_DEFAULT,	0), \
LINE(AUTHOR,	   "author ",		COLOR_CYAN,	COLOR_DEFAULT,	0), \
LINE(MAIN_DELIM,   "",			COLOR_MAGENTA,	COLOR_DEFAULT,	0), \
LINE(MAIN_TAG,     "",			COLOR_MAGENTA,	COLOR_DEFAULT,	A_BOLD), \
LINE(MAIN_REF,     "",			COLOR_CYAN,	COLOR_DEFAULT,	A_BOLD),
/**
 * ENVIRONMENT VARIABLES
 * ---------------------
 * Several options related to the interface with git can be configured
 * via environment options.
 *
 * Repository references
 * ~~~~~~~~~~~~~~~~~~~~~
 * Commits that are referenced by tags and branch heads will be marked
 * by the reference name surrounded by '[' and ']':
 *
 *	2006-04-18 23:12 Jonas Fonseca       | [tig-0.2] tig version 0.2
 *
 * If you want to filter out certain directories under `.git/refs/`, say
 * `tmp` you can do it by setting the following variable:
 *
 *	$ TIG_LS_REMOTE="git ls-remote | sed '/\/tmp\//d'"
 *
 * Or set the variable permanently in your environment.
 *
 * TIG_LS_REMOTE::
 *	Set command for retrieving all repository references.private
 **/

#define TIG_LS_REMOTE \
	"git ls-remote ."

/**
 * View commands
 * ~~~~~~~~~~~~~
 * It is possible to alter which commands are used for the different views.
 * If for example you prefer commits in the main to be sorted by date and
 * only show 500 commits, use:
 *
 *	$ TIG_MAIN_CMD="git log --date-order -n500 --pretty=raw %s" tig
 *
 * Or set the variable permanently in your environment.
 *
 * Notice, how `%s` is used to specify the commit reference. There can
 * be a maximum of 5 `%s` ref specifications.
 *
 * TIG_DIFF_CMD::
 *	The command used for the diff view. By default, git show is used
 *	as a backend.
 *
 * TIG_LOG_CMD::
 *	The command used for the log view.
 *
 * TIG_MAIN_CMD::
 *	The command used for the main view. Note, you must always specify
 *	the option: `--pretty=raw` since the main view parser expects to
 *	read that format.
 **/

#define TIG_DIFF_CMD \
	"git show --patch-with-stat --find-copies-harder -B -C %s"

#define TIG_LOG_CMD	\
	"git log --cc --stat -n100 %s"

#define TIG_MAIN_CMD \
	"git log --topo-order --stat --pretty=raw %s"

/* We silently ignore that the following are also exported. */

#define TIG_HELP_CMD \
	"man tig 2> /dev/null"

#define TIG_PAGER_CMD \
	""


	const char *name;	/* View name */
	char *cmd_fmt;		/* Default command line format */
	char *cmd_env;		/* Command line set via environment */
	char *id;		/* Points to either of ref_{head,commit} */
	size_t objsize;		/* Size of objects in the line index */
		/* Draw one line; @lineno must be < view->height. */
		/* Read one line; updates view->line. */
		/* Depending on view, change display based on current line. */
	char cmd[SIZEOF_CMD];	/* Command buffer */
	char ref[SIZEOF_REF];	/* Hovered commit reference */
	char vid[SIZEOF_REF];	/* View ID. Set to id member when updating. */
	int height, width;	/* The width and height of the main window */
	WINDOW *win;		/* The main window */
	WINDOW *title;		/* The title window living below the main window */
	void **line;		/* Line index; each line contains user data */
	unsigned int digits;	/* Number of digits in the lines member. */
char ref_head[SIZEOF_REF]	= "HEAD";
char ref_commit[SIZEOF_REF]	= "HEAD";
#define VIEW_STR(name, cmd, env, ref, objsize, ops) \
	{ name, cmd, #env, ref, objsize, ops }
#define VIEW_(id, name, ops, ref, objsize) \
	VIEW_STR(name, TIG_##id##_CMD,  TIG_##id##_CMD, ref, objsize, ops)
	VIEW_(MAIN,  "main",  &main_ops,  ref_head,   sizeof(struct commit)),
	VIEW_(DIFF,  "diff",  &pager_ops, ref_commit, sizeof(char)),
	VIEW_(LOG,   "log",   &pager_ops, ref_head,   sizeof(char)),
	VIEW_(HELP,  "help",  &pager_ops, ref_head,   sizeof(char)),
	VIEW_(PAGER, "pager", &pager_ops, "static",   sizeof(char)),
	int offset, i;
	getmaxyx(stdscr, base->height, base->width);
	base->height -= 1;
		/* Horizontal split. */
		view->width   = base->width;

	if (*view->ref)
		wprintw(view->title, "[%s] ref: %s", view->name, view->ref);
	else
		wprintw(view->title, "[%s]", view->name);

			report("Cannot scroll beyond the last line");
			report("Cannot scroll beyond the first line");

		report("Cannot move beyond the first line");
	} else if (steps >= 0 && view->lineno + 1 >= view->lines) {
		report("Cannot move beyond the last line");
		view->ops->draw(view, prev_lineno);
static bool
	if (opt_cmd[0]) {
		string_copy(view->cmd, opt_cmd);
		opt_cmd[0] = 0;
		/* When running random commands, the view ref could have become
		 * invalid so clear it. */
		view->ref[0] = 0;
	} else {
		char *format = view->cmd_env ? view->cmd_env : view->cmd_fmt;

		if (snprintf(view->cmd, sizeof(view->cmd), format,
			     id, id, id, id, id) >= sizeof(view->cmd))
			return FALSE;
	}

	/* Special case for the pager view. */
	if (opt_pipe) {
		view->pipe = opt_pipe;
		opt_pipe = NULL;
	} else {
		view->pipe = popen(view->cmd, "r");
	}
	string_copy(view->vid, id);
	if (!view->pipe)
		return;
	if (view->pipe == stdin)
		fclose(view->pipe);
	else
		pclose(view->pipe);
static bool
	unsigned long lines = view->height;
		int linelen = strlen(line);
	{
		int digits;

		lines = view->lines;
		for (digits = 0; lines; digits++)
			lines /= 10;

		/* Keep the displayed view in sync with line number scaling. */
		if (digits != view->digits) {
			view->digits = digits;
			redraw_from = 0;
		}
	}
	/* Update the title _after_ the redraw so that if the redraw picks up a
	 * commit reference in view->ref it'll be available here. */
	update_view_title(view);

		report("Failed to read: %s", strerror(errno));
enum open_flags {
	OPEN_DEFAULT = 0,	/* Use default view switching. */
	OPEN_SPLIT = 1,		/* Split current view. */
	OPEN_BACKGROUNDED = 2,	/* Backgrounded. */
	OPEN_RELOAD = 4,	/* Reload view even if it is the current. */
};

open_view(struct view *prev, enum request request, enum open_flags flags)
	bool backgrounded = !!(flags & OPEN_BACKGROUNDED);
	bool split = !!(flags & OPEN_SPLIT);
	bool reload = !!(flags & OPEN_RELOAD);
	/* Cycle between displayed views and count the views. */
		if (prev != view &&
		    view == displayed &&
		    !strcmp(view->vid, prev->vid)) {
	if (view == prev && nviews == 1 && !reload) {
	if ((reload || strcmp(view->vid, view->id)) &&
	    !begin_update(view)) {
	if (split && prev->lineno - prev->offset >= prev->height) {
		/* Take the title line into account. */
		int lines = prev->lineno - prev->offset - prev->height + 1;

		/* Scroll the view that was split if the current line is
		 * outside the new limited view. */
		do_scroll_view(prev, lines);
	}

		if (!split)
	if (view->pipe) {
		/* Clear the old view and let the incremental updating refill
		 * the screen. */
		wclear(view->win);
		report("Loading...");
	} else {
		redraw_view(view);
		report("");
	}
	case REQ_VIEW_PAGER:
		open_view(view, request, OPEN_DEFAULT);
		if (!view->lines) {
			report("Nothing to enter");
			break;
		}
	case REQ_VIEW_NEXT:
	{
		int nviews = display[1] ? 2 : 1;
		int next_view = (current_view + 1) % nviews;

		if (next_view == current_view) {
			report("Only one view is displayed");
			break;
		}

		current_view = next_view;
		/* Blur out the title of the previous view. */
		update_view_title(view);
		report("Switching to %s view", display[current_view]->name);
		break;
	}
	case REQ_PROMPT:
		/* Always reload^Wrerun commands from the prompt. */
		open_view(view, opt_request, OPEN_RELOAD);
		break;

		foreach_view (view, i) {
				report("Stopped loaded of %s view", view->name),
			end_update(view);
		}
	case REQ_SCREEN_RESIZE:
		resize_display();
		/* Fall-through */
		foreach_view (view, i) {
			redraw_view(view);
			update_view_title(view);
		}
		if (type == LINE_COMMIT) {
			string_copy(view->ref, line + 7);
			string_copy(ref_commit, view->ref);
		}

		static char indent[] = "                    ";
		unsigned long real_lineno = view->offset + lineno + 1;
			mvwprintw(view->win, lineno, 0, "%.*d", view->digits, real_lineno);

		else if (view->digits < sizeof(indent))
			mvwaddnstr(view->win, lineno, 0, indent, view->digits);

		waddstr(view->win, ": ");
		open_view(view, REQ_VIEW_DIFF, OPEN_DEFAULT);

static struct ref **get_refs(char *id);

		string_copy(view->ref, commit->id);
		string_copy(ref_commit, view->ref);
	wmove(view->win, lineno, cols + 2);

	if (commit->refs) {
		size_t i = 0;

		do {
			if (commit->refs[i]->tag)
				wattrset(view->win, get_line_attr(LINE_MAIN_TAG));
			else
				wattrset(view->win, get_line_attr(LINE_MAIN_REF));
			waddstr(view->win, "[");
			waddstr(view->win, commit->refs[i]->name);
			waddstr(view->win, "]");
			wattrset(view->win, A_NORMAL);
			waddstr(view->win, " ");
		} while (commit->refs[i++]->next);
	}

	waddstr(view->win, commit->title);
		commit->refs = get_refs(commit->id);
	case LINE_AUTHOR:
		/* FIXME: More gracefull handling of titles; append "..." to
		 * shortened titles, etc. */
		    isspace(line[4]))
	open_view(view, REQ_VIEW_DIFF, OPEN_SPLIT | OPEN_BACKGROUNDED);

/* Whether or not the curses interface has been initialized. */
bool cursed = FALSE;

	va_start(args, msg);

	if (*msg)
		vwprintw(status_win, msg, args);
set_nonblocking_input(bool loading)
	if ((loading == FALSE && nloading-- == 1) ||
	    (loading == TRUE  && nloading++ == 0))
		nodelay(status_win, loading);
	/* Initialize the curses library */
	if (isatty(STDIN_FILENO)) {
		cursed = !!initscr();
	} else {
		/* Leave stdin and stdout alone when acting as a pager. */
		FILE *io = fopen("/dev/tty", "r+");

		cursed = !!newterm(NULL, io, io);
	}

	if (!cursed)
		die("Failed to initialize curses");


/*
 * Repository references
 */

static struct ref *refs;
size_t refs_size;

static struct ref **
get_refs(char *id)
{
	struct ref **id_refs = NULL;
	size_t id_refs_size = 0;
	size_t i;

	for (i = 0; i < refs_size; i++) {
		struct ref **tmp;

		if (strcmp(id, refs[i].id))
			continue;

		tmp = realloc(id_refs, (id_refs_size + 1) * sizeof(*id_refs));
		if (!tmp) {
			if (id_refs)
				free(id_refs);
			return NULL;
		}

		id_refs = tmp;
		if (id_refs_size > 0)
			id_refs[id_refs_size - 1]->next = 1;
		id_refs[id_refs_size] = &refs[i];

		/* XXX: The properties of the commit chains ensures that we can
		 * safely modify the shared ref. The repo references will
		 * always be similar for the same id. */
		id_refs[id_refs_size]->next = 0;
		id_refs_size++;
	}

	return id_refs;
}

static int
load_refs(void)
{
	char *cmd_env = getenv("TIG_LS_REMOTE");
	char *cmd = cmd_env ? cmd_env : TIG_LS_REMOTE;
	FILE *pipe = popen(cmd, "r");
	char buffer[BUFSIZ];
	char *line;

	if (!pipe)
		return ERR;

	while ((line = fgets(buffer, sizeof(buffer), pipe))) {
		char *name = strchr(line, '\t');
		struct ref *ref;
		int namelen;
		bool tag = FALSE;

		if (!name)
			continue;

		*name++ = 0;
		namelen = strlen(name) - 1;
		if (name[namelen - 1] == '}') {
			while (namelen > 0 && name[namelen] != '^')
				namelen--;
		}
		name[namelen] = 0;

		if (!strncmp(name, "refs/tags/", STRING_SIZE("refs/tags/"))) {
			name += STRING_SIZE("refs/tags/");
			tag = TRUE;

		} else if (!strncmp(name, "refs/heads/", STRING_SIZE("refs/heads/"))) {
			name += STRING_SIZE("refs/heads/");

		} else if (!strcmp(name, "HEAD")) {
			continue;
		}

		refs = realloc(refs, sizeof(*refs) * (refs_size + 1));
		if (!refs)
			return ERR;

		ref = &refs[refs_size++];
		ref->tag = tag;
		ref->name = strdup(name);
		if (!ref->name)
			return ERR;

		string_copy(ref->id, line);
	}

	if (ferror(pipe))
		return ERR;

	pclose(pipe);

	return OK;
}

	/* XXX: Restore tty modes and let the OS cleanup the rest! */
	if (cursed)
		endwin();
	struct view *view;
	size_t i;
	if (!parse_options(argc, argv))
	if (load_refs() == ERR)
		die("Failed to load refs.");

	for (i = 0; i < ARRAY_SIZE(views) && (view = &views[i]); i++)
		view->cmd_env = getenv(view->cmd_env);

		/* Some low-level request handling. This keeps handling of
		 * status_win restricted. */
		switch (request) {
		case REQ_PROMPT:
			report(":");
			/* Temporarily switch to line-oriented and echoed
			 * input. */
			nocbreak();
			echo();

			if (wgetnstr(status_win, opt_cmd + 4, sizeof(opt_cmd) - 4) == OK) {
				memcpy(opt_cmd, "git ", 4);
				opt_request = REQ_VIEW_PAGER;
			} else {
				request = ERR;
			}

			noecho();
			cbreak();
			break;

		case REQ_SCREEN_RESIZE:
		{
			int height, width;

			getmaxyx(stdscr, height, width);

			/* Resize the status view and let the view driver take
			 * care of resizing the displayed views. */
			wresize(status_win, 1, width);
			mvwin(status_win, height - 1, 0);
			wrefresh(status_win);
			break;
		}
		default:
			break;
		}
 * - Searching.