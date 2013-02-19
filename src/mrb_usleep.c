/*
** mrb_sleep - usleep class for mruby
**
** Copyright (c) EmAF project 2013-
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the
** "Software"), to deal in the Software without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
** [ MIT license: http://www.opensource.org/licenses/mit-license.php ]
*/

#include <unistd.h>
#include <sys/time.h>

#include "mruby.h"

mrb_value
mrb_f_usleep_usleep(mrb_state *mrb, mrb_value self)
{
	mrb_int argc;
	mrb_value *argv;
	struct timeval st_tm,ed_tm;
	time_t slp_tm;

	gettimeofday( &st_tm, NULL );

	mrb_get_args(mrb, "*", &argv, &argc);

	if(argc == 0) {
		/* not implemented forever sleep */
		mrb_raise(mrb, E_ARGUMENT_ERROR, "wrong number of arguments");
	} else if(argc == 1) {
		usleep(mrb_fixnum(argv[0]));
	} else {
		mrb_raise(mrb, E_ARGUMENT_ERROR, "wrong number of arguments");
	}

	gettimeofday( &ed_tm, NULL );

	if ( st_tm.tv_usec > ed_tm.tv_usec ) {
		slp_tm = 1000000 + ed_tm.tv_usec - st_tm.tv_usec;
	} else {
		slp_tm = ed_tm.tv_usec - st_tm.tv_usec;
	}

	return mrb_fixnum_value(slp_tm);
}

void
mrb_mruby_usleep_gem_init(mrb_state *mrb) {
	struct RClass *usleep;

	usleep = mrb_define_module(mrb, "USleep");
	mrb_define_class_method(mrb, usleep, "usleep", mrb_f_usleep_usleep, ARGS_REQ(1));
}

void mrb_mruby_usleep_gem_final(mrb_state *mrb) {
}
