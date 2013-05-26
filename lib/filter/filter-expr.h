/*
 * Copyright (c) 2002-2012 BalaBit IT Ltd, Budapest, Hungary
 * Copyright (c) 1998-2012 Balázs Scheidler
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * As an additional exemption you are allowed to compile & link against the
 * OpenSSL libraries as published by the OpenSSL project. See the file
 * COPYING for details.
 *
 */

#ifndef FILTER_H_INCLUDED
#define FILTER_H_INCLUDED

#include "syslog-ng.h"
#include "logmsg.h"
#include "messages.h"
#include "logmatcher.h"
#include "cfg-parser.h"

struct _GlobalConfig;
typedef struct _FilterExprNode FilterExprNode;

struct _FilterExprNode
{
  guint32 ref_cnt;
  guint32 comp:1,   /* this not is negated */
          modify:1; /* this filter changes the log message */
  const gchar *type;
  void (*init)(FilterExprNode *self, GlobalConfig *cfg);
  gboolean (*eval)(FilterExprNode *self, LogMessage **msg, gint num_msg);
  void (*free_fn)(FilterExprNode *self);
};

gboolean filter_expr_eval(FilterExprNode *self, LogMessage *msg);
gboolean filter_expr_eval_with_context(FilterExprNode *self, LogMessage **msgs, gint num_msg);
void filter_expr_node_init(FilterExprNode *self);
FilterExprNode *filter_expr_ref(FilterExprNode *self);
void filter_expr_unref(FilterExprNode *self);

#endif
