/*
 * %CopyrightBegin%
 *
 * Copyright Dustin Sallings, Michal Ptaszek, Scott Lystig Fritchie 2011.
 * All Rights Reserved.
 *
 * The contents of this file are subject to the Erlang Public License,
 * Version 1.1, (the "License"); you may not use this file except in
 * compliance with the License. You should have received a copy of the
 * Erlang Public License along with this software. If not, it can be
 * retrieved online at http://www.erlang.org/.
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License for the specific language governing rights and limitations
 * under the License.
 *
 * %CopyrightEnd%
 */

#ifndef __DTRACE_WRAPPER_H
#define __DTRACE_WRAPPER_H

#define DTRACE_TERM_BUF_SIZE 256

#ifndef	DTRACE_DRIVER_SKIP_FUNC_DECLARATIONS
inline void dtrace_proc_str(Process *process, char *process_buf);
inline void dtrace_pid_str(Eterm pid, char *process_buf);
inline void dtrace_port_str(Port *port, char *port_buf);
inline void dtrace_fun_decode(Process *process,
			      Eterm module, Eterm function, int arity,
			      char *process_buf, char *mfa_buf);
#endif

#ifdef  HAVE_DTRACE

#include "erlang_dtrace.h"

#define DTRACE_ENABLED(name)                         \
    erlang_##name##_enabled()
#define DTRACE0(name)                                \
    erlang_##name()
#define DTRACE1(name, a0)                            \
    erlang_##name(a0)
#define DTRACE2(name, a0, a1)                        \
    erlang_##name((a0), (a1))
#define DTRACE3(name, a0, a1, a2)                    \
    erlang_##name((a0), (a1), (a2))
#define DTRACE4(name, a0, a1, a2, a3)                \
    erlang_##name((a0), (a1), (a2), (a3))
#define DTRACE5(name, a0, a1, a2, a3, a4)            \
    erlang_##name((a0), (a1), (a2), (a3), (a4))
#define DTRACE6(name, a0, a1, a2, a3, a4, a5)        \
    erlang_##name((a0), (a1), (a2), (a3), (a4), (a5))
#define DTRACE7(name, a0, a1, a2, a3, a4, a5, a6)    \
    erlang_##name((a0), (a1), (a2), (a3), (a4), (a5), (a6))
#define DTRACE10(name, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9) \
    erlang_##name((a0), (a1), (a2), (a3), (a4), (a5), (a6), (a7), (a8), (a9))
#define DTRACE11(name, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) \
    erlang_##name((a0), (a1), (a2), (a3), (a4), (a5), (a6), (a7), (a8), (a9), (a10))

#else   /* HAVE_DTRACE */

/* Render all macros to do nothing */
#define DTRACE_ENABLED(name)                         0
#define DTRACE0(name)                                do {} while (0)
#define DTRACE1(name, a0)                            do {} while (0)
#define DTRACE2(name, a0, a1)                        do {} while (0)
#define DTRACE3(name, a0, a1, a2)                    do {} while (0)
#define DTRACE4(name, a0, a1, a2, a3)                do {} while (0)
#define DTRACE5(name, a0, a1, a2, a3, a4)            do {} while (0)
#define DTRACE6(name, a0, a1, a2, a3, a4, a5)        do {} while (0)
#define DTRACE7(name, a0, a1, a2, a3, a4, a5, a6)    do {} while (0)
#define DTRACE10(name, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9) \
                                                     do {} while (0)
#define DTRACE11(name, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) \
                                                     do {} while (0)

#if defined(_SDT_PROBE) && !defined(STAP_PROBE11)
/* work arround for missing STAP macro */
#define STAP_PROBE11(provider,name,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11) \
  _SDT_PROBE(provider, name, 11, \
             (arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11))
#define _SDT_ASM_OPERANDS_11(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11) \
  _SDT_ASM_OPERANDS_10(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9,arg10), \
    _SDT_ARG(11, arg11)
#endif

#endif  /* HAVE_DTRACE */

#endif  /* __DTRACE_WRAPPER_H */
