#include <env.h>
#include <pmap.h>
#include <printf.h>

/* Overview:
 *  Implement simple round-robin scheduling.
 *  Search through 'envs' for a runnable environment ,
 *  in circular fashion statrting after the previously running env,
 *  and switch to the first such environment found.
 *
 * Hints:
 *  The variable which is for counting should be defined as 'static'.
 */
void sched_yield_new(void)
{
	static int times = 0;
	struct Env *e = curenv;
	static int sched_i = 0;
	if (!e) {
		while (LIST_EMPTY(&env_sched_list[sched_i]))
			sched_i ^= 1;
		e = LIST_FIRST(&env_sched_list[sched_i]);
		times = e->env_pri;
		times -= 1;
		env_run(e);
	}
	if (times <= 0) {
		e->env_pri -= 1;
		if (e->env_pri == 0)
			env_destroy(e);
		LIST_REMOVE(e,env_sched_link);
		LIST_INSERT_HEAD(&env_sched_list[sched_i^1],e,env_sched_link);
		while (LIST_EMPTY(&env_sched_list[sched_i])) {
			sched_i ^= 1;
		}
		e = LIST_FIRST(&env_sched_list[sched_i]);
		times = e->env_pri;
		times -= 1;
		env_run(e);
	} else {
		times -= 1;
		env_run(e);
	}
}
