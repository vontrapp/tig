/* Copyright (c) 2006-2010 Jonas Fonseca <fonseca@diku.dk>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef TIG_IO_H
#define TIG_IO_H

/*
 * Argument array helpers.
 */

bool argv_from_string(const char *argv[SIZEOF_ARG], int *argc, char *cmd);
bool argv_from_env(const char **argv, const char *name);
void argv_free(const char *argv[]);
size_t argv_size(const char **argv);
bool argv_append(const char ***argv, const char *arg);
bool argv_append_array(const char ***dst_argv, const char *src_argv[]);
bool argv_copy(const char ***dst, const char *src[]);

/*
 * Executing external commands.
 */

enum io_type {
	IO_FD,			/* File descriptor based IO. */
	IO_BG,			/* Execute command in the background. */
	IO_FG,			/* Execute command with same std{in,out,err}. */
	IO_RD,			/* Read only fork+exec IO. */
	IO_WR,			/* Write only fork+exec IO. */
	IO_AP,			/* Append fork+exec output to file. */
};

struct io {
	int pipe;		/* Pipe end for reading or writing. */
	pid_t pid;		/* PID of spawned process. */
	int error;		/* Error status. */
	char *buf;		/* Read buffer. */
	size_t bufalloc;	/* Allocated buffer size. */
	size_t bufsize;		/* Buffer content size. */
	char *bufpos;		/* Current buffer position. */
	unsigned int eof:1;	/* Has end of file been reached. */
};

typedef int (*io_read_fn)(char *, size_t, char *, size_t, void *data);

bool io_open(struct io *io, const char *fmt, ...);
bool io_kill(struct io *io);
bool io_done(struct io *io);
bool io_run(struct io *io, enum io_type type, const char *dir, const char *argv[], ...);
bool io_run_bg(const char **argv);
bool io_run_fg(const char **argv, const char *dir);
bool io_run_append(const char **argv, int fd);
bool io_eof(struct io *io);
int io_error(struct io *io);
char * io_strerror(struct io *io);
bool io_can_read(struct io *io, bool can_block);
ssize_t io_read(struct io *io, void *buf, size_t bufsize);
char * io_get(struct io *io, int c, bool can_read);
bool io_write(struct io *io, const void *buf, size_t bufsize);
bool io_read_buf(struct io *io, char buf[], size_t bufsize);
bool io_run_buf(const char **argv, char buf[], size_t bufsize);
int io_load(struct io *io, const char *separators,
	    io_read_fn read_property, void *data);
int io_run_load(const char **argv, const char *separators,
		io_read_fn read_property, void *data);

#endif
