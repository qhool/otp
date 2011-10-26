/* example usage: dtrace -q -s /path/to/dist.d */
/*
 * %CopyrightBegin%
 * 
 * Copyright Scott Lystig Fritchie 2011. All Rights Reserved.
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

erlang*:::dist-monitor
{
    printf("monitor: pid %d, who %s, what %s, node %s, type %s, reason %s\n",
           pid,
           copyinstr(arg0), copyinstr(arg1), copyinstr(arg2), copyinstr(arg3),
           copyinstr(arg4));
}

erlang*:::dist-port_busy
{
    printf("port_busy: node %s, port %s, remote_node %s, blocked pid %s\n",
           copyinstr(arg0), copyinstr(arg1), copyinstr(arg2), copyinstr(arg3));
    blocked_procs[copyinstr(arg3)] = 1;
}

erlang*:::dist-port_not_busy
{
    printf("port_not_busy: node %s, port %s, remote_node %s\n",
           copyinstr(arg0), copyinstr(arg1), copyinstr(arg2));
}

erlang*:::process-scheduled
/blocked_procs[copyinstr(arg0)]/
{
    pidstr = copyinstr(arg0);
    printf("blocked pid %s scheduled now\n", pidstr);
    blocked_procs[pidstr] = 0;
}

/**
erlang*:::process-port_unblocked
{
    printf("process unblocked: pid %s, port %s\n",
           copyinstr(arg0), copyinstr(arg1));
}
**/
