/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef TOOLS_CIF_H
#define TOOLS_CIF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <mtcr.h>
#include <tools_layouts/tools_open_layouts.h>


/**
 * tcif_query_dev_cap:
 * @param[in]  dev           A pointer to a device context.
 * @param[in]  offs          offset in even dword to read from the DEV_CAP vector
 * @param[out] data          Quad-word read from the device capabilities vector from offset: offs

 * @return     One of the MError* values, or a raw
 **/
MError tcif_query_dev_cap(mfile* dev, u_int32_t offs, u_int64_t* data);

/**
 * tcif_query_global_def_params:
 * @param[in]     dev           A pointer to a device context.
 * @param[in/out] global_params pointer to global params struct

 * @return     One of the MError* values, or a raw
 **/
MError tcif_query_global_def_params(mfile* dev, struct tools_open_query_def_params_global* global_params);

/**
 * tcif_query_per_port_def_params:
 * @param[in]     dev           A pointer to a device context.
 * @param[in]     port          Port that the query will be performed on (1 or 2)
 * @param[in/out] port_params   Pointer to port params struct

 * @return     One of the MError* values, or a raw
 **/
MError tcif_query_per_port_def_params(mfile* dev, u_int8_t port, struct tools_open_query_def_params_per_port* port_params);

/**
 * tcif_err2str:
 * @param[in]  rc            return code from one of the above functions

 * @return     string describing the error occured.
 **/
const char* tcif_err2str(MError rc);

#ifdef __cplusplus
}
#endif

#endif /* TOOLS_CIF_H */