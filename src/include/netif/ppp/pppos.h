/**
 * @file
 * Network Point to Point Protocol over Serial header file.
 *
 */

/*
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 */

#include "lwip/opt.h"
#if PPP_SUPPORT && PPPOS_SUPPORT /* don't build if not configured for use in lwipopts.h */

#ifndef PPPOS_H
#define PPPOS_H

#include "ppp.h"
#include "vj.h"

/*
 * PPPoS interface control block.
 */
typedef struct pppos_pcb_s pppos_pcb;
struct pppos_pcb_s {
  ppp_pcb *ppp;                  /* PPP PCB */
  sio_fd_t fd;                   /* File device ID of port. */
#if VJ_SUPPORT
  struct vjcompress vj_comp;     /* Van Jacobson compression header. */
#endif /* VJ_SUPPORT */
};

/* Create a new PPPoS session. */
ppp_pcb *ppp_over_serial_create(struct netif *pppif, sio_fd_t fd,
             ppp_link_status_cb_fn link_status_cb, void *ctx_cb);

/* PPP over Serial: this is the input function to be called for received data. */
void pppos_input(ppp_pcb *pcb, u_char* data, int len);


void pppos_vjc_config(ppp_pcb *pcb, int vjcomp, int cidcomp, int maxcid);
int pppos_vjc_comp(ppp_pcb *pcb, struct pbuf *pb);
int pppos_vjc_uncomp(ppp_pcb *pcb, struct pbuf *pb);

#endif /* PPPOS_H */
#endif /* PPP_SUPPORT && PPPOL2TP_SUPPORT */
