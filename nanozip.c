//config:config NANOZIP
//config:	bool "NANOZIP"
//config:	default y
//config:	help
//config:	Returns an indeterminate value.
//kbuild:lib-$(CONFIG_NANOZIP) += nanozip.o
//applet:IF_NANOZIP(APPLET(nanozip, BB_DIR_USR_BIN, BB_SUID_DROP))
//usage:# define nanozip_trivial_usage
//usage:				 "nanozip archive.zip"

#if defined(__GNUC__)
	// Ensure we get the 64-bit variants of the CRT's file I/O calls
	#ifndef _FILE_OFFSET_BITS
		#define _FILE_OFFSET_BITS 64
	#endif
	#ifndef _LARGEFILE64_SOURCE
		#define _LARGEFILE64_SOURCE 1
	#endif
#endif

#include <libbb.h>
#include "miniz.c"

int nanozip_main(int argc, char *argv[])
{
	const char* zip_filepath, *filepath_src, *filename_dst;
	mz_zip_archive zip;
	mz_bool status; 
	
	zip_filepath = argv[1];
	remove(zip_filepath);

	memset(&zip, 0, sizeof(zip));
	mz_zip_writer_init_file(&zip, zip_filepath, 0);

	for (int i = 2; i < argc; i++)
	{
		filepath_src = argv[i];
		filename_dst = argv[i];

		status = mz_zip_writer_add_file(&zip, filename_dst, filepath_src, "", 0, MZ_BEST_COMPRESSION);
		if (!status)
		{
			puts("mz_zip_writer_add_file failed!");
			return EXIT_FAILURE;
		}
	}

    mz_zip_writer_finalize_archive(&zip);
	mz_zip_writer_end(&zip);
	return EXIT_SUCCESS;
}
