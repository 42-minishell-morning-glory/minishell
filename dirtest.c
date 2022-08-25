#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

int main()
{
	DIR            *dir_info;
	struct dirent  *dir_entry;

	// mkdir( "test_A", 0755);
	// mkdir( "test_B", 0755);
	
	dir_info = opendir("bin_tree");
	if (dir_info != NULL)
	{
		dir_entry = readdir(dir_info);
		while (dir_entry)
		{
			printf("DIR : %s type : %hhu\n", dir_entry->d_name, dir_entry->d_type);
			dir_entry = readdir(dir_info);
		}
		closedir( dir_info);   
	}
}


// dir : 4 // file : 8
//typedef struct {
//	int	__dd_fd;	/* file descriptor associated with directory */
//	long	__dd_loc;	/* offset in current buffer */
//	long	__dd_size;	/* amount of data returned */
//	char	*__dd_buf;	/* data buffer */
//	int	__dd_len;	/* size of data buffer */
//	long	__dd_seek;	/* magic cookie returned */
//	__unused long	__padding; /* (__dd_rewind space left for bincompat) */
//	int	__dd_flags;	/* flags for readdir */
//	__darwin_pthread_mutex_t __dd_lock; /* for thread locking */
//	struct _telldir *__dd_td; /* telldir position recording */
//} DIR;