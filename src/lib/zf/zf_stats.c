/* SPDX-License-Identifier: MIT */
/* SPDX-FileCopyrightText: (c) Advanced Micro Devices, Inc. */
#include <zf_internal/zf_stack.h>

int
zf_stats_query_layout(struct zf_stack* stack,
                      const zf_stats_layout** const layout_out, int layout_sz)
{
  int i, rc = 0;
  int num_nics = stack->nics_n;

  if( num_nics > layout_sz )
    num_nics = layout_sz;

  for( i = 0; i < num_nics && rc == 0; i++ ) {
    ef_vi* vi = &stack->nic[i].vi;
    rc = ef_vi_stats_query_layout(vi,
        (const ef_vi_stats_layout** const) &layout_out[i]);
  }

  if( rc < 0 )
    return rc;
  return i;
}

int
zf_stats_query(struct zf_stack* stack, void* data,
               const zf_stats_layout** const layout,
               int nic_cnt, int do_reset)
{
  int i, rc = 0;
  int num_nics = stack->nics_n;
  char* pData = (char*)data;

  if( num_nics > nic_cnt)
    num_nics = nic_cnt;

  for( i = 0; i < num_nics && rc == 0; i++ ) {
    ef_vi* vi = &stack->nic[i].vi;
    rc = ef_vi_stats_query(vi, vi->dh, (void*)pData, do_reset);
    pData += layout[i]->zfsl_data_size;
  }

  if( rc < 0 )
    return rc;
  return i;
}
