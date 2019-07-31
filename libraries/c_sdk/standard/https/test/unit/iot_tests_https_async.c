/*
 * Amazon FreeRTOS HTTPS Client V1.0.0
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

/**
 * @file iot_tests_https_async.c
 * @brief Tests for IotHttpsClient_SendAsync().
 * in iot_https_client.h.
 */

#include "iot_tests_https_common.h"
#include "platform/iot_clock.h"

/**
 * @brief Timeout for all requests to finish on a single connection.
 */
#define HTTPS_TEST_ASYNC_TIMEOUT_MS                     ( (uint32_t) 30000 )

/**
 * @brief The maximum number of asynchronous requests on the same connection. 
 * 
 * This is used to separate the user buffers needed for each request.
 */
#define HTTPS_TEST_MAX_ASYNC_REQUESTS                   ( 3 )

/*-----------------------------------------------------------*/

/**
 * @brief HTTPS response and request user buffers for scheduling multiple requests.
 */
static uint8_t _pAsyncRespUserBuffers[HTTPS_TEST_MAX_ASYNC_REQUESTS][HTTPS_TEST_RESP_USER_BUFFER_SIZE] = { 0 };
static uint8_t _pAsyncReqUserBuffers[HTTPS_TEST_MAX_ASYNC_REQUESTS][HTTPS_TEST_REQ_USER_BUFFER_SIZE] = { 0 };

/**
 * @brief HTTPS request and response information configrations for sheduling multiple requests.
 */
static IotHttpsRequestInfo_t _pAsyncReqConfigs[HTTPS_TEST_MAX_ASYNC_REQUESTS] = {0};

/**
 * @brief A base IotHttpsAsyncInfo_t to copy to each of the request information configurations for each request.
 * 
 * The tests will replace callbacks in .callbacks as needed and add pPrivData as need for the test.
 */
static IotHttpsAsyncInfo_t _asyncInfoBase = {
    .callbacks = { 0 },     /* To be updated during TEST_SETUP and as needed during testing. */
    .pPrivData = NULL       /* To be updated as needed during testing. */
};

/**
 * @brief A base IotHttpsRequestInfo_t to copy to each of the request information configurations for each request.
 */
static IotHttpsRequestInfo_t _reqInfoBase = {
    .pPath = HTTPS_TEST_PATH,
    .pathLen = sizeof( HTTPS_TEST_PATH ) - 1,
    .method = IOT_HTTPS_METHOD_GET,
    .pHost = HTTPS_TEST_ADDRESS,
    .hostLen = sizeof( HTTPS_TEST_ADDRESS ) - 1,
    .isNonPersistent = false,
    .userBuffer.pBuffer = NULL, /* To be updated during TEST_SETUP. */
    .userBuffer.bufferLen = 0,  /* To be updated during TEST_SETUP. */
    .isAsync = true,
    .u.pAsyncInfo = &_asyncInfoBase
};

/**
 * @brief A IotHttpsResponseInfo_t for an asynchronous response.
 */
static IotHttpsResponseInfo_t _respInfoBase = {
    .userBuffer.pBuffer = NULL, /* To be updated during TEST_SETUP */
    .userBuffer.bufferLen = 0,  /* To be updated during TEST_SETUP */
    .pSyncInfo = NULL
};

/*-----------------------------------------------------------*/

/**
 * @brief Test group for HTTPS Client Async Unit tests.
 */
TEST_GROUP( HTTPS_Client_Unit_Async );

/*-----------------------------------------------------------*/

/**
 * @brief Test setup for the HTTP Client Async unit tests.
 */
TEST_SETUP( HTTPS_Client_Unit_Async )
{

    /* This will initialize the library before every test case, which is OK. */
    TEST_ASSERT_EQUAL_INT( true, IotSdk_Init() );
    TEST_ASSERT_EQUAL( IOT_HTTPS_OK, IotHttpsClient_Init());
}

/*-----------------------------------------------------------*/

/**
 * @brief Test teardown for the HTTP Client Async unit tests.
 */
TEST_TEAR_DOWN( HTTPS_Client_Unit_Async )
{
    IotHttpsClient_Deinit();
    IotSdk_Cleanup();
}

/*-----------------------------------------------------------*/

TEST_GROUP_RUNNER( HTTPS_Client_Unit_Async )
{
    RUN_TEST_CASE( HTTPS_Client_Unit_Async, SendAsyncInvalidParameters );
}

/*-----------------------------------------------------------*/

TEST( HTTPS_Client_Unit_Async, SendAsyncInvalidParameters )
{
    IotHttpsReturnCode_t returnCode = IOT_HTTPS_OK;
    IotHttpsRequestHandle_t reqHandle = IOT_HTTPS_REQUEST_HANDLE_INITIALIZER;
    IotHttpsConnectionHandle_t connHandle = IOT_HTTPS_CONNECTION_HANDLE_INITIALIZER;
    IotHttpsResponseHandle_t respHandle = IOT_HTTPS_RESPONSE_HANDLE_INITIALIZER;


}