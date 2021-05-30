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

#define TEST_OUT_PATH "./"
#define TEST_DATA_PATH "../../../tests/libobj/test_files/"


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
Test(test_load_wdz, zip_simple)
{
    char zip_name[10 * (MAXLEN_ID + 1)] = {0};
    strcat(zip_name, TEST_OUT_PATH);
    strcat(zip_name, "zip_simple.zip");

    // Create the zip
    int error = 0;
    zip_t *zip = zip_open(zip_name, ZIP_CREATE | ZIP_TRUNCATE, &error);
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

    int open_status;
    zip = zip_open(zip_name, 0, &open_status);

    // Read the zip into an obj
    obj_t *obj = obj_new("test");
    rc = load_obj_store_from_zip(obj, zip);
    cr_assert_neq(rc, EXIT_FAILURE, "Could not load object from zip");

    char *str = obj_get_str(obj, "GAME.intro");
    cr_assert_str_eq("Welcome to the Test Dungeon!", str,
        "Received the incorrect data at 'GAME.start.id': %s", str);
}

/* Tests parsing a simple nested zip file */
Test(test_load_wdz, zip_nested)
{
    char zip_name[10 * (MAXLEN_ID + 1)] = {0};
    strcat(zip_name, TEST_OUT_PATH);
    strcat(zip_name, "zip_nested.zip");

    // Create the zip
    int error = 0;
    zip_t *zip = zip_open(zip_name, ZIP_CREATE | ZIP_TRUNCATE, &error);
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

    int open_status;
    zip = zip_open(zip_name, 0, &open_status);

    // Read the zip into an obj
    obj_t *obj = obj_new("test");
    rc = load_obj_store_from_zip(obj, zip);
    cr_assert_neq(rc, EXIT_FAILURE, "Could not load object from zip");

    char *str = obj_get_str(obj, "ITEMS.blue_lever.short_desc");
    cr_assert_str_eq("A blue lever.", str,
        "Received the incorrect data at 'ITEMS.blue_lever.short_desc': %s", str);
}

/* Tests parsing a simple zip file with DEFAULT */
Test(test_load_wdz, zip_default)
{
    char zip_name[10 * (MAXLEN_ID + 1)] = {0};
    strcat(zip_name, TEST_OUT_PATH);
    strcat(zip_name, "zip_default.zip");

    // Create the zip
    int error = 0;
    zip_t *zip = zip_open(zip_name, ZIP_CREATE | ZIP_TRUNCATE, &error);
    cr_assert_eq(error, ZIP_ET_NONE, 
        "Could not create zip file; code: %d", error);

    char *folder_name = "ITEMS";
    zip_int64_t idx = zip_dir_add(zip, folder_name, 0);
    cr_assert_neq(idx, -1, 
        "Could not add folder to zip file; check archive code");

    // Add ITEMS/DEFAULT.json to the zip
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

    int open_status;
    zip = zip_open(zip_name, 0, &open_status);

    // Read the zip into an obj
    obj_t *obj = obj_new("test");
    rc = load_obj_store_from_zip(obj, zip);
    cr_assert_neq(rc, EXIT_FAILURE, "Could not load object from zip");

    char *str = obj_get_str(obj, "ITEMS.SIGN.short_desc");
    cr_assert_str_eq("A sign.", str,
        "Received the incorrect data at 'ITEMS.SIGN.short_desc': %s", str);
}

/* Tests parsing a zip file with multiple files */
Test(test_load_wdz, zip_multiple)
{
    char zip_name[10 * (MAXLEN_ID + 1)] = {0};
    strcat(zip_name, TEST_OUT_PATH);
    strcat(zip_name, "zip_default.zip");

    // Create the zip
    int error = 0;
    zip_t *zip = zip_open(zip_name, ZIP_CREATE | ZIP_TRUNCATE, &error);
    cr_assert_eq(error, ZIP_ET_NONE, 
        "Could not create zip file; code: %d", error);

    char *folder_name = "ITEMS";
    zip_int64_t idx = zip_dir_add(zip, folder_name, 0);
    cr_assert_neq(idx, -1, 
        "Could not add folder to zip file; check archive code");

    // Add GAME.json to the zip
    char *data_name0 = "GAME.json";
    char *data_path0 = calloc(10 * (MAXLEN_ID + 1), sizeof(char));
    strcat(data_path0, TEST_DATA_PATH);
    strcat(data_path0, data_name0);

    zip_error_t err0 = {0};
    zip_source_t *zip_src0 = zip_source_file_create(data_path0, 0, 0, &err0);
    cr_assert_not_null(zip_src0, "Could not create zip source; code: %d", zip_error_system_type(&err0));

    idx = zip_file_add(zip, data_name0, zip_src0, ZIP_FL_ENC_UTF_8);
    cr_assert_neq(idx, -1, 
        "Could not add folder to zip file; check archive code");

    // Add ITEMS/DEFAULT.json to the zip
    char *data_name1 = "ITEMS/DEFAULT.json";
    char *data_path1 = calloc(10 * (MAXLEN_ID + 1), sizeof(char));
    strcat(data_path1, TEST_DATA_PATH);
    strcat(data_path1, data_name1);

    zip_error_t err1 = {0};
    zip_source_t *zip_src1 = zip_source_file_create(data_path1, 0, 0, &err1);
    cr_assert_not_null(zip_src1, "Could not create zip source; code: %d", zip_error_system_type(&err1));

    idx = zip_file_add(zip, data_name1, zip_src1, ZIP_FL_ENC_UTF_8);
    cr_assert_neq(idx, -1, 
        "Could not add file to zip file; check archive code");

    // Add ITEMS/blue_lever.json to the zip
    char *data_name2 = "ITEMS/blue_lever.json";
    char *data_path2 = calloc(10 * (MAXLEN_ID + 1), sizeof(char));
    strcat(data_path2, TEST_DATA_PATH);
    strcat(data_path2, data_name2);

    zip_error_t err2 = {0};
    zip_source_t *zip_src2 = zip_source_file_create(data_path2, 0, 0, &err2);
    cr_assert_not_null(zip_src2, "Could not create zip source; code: %d", zip_error_system_type(&err2));

    idx = zip_file_add(zip, data_name2, zip_src2, ZIP_FL_ENC_UTF_8);
    cr_assert_neq(idx, -1, 
        "Could not add file to zip file; check archive code");

    // Write and save to disk
    int rc = zip_close(zip);
    cr_assert_neq(rc, -1, 
        "Could not close zip file; check archive code");

    int open_status;
    zip = zip_open(zip_name, 0, &open_status);

    // Read the zip into an obj
    obj_t *obj = obj_new("test");
    rc = load_obj_store_from_zip(obj, zip);
    cr_assert_neq(rc, EXIT_FAILURE, "Could not load object from zip");

    char *str = obj_get_str(obj, "GAME.intro");
    cr_assert_str_eq("Welcome to the Test Dungeon!", str,
        "Received the incorrect data at 'GAME.start.id': %s", str);

    str = obj_get_str(obj, "ITEMS.SIGN.short_desc");
    cr_assert_str_eq("A sign.", str,
        "Received the incorrect data at 'ITEMS.SIGN.short_desc': %s", str);

    str = obj_get_str(obj, "ITEMS.blue_lever.short_desc");
    cr_assert_str_eq("A blue lever.", str,
        "Received the incorrect data at 'ITEMS.blue_lever.short_desc': %s", str);
}
