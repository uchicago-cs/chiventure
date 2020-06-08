#include <criterion/criterion.h>
#include "wdl/load_wdz_internal.h"

/* Checks the file extension checker when format is normal */
Test(load_wdz, file_extension_normal)
{
    cr_assert_eq(filename_extension_is("wdz", "myfile.wdz"), true,
        "File extension was wdz but filename_extension_is returned false");

    cr_assert_eq(filename_extension_is("wdz", "myfile.zip"), false,
        "File extension was NOT wdz but filename_extension_is returned true");
}

/* Checks the file extension checker when filename has multiple dots */
Test(load_wdz, file_extension_multiple_dots)
{
    cr_assert_eq(filename_extension_is("wdz", "myfile.backup.wdz"), true,
        "File extension was wdz but filename_extension_is returned false");

    cr_assert_eq(filename_extension_is("wdz", "myfile.wdz.backup"), false,
        "File extension was NOT wdz but filename_extension_is returned true");
}

/* Checks the file extension checker when filename has path */
Test(load_wdz, file_extension_withpath)
{
    cr_assert_eq(filename_extension_is("wdz", "path/to/myfile.wdz"), true,
        "File extension was wdz but filename_extension_is returned false");

    cr_assert_eq(filename_extension_is("wdz", "path/to/myfile.zip"), false,
        "File extension was NOT wdz but filename_extension_is returned true");
}


/* The other loading functions do not have tests as their full
 * implementations are still pending, in branch wdl/parsing-wdz-namanh.
 */