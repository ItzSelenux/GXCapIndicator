 gboolean cap_thread_active = FALSE;
 gboolean num_thread_active = FALSE;

void create_cap_thread(void *(*start_routine)(void *))
{
	if (pthread_create(&cap_threadid, NULL, start_routine, NULL) == 0)
	{
		cap_thread_active = TRUE;
	}
}

void create_num_thread(void *(*start_routine)(void *))
{
	if (pthread_create(&num_threadid, NULL, start_routine, NULL) == 0)
	{
		num_thread_active = TRUE;
	}
}

void cleanup_thread(pthread_t *thread, gboolean *active)
{
	if (*active)
	{
		pthread_cancel(*thread);
		pthread_join(*thread, NULL);
		*active = TRUE;
	}
}
