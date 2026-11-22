#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "process_identity.h"
#include "GoldHEN.h"

static int mock_result;
static struct proc_info mock_info;

int sys_sdk_proc_info(struct proc_info *info)
{
    if (mock_result != 0)
        return mock_result;

    *info = mock_info;
    return 0;
}

static void set_valid_mock(void)
{
    memset(&mock_info, 0, sizeof(mock_info));
    mock_info.pid = 123;
    strcpy(mock_info.name, "eboot.bin");
    strcpy(mock_info.titleid, "CUSA00001");
    strcpy(mock_info.version, "01.00");
    strcpy(mock_info.contentid, "UP0000-CUSA00001_00-TESTCONTENT0001");
    mock_info.base_address = 0x100000;
    mock_result = 0;
}

static void test_valid_identity(void)
{
    fusionfx_process_identity identity;

    set_valid_mock();
    assert(fusionfx_get_process_identity(&identity) == 0);
    assert(identity.pid == 123);
    assert(strcmp(identity.title_id, "CUSA00001") == 0);
    assert(strcmp(identity.process_name, "eboot.bin") == 0);
    assert(strcmp(identity.game_version, "01.00") == 0);
}

static void test_api_error_fails_closed(void)
{
    fusionfx_process_identity identity;

    set_valid_mock();
    mock_result = -1;
    assert(fusionfx_get_process_identity(&identity) == -2);
    assert(identity.pid == 0);
    assert(identity.title_id[0] == '\0');
}

static void test_empty_title_id_rejected(void)
{
    fusionfx_process_identity identity;

    set_valid_mock();
    mock_info.titleid[0] = '\0';
    assert(fusionfx_get_process_identity(&identity) == -3);
    assert(identity.pid == 0);
}

static void test_missing_terminator_rejected(void)
{
    fusionfx_process_identity identity;

    set_valid_mock();
    memset(mock_info.titleid, 'A', sizeof(mock_info.titleid));
    assert(fusionfx_get_process_identity(&identity) == -3);
    assert(identity.pid == 0);
}

static void test_null_output_rejected(void)
{
    set_valid_mock();
    assert(fusionfx_get_process_identity(NULL) == -1);
}

int main(void)
{
    test_valid_identity();
    test_api_error_fails_closed();
    test_empty_title_id_rejected();
    test_missing_terminator_rejected();
    test_null_output_rejected();

    puts("PASS: process identity discovery tests");
    return 0;
}
