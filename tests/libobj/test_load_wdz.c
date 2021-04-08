#define _XOPEN_SOURCE 500
#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <criterion/criterion.h>
#include <stdio.h>
#include <ftw.h>
#include <unistd.h>
#include "libobj/obj.h"
#include "libobj/load.h"
#include "load_internal.h"
#include "common/utlist.h"
#include "common/uthash.h"

#define TEST_OUT_PATH "test_files/"
#define TEST_DATA_PATH "../../../tests/libobj/test_files/"

// Deletes a file
// From https://stackoverflow.com/questions/5467725/how-to-delete-a-directory-and-its-contents-in-posix-c
int unlink_cb(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    int rv = remove(fpath);

    if (rv)
        perror(fpath);

    return rv;
}

// Performs rm -rf on a directory
// From https://stackoverflow.com/questions/5467725/how-to-delete-a-directory-and-its-contents-in-posix-c
int rmrf(char *path)
{
    return nftw(path, unlink_cb, 64, FTW_DEPTH | FTW_PHYS);
}

// Deletes the test directory
void clean_testdir()
{
    char path[10 * (MAXLEN_ID + 1)] = {0};
    strcat(path, TEST_OUT_PATH);
    int rc = rmrf(path);
    cr_assert_eq(rc, 0, "rmrf errored- could not delete /build/tests/libobj/test_files/");
}

// Creates the test output directory
void make_testdir()
{
    char cwd[10 * (MAXLEN_ID + 1)] = {0};
    strcat(cwd, TEST_OUT_PATH);
    int rc = mkdir(cwd, 0777);
    cr_assert_eq(rc, 0, 
        "mkdir errored- make sure that /build/tests/libobj/test_files/ and any files inside "
        "have been deleted");
}

/* Tests _strip_expected_extension for an expected extension */
Test(test_load_wdz, extension_success)
{
    char str[] = "test_str.json";

    bool rc = _strip_expected_extension(str, "json");

    cr_assert_eq(rc, true, "_strip_expected_extension failed");
    cr_assert_str_eq(str, "test_str", 
        "_strip_expected_extension incorrectly modified the string");
}

/* Tests _strip_expected_extension for no extension */
Test(test_load_wdz, extension_none)
{
    char str[] = "test_str";

    bool rc = _strip_expected_extension(str, "json");

    cr_assert_eq(rc, false, "_strip_expected_extension failed");
}

/* Tests _strip_expected_extension for the wrong extension */
Test(test_load_wdz, extension_wrong)
{
    char str[] = "test_str.diff";

    bool rc = _strip_expected_extension(str, "json");

    cr_assert_eq(rc, false, "_strip_expected_extension failed");
}

/* Tests _strip_expected_extension for the wrong final extension */
Test(test_load_wdz, extension_wrong_nested)
{
    char str[] = "test_str.json.diff";

    bool rc = _strip_expected_extension(str, "json");

    cr_assert_eq(rc, false, "_strip_expected_extension failed");
}

/* Tests _strip_expected_extension for a DEFAULT file */
Test(test_load_wdz, extension_default)
{
    char str[] = "DEFAULT.json";

    bool rc = _strip_expected_extension(str, "json");

    cr_assert_eq(rc, true, "_strip_expected_extension failed");
    cr_assert_str_eq(str, ".", 
        "_strip_expected_extension incorrectly modified the string");
}

/* Tests _strip_expected_extension for a nested DEFAULT file */
Test(test_load_wdz, extension_default_nested)
{
    char str[] = "folder/DEFAULT.json";

    bool rc = _strip_expected_extension(str, "json");

    cr_assert_eq(rc, true, "_strip_expected_extension failed");
    cr_assert_str_eq(str, "folder/.", 
        "_strip_expected_extension incorrectly modified the string");
}

/* Tests _strip_expected_extension for a nested DEFAULT file inside a DEFAULT folder */
Test(test_load_wdz, extension_default_nested_default)
{
    char str[] = "DEFAULT/DEFAULT.json";

    bool rc = _strip_expected_extension(str, "json");

    cr_assert_eq(rc, true, "_strip_expected_extension failed");
    cr_assert_str_eq(str, "DEFAULT/.", 
        "_strip_expected_extension incorrectly modified the string");
}

/* Tests parsing a simple zip file */
Test(test_load_wdz, zip_simple, .init = make_testdir, .fini = clean_testdir)
{
    char zip_name[10 * (MAXLEN_ID + 1)] = {0};
    strcat(zip_name, TEST_OUT_PATH);
    strcat(zip_name, "zip_simple.zip");

    // Create the zip
    int error = 0;
    zip_t *zip = zip_open(zip_name, ZIP_CREATE | ZIP_EXCL, &error);
    cr_assert_eq(error, ZIP_ET_NONE, 
        "Could not create zip file; code: %d", error);

    // Add GAME.json to the zip
    char *data_name = "GAME.json";
    char *data_path = calloc(10 * (MAXLEN_ID + 1), sizeof(char));
    strcat(data_path, TEST_DATA_PATH);
    strcat(data_path, data_name);

    zip_error_t err = {0};
    zip_source_t *zip_src = zip_source_file_create(data_path, 0, 0, &err);
    cr_assert_not_null(zip_src, "Could not create zip source; code: %d", zip_error_system_type(&err));

    zip_int64_t idx = zip_file_add(zip, data_name, zip_src, ZIP_FL_ENC_UTF_8);
    cr_assert_neq(idx, -1, 
        "Could not add folder to zip file; check archive code");

    // Write and save to disk
    int rc = zip_close(zip);
    cr_assert_neq(rc, -1, 
        "Could not close zip file; check archive code");

    // Read the zip into an obj
    obj_t *obj = obj_new("test");
    rc = load_obj_zip(obj, zip_name);
    cr_assert_neq(rc, EXIT_FAILURE, "Could not load object from zip");

    char *str = obj_get_str(obj, "GAME.intro");
    cr_assert_str_eq("Welcome to the Test Dungeon!", str,
        "Received the incorrect data at 'GAME.start.id': %s", str);
}

/* Tests parsing a simple nested zip file */
Test(test_load_wdz, zip_nested, .init = make_testdir, .fini = clean_testdir)
{
    char zip_name[10 * (MAXLEN_ID + 1)] = {0};
    strcat(zip_name, TEST_OUT_PATH);
    strcat(zip_name, "zip_nested.zip");

    // Create the zip
    int error = 0;
    zip_t *zip = zip_open(zip_name, ZIP_CREATE | ZIP_EXCL, &error);
    cr_assert_eq(error, ZIP_ET_NONE, 
        "Could not create zip file; code: %d", error);

    char *folder_name = "ITEMS";
    zip_int64_t idx = zip_dir_add(zip, folder_name, 0);
    cr_assert_neq(idx, -1, 
        "Could not add folder to zip file; check archive code");

    // Add ITEMS/blue_lever.json to the zip
    char *data_name = "ITEMS/blue_lever.json";
    char *data_path = calloc(10 * (MAXLEN_ID + 1), sizeof(char));
    strcat(data_path, TEST_DATA_PATH);
    strcat(data_path, data_name);

    zip_error_t err = {0};
    zip_source_t *zip_src = zip_source_file_create(data_path, 0, 0, &err);
    cr_assert_not_null(zip_src, "Could not create zip source; code: %d", zip_error_system_type(&err));

    idx = zip_file_add(zip, data_name, zip_src, ZIP_FL_ENC_UTF_8);
    cr_assert_neq(idx, -1, 
        "Could not add file to zip file; check archive code");

    // Write and save to disk
    int rc = zip_close(zip);
    cr_assert_neq(rc, -1, 
        "Could not close zip file; check archive code");

    // Read the zip into an obj
    obj_t *obj = obj_new("test");
    rc = load_obj_zip(obj, zip_name);
    cr_assert_neq(rc, EXIT_FAILURE, "Could not load object from zip");

    char *str = obj_get_str(obj, "ITEMS.blue_lever.short_desc");
    cr_assert_str_eq("A blue lever.", str,
        "Received the incorrect data at 'ITEMS.blue_lever.short_desc': %s", str);
}

/* Tests parsing a simple zip file with DEFAULT */
Test(test_load_wdz, zip_default, .init = make_testdir, .fini = clean_testdir)
{
    char zip_name[10 * (MAXLEN_ID + 1)] = {0};
    strcat(zip_name, TEST_OUT_PATH);
    strcat(zip_name, "zip_default.zip");

    // Create the zip
    int error = 0;
    zip_t *zip = zip_open(zip_name, ZIP_CREATE | ZIP_EXCL, &error);
    cr_assert_eq(error, ZIP_ET_NONE, 
        "Could not create zip file; code: %d", error);

    char *folder_name = "ITEMS";
    zip_int64_t idx = zip_dir_add(zip, folder_name, 0);
    cr_assert_neq(idx, -1, 
        "Could not add folder to zip file; check archive code");

    // Add ITEMS/blue_lever.json to the zip
    char *data_name = "ITEMS/DEFAULT.json";
    char *data_path = calloc(10 * (MAXLEN_ID + 1), sizeof(char));
    strcat(data_path, TEST_DATA_PATH);
    strcat(data_path, data_name);

    zip_error_t err = {0};
    zip_source_t *zip_src = zip_source_file_create(data_path, 0, 0, &err);
    cr_assert_not_null(zip_src, "Could not create zip source; code: %d", zip_error_system_type(&err));

    idx = zip_file_add(zip, data_name, zip_src, ZIP_FL_ENC_UTF_8);
    cr_assert_neq(idx, -1, 
        "Could not add file to zip file; check archive code");

    // Write and save to disk
    int rc = zip_close(zip);
    cr_assert_neq(rc, -1, 
        "Could not close zip file; check archive code");

    // Read the zip into an obj
    obj_t *obj = obj_new("test");
    rc = load_obj_zip(obj, zip_name);
    cr_assert_neq(rc, EXIT_FAILURE, "Could not load object from zip");

    char *str = obj_get_str(obj, "ITEMS.SIGN.short_desc");
    cr_assert_str_eq("A sign.", str,
        "Received the incorrect data at 'ITEMS.SIGN.short_desc': %s", str);
}
