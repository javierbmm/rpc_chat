/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _RPCCHAT_H_RPCGEN
#define _RPCCHAT_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


enum status {
	_ERROR = 0,
	_OK = 1,
};
typedef enum status status;

#define rpcchat 0x20000001
#define rpcchat_version 0

#if defined(__STDC__) || defined(__cplusplus)
#define _write 1
extern  status * write_0(char **, CLIENT *);
extern  status * write_0_svc(char **, struct svc_req *);
#define getChat 2
extern  char ** getchat_0(void *, CLIENT *);
extern  char ** getchat_0_svc(void *, struct svc_req *);
extern int rpcchat_0_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define _write 1
extern  status * write_0();
extern  status * write_0_svc();
#define getChat 2
extern  char ** getchat_0();
extern  char ** getchat_0_svc();
extern int rpcchat_0_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_status (XDR *, status*);

#else /* K&R C */
extern bool_t xdr_status ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_RPCCHAT_H_RPCGEN */
