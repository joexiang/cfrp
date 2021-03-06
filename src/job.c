#include <unistd.h>

#include "lib.h"
#include "job.h"
#include "logger.h"

void cfrp_start_worker_process(struct cfrp *frp, woker_handler run_process)
{
    pid_t mpid = getpid();
    pid_t pid;
    for (int i = 0; i < cfrp_cpu; i++)
    {
        if ((pid = fork()) < 0)
        {
            log_error("cfrp woker process error! %s", SYS_ERROR);
        }
        else if ((pid = getpid()) != mpid)
        {
            break;
        }
    }
    if (pid == mpid)
    {
        return;
    }
    else
    {
        worker_t *wk = (worker_t *)malloc(sizeof(worker_t));
        wk->ctx = frp;
        wk->pid = pid;
        run_process(wk);
    }
}